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

// Utilities
#include "Utilities.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace BMPBildverarbeitung;
using namespace System::Diagnostics;
using namespace std::chrono;

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
	Filters::ChangeHSVValue(*BMPimage, 1, ValueFactor, SaturationFactor);
	UpdatePicture();
}

// BackgroundWorker for the Sobel-Filter-Process

void BMPBildverarbeitung::MainFrame::bwSobel_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::ApplySobel(*BMPimage);	
	UpdatePicture();
}

// BackgroundWorker for the Gauss-Filter-Process

void BMPBildverarbeitung::MainFrame::bwGauss_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::ApplyGaussFilterRGB(*BMPimage);
	UpdatePicture();
}

// BackgroundWorker for the GreyScale-Process

void BMPBildverarbeitung::MainFrame::bwGreyScale_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::TurnToGrayScaleOptimized(*BMPimage);
	//Filters::ApplyGaussFilterBW("BestesBild.bmp");
	UpdatePicture();
}

// BackgroundWorker for the Scaling-Process

void BMPBildverarbeitung::MainFrame::bwScale_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::ScaleWithNN(*BMPimage, ScaleNewHeight, ScaleNewWidth);
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
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwSobel_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();	
	}			
}

// Button-Click-Event for the Button "Gau�-Filter"

inline System::Void BMPBildverarbeitung::MainFrame::BGauss_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (!IsProcessing) {
		BUndo->Enabled = true;
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		// Copy BMPimage in UndoImage
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwGauss_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
	}
}

// Button-Click-Event for the Button "Helligkeit"

inline System::Void BMPBildverarbeitung::MainFrame::BHelligkeit_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	// Test to measure method time
	Utilities::Benchmark bench = Utilities::Benchmark();
	bench.StartTimer("TurnGrayScale");

	//auto watch = Stopwatch::StartNew();
	Filters::TurnToGrayScale(*BMPimage);
	bench.StopTimer();

	//MessageBox::Show(watch->ElapsedMilliseconds.ToString());
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
			// Copy BMPimage in UndoImage
			BackgroundWorker^ bw = gcnew BackgroundWorker();
			bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwScale_DoWork);
			bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
			bw->RunWorkerAsync();
		}	
	}
	
}

// Button-Click-Event for the Button "Graustufe"

inline System::Void BMPBildverarbeitung::MainFrame::BGreyScale_Click(System::Object ^ sender, System::EventArgs ^ e) {

	if (!IsProcessing) {
		BUndo->Enabled = true;
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		// Copy BMPimage in UndoImage
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwGreyScale_DoWork);
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

		// Copy BMPimage in UndoImage

		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwHSV_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();

		TBrightness->Value = 20;
		TSaturation->Value = 20;
		
	}	
}

System::Void BMPBildverarbeitung::MainFrame::BUndo_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Copy UndoBMP in BMPimage
	UpdatePicture();
	BUndo->Enabled = false;
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
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Ung�ltiges Dateiformat/Datei konnte nicht gelesen werden");
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
