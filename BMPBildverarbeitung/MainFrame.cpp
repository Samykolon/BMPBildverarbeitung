#include "MainFrame.h"
#include <msclr\marshal.h>
#include <chrono>
#include <math.h>

// Filter
#include "HSVPixel.h"
#include "ChangeHSVValue.h"
#include "ApplySobel.h"
#include "ApplyGaussFilterBW.h"
#include "ApplyGaussRGB.h"
#include "ScaleWithNN.h"
#include "BMPScale.h"
#include "DarkenSIMD.h"

// Utilities
#include "Utilities.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace BMPBildverarbeitung;
using namespace System::Diagnostics;
using namespace std::chrono;
using namespace System::IO;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	BMPBildverarbeitung::MainFrame form;
	Application::Run(%form);
}

// BackgroundWorker-Completed-Event

void BMPBildverarbeitung::MainFrame::RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e)
{
	IsProcessing = false;
	ProgressBar->Visible = false;
}

// BackgroundWorker for the HSV-Value-Change-Process

inline void MainFrame::bwHSV_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	auto s = Stopwatch::StartNew();
	Filters::ChangeHSVValue(*BMPimage, 1, ValueFactor, SaturationFactor);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "HSV-Change: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// BackgroundWorker for the Sobel-Filter-Process

void BMPBildverarbeitung::MainFrame::bwSobel_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	auto s = Stopwatch::StartNew();
	Filters::ApplySobel(*BMPimage);	
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "Sobel: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// BackgroundWorker for the Gauss-Filter-Process

void BMPBildverarbeitung::MainFrame::bwGauss_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	auto s = Stopwatch::StartNew();
	Filters::ApplyGaussFilterRGB(*BMPimage);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "Gauss: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// BackgroundWorker for the GrayScale-Process

void BMPBildverarbeitung::MainFrame::bwGrayScale_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	
	auto s = Stopwatch::StartNew();
	Filters::DarkenSIMD(*BMPimage);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "Grayscale: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// BackgroundWorker for the Scaling-Process

void BMPBildverarbeitung::MainFrame::bwScale_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	// Speed "improvement" demo
		// Spoiler the reference is faster
	Utilities::Benchmark bench;

	BMP* image1 = new BMP(*BMPimage);
	BMP* image2 = new BMP(*BMPimage);

	bench.StartTimer("Reference Scale");
	Filters::ScaleWithNN(*image1, ScaleNewHeight, ScaleNewWidth);
	bench.StopTimer();

	
	bench.StartTimer("SIMD Scale");
	Filters::ScaleWithNNSIMD(*image2, ScaleNewHeight, ScaleNewWidth);
	bench.StopTimer();

	/*
	if (!Utilities::compareImage(image1, image1))
	{
		MessageBox::Show("Unlike each other");
	}*/
	
	delete image1;
	delete BMPimage;
	BMPimage = image2;
	
	UpdatePicture();
	/*
	auto s = Stopwatch::StartNew();
	Filters::ScaleWithNN(*BMPimage, ScaleNewHeight, ScaleNewWidth);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "Scaling: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
	*/
}

// BackgroundWorker for the Undo-Process

void BMPBildverarbeitung::MainFrame::bwUndo_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	auto s = Stopwatch::StartNew();
	BMPimage = new BMP(*UndoImage);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "Undo-Process: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// Button-Click-Event for the Button "Sobel-Filter"

inline System::Void BMPBildverarbeitung::MainFrame::BSobel_Click(System::Object ^ sender, System::EventArgs ^ e) 
{	
	if (!IsProcessing) {
		BUndo->Enabled = true;
		IsProcessing = true;		
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		UndoImage = new BMP(*BMPimage);

		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwSobel_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();	
	}			
}

// Button-Click-Event for the Button "Gauß-Filter"

inline System::Void BMPBildverarbeitung::MainFrame::BGauss_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (!IsProcessing) {
		BUndo->Enabled = true;
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		UndoImage = new BMP(*BMPimage);
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwGauss_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
	}
}

// Button-Click-Event for the Button "Skalierung"

inline System::Void BMPBildverarbeitung::MainFrame::BScale_Click(System::Object ^ sender, System::EventArgs ^ e) {

	BMPScale^ sc = gcnew BMPScale((BMPimage->TellWidth()).ToString(), (BMPimage->TellHeight()).ToString());
	double oldWidth, oldHeight;
		
	if (!IsProcessing) {

		if (sc->ShowDialog(this) == ::DialogResult::OK)
		{
			BUndo->Enabled = true;
			oldWidth = floor(sc->Width);
			oldHeight = floor(sc->Height);
			ScaleNewWidth = System::Convert::ToInt32(oldWidth);
			ScaleNewHeight = System::Convert::ToInt32(oldHeight);
			IsProcessing = true;
			ProgressBar->Visible = true;
			ProgressBar->Style = ProgressBarStyle::Continuous;
			ProgressBar->Style = ProgressBarStyle::Marquee;
			UndoImage = new BMP(*BMPimage);
			BackgroundWorker^ bw = gcnew BackgroundWorker();
			bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwScale_DoWork);
			bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
			bw->RunWorkerAsync();
		}	
	}
	
}

// Button-Click-Event for the Button "Graustufe"

inline System::Void BMPBildverarbeitung::MainFrame::BGrayScale_Click(System::Object ^ sender, System::EventArgs ^ e) {

	if (!IsProcessing) {
		BUndo->Enabled = true;
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		UndoImage = new BMP(*BMPimage);
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwGrayScale_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
	}
}

// Updates the Main Picture-Box

inline Void BMPBildverarbeitung::MainFrame::UpdatePicture()
{
	int PBWidht = PBMain->Size.Width;                                 
	int PBHeight = PBMain->Size.Height;
	int PictureWidth = BMPimage->TellWidth();
	int PictureHeight = BMPimage->TellHeight();

	if ((PictureWidth > PBWidht) || (PictureHeight > PBHeight))             // Preventing the PictureBox-Zoom from zooming an image smaller than the PictureBox itself
		PBMain->SizeMode = PictureBoxSizeMode::Zoom;
	else
		PBMain->SizeMode = PictureBoxSizeMode::Normal;

	PBMain->Image = ConvertBitmap::ToBitmap(BMPimage);
}



// Button-Click-Event for the Button "Anwenden"

System::Void BMPBildverarbeitung::MainFrame::BApply_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {
		BUndo->Enabled = true;
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;

		ValueFactor = TBrightness->Value;
		SaturationFactor = TSaturation->Value;
		if (ValueFactor < 20) {
			ValueFactor /= 20;
		}
		else if (ValueFactor > 20) {
			ValueFactor /= 20;
		}
		else {
			ValueFactor = 1;
		}
		if (SaturationFactor < 20) {
			SaturationFactor /= 20;
		}
		else if (SaturationFactor > 20) {
			SaturationFactor /= 20;
		}
		else {
			SaturationFactor = 1;
		}

		UndoImage = new BMP(*BMPimage);

		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwHSV_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();

		TBrightness->Value = 20;
		TSaturation->Value = 20;
		
	}	
}

// Button-Click-Event for the Button "Rückgängig"

System::Void BMPBildverarbeitung::MainFrame::BUndo_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwUndo_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
	}
}

// Loading an image

System::Void BMPBildverarbeitung::MainFrame::bMPLadenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
	OpenFileDialog->FileName = "";
	OpenFileDialog->DefaultExt = L".bmp";
	OpenFileDialog->AddExtension;
	OpenFileDialog->Filter = L"BMP-Datei (*.bmp)|*.bmp|DIP-Datei (*.dip)|*.dip";
	try {
		if (OpenFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			FilePath = OpenFileDialog->FileName;

			msclr::interop::marshal_context context;
			BMPimage->ReadFromFile(context.marshal_as<const char*>(FilePath));

			UpdatePicture();
			PBOriginal->Image = ConvertBitmap::ToBitmap(BMPimage);
			BUndo->Enabled = false;
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Ungültiges Dateiformat/Datei konnte nicht gelesen werden");
	}
	
}

// Saving an image

System::Void BMPBildverarbeitung::MainFrame::bMPSpeichernToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog->DefaultExt = L".bmp";
	SaveFileDialog->AddExtension;
	SaveFileDialog->Filter = L"BMP-Datei (*.bmp)|*.bmp";
	if (SaveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if (BMPimage != nullptr)
		{
			FilePath = SaveFileDialog->FileName;
			msclr::interop::marshal_context context;
			BMPimage->WriteToFile(context.marshal_as<const char*>(FilePath));
		}

	}
}

// Closing form

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->Close();
}
