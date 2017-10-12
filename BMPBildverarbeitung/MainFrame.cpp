#include "MainFrame.h"
#include "AboutForm.h"
#include "DarkerForm.h"
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
#include "AlphaBlend.h"
#include "CalculateNegative.h"

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
	RGBApixel colorToBlend;
	colorToBlend.Alpha = 127;
	colorToBlend.Blue = 0;
	colorToBlend.Green = 0;
	colorToBlend.Red = 255;
	Filters::TurnToGrayScaleOptimized(*BMPimage);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "Grayscale: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// BackgroundWorker for the Scaling-Process

void BMPBildverarbeitung::MainFrame::bwScale_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Utilities::Benchmark bench;
	
	bench.StartTimer("SIMD Scale");
	Filters::ScaleWithNNSIMD(*BMPimage, ScaleNewHeight, ScaleNewWidth);
	bench.StopTimer();
	
	UpdatePicture();

}

// BackgroundWorker for the Darken-Process

void BMPBildverarbeitung::MainFrame::bwDarker_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	auto s = Stopwatch::StartNew();
	Filters::DarkenSIMD(*BMPimage, DarkenFactor);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "DarkenSIMD: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// BackgroundWorker for the Alpha-Blending-Process

void BMPBildverarbeitung::MainFrame::bwAlphaBlend_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	auto s = Stopwatch::StartNew();
	RGBApixel AlphaBlendPixel;
	Color c = CDAlphaBlend->Color;
	AlphaBlendPixel.Alpha = 78;
	AlphaBlendPixel.Blue = c.B;
	AlphaBlendPixel.Green = c.G;
	AlphaBlendPixel.Red = c.R;
	Filters::AlphaBlend(*BMPimage, AlphaBlendPixel);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "AlphaBlend: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// BackgroundWorker for the Picture-Negative-Process

void BMPBildverarbeitung::MainFrame::bwNegative_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	auto s = Stopwatch::StartNew();
	Filters::CalculateNegative(*BMPimage);
	s->Stop();
	File::AppendAllText((String^)L"out.txt", "Negative: " + s->Elapsed.ToString() + Environment::NewLine);
	UpdatePicture();
}

// BackgroundWorker for the Undo-Process

void BMPBildverarbeitung::MainFrame::bwUndo_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	delete BMPimage;
	BMPimage = UndoImage;
	UndoImage = nullptr;
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
		if (UndoImage != nullptr)
			delete UndoImage;
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
		if (UndoImage != nullptr)
			delete UndoImage;
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
			if (UndoImage != nullptr)
				delete UndoImage;
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
		if (UndoImage != nullptr)
			delete UndoImage;
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

// Disable Buttons

Void BMPBildverarbeitung::MainFrame::DisableButtons()
{
	BDark->Enabled = false;
	BApply->Enabled = false;
	BUndo->Enabled = false;
	BSobel->Enabled = false;
	BGauss->Enabled = false;
	BGrayScale->Enabled = false;
	BScale->Enabled = false;
	BAlphaBlend->Enabled = false;
	BNegative->Enabled = false;
	label9->Visible = false;
	TSaturation->Value = 20;
	TBrightness->Value = 20;
	TSaturation->Enabled = false;
	TBrightness->Enabled = false;
}

// Enable Buttons

Void BMPBildverarbeitung::MainFrame::EnableButtons()
{
	BDark->Enabled = true;
	BApply->Enabled = true;
	BSobel->Enabled = true;
	BGauss->Enabled = true;
	BGrayScale->Enabled = true;
	BScale->Enabled = true;
	BAlphaBlend->Enabled = true;
	BNegative->Enabled = true;
	label9->Visible = true;
	TSaturation->Enabled = true;
	TBrightness->Enabled = true;
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
		if (UndoImage != nullptr)
			delete UndoImage;
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
		BUndo->Enabled = false;
	}
}

// Button-Click-Event for the Button "Verdunklern"

System::Void BMPBildverarbeitung::MainFrame::BDark_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DarkerForm^ DF = gcnew DarkerForm();
	
	if (!IsProcessing) {

		if (DF->ShowDialog(this) == ::DialogResult::OK)
		{
			BUndo->Enabled = true;
			DarkenFactor = DF->TValue;
			IsProcessing = true;
			ProgressBar->Visible = true;
			ProgressBar->Style = ProgressBarStyle::Continuous;
			ProgressBar->Style = ProgressBarStyle::Marquee;
			
			if (UndoImage != nullptr)
				delete UndoImage;

			UndoImage = new BMP(*BMPimage);
			BackgroundWorker^ bw = gcnew BackgroundWorker();
			bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwDarker_DoWork);
			bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
			bw->RunWorkerAsync();
		}
	}
}

// Button-Click-Event for the Button "Alpha-Blending"

System::Void BMPBildverarbeitung::MainFrame::BAlphaBlend_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {

		if (CDAlphaBlend->ShowDialog() == ::DialogResult::OK)
		{
			BUndo->Enabled = true;
			IsProcessing = true;
			ProgressBar->Visible = true;
			ProgressBar->Style = ProgressBarStyle::Continuous;
			ProgressBar->Style = ProgressBarStyle::Marquee;

			if (UndoImage != nullptr)
				delete UndoImage;

			UndoImage = new BMP(*BMPimage);
			BackgroundWorker^ bw = gcnew BackgroundWorker();
			bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwAlphaBlend_DoWork);
			bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
			bw->RunWorkerAsync();
		}
	}
}

// Button-Click-Event for the Button "Negativ"

System::Void BMPBildverarbeitung::MainFrame::BNegative_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {
		BUndo->Enabled = true;
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		BackgroundWorker^ bw = gcnew BackgroundWorker();

		if (UndoImage != nullptr)
			delete UndoImage;

		UndoImage = new BMP(*BMPimage);
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwNegative_DoWork);
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
			EnableButtons();
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

// Click-Event for the "Über..." Menulistitem

System::Void BMPBildverarbeitung::MainFrame::überToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	AboutForm^ AF = gcnew AboutForm();
	AF->ShowDialog();
}

System::Void BMPBildverarbeitung::MainFrame::schließenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	PBMain->Image = nullptr;
	PBOriginal->Image = nullptr;
	DisableButtons();
}

// Closing form

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->Close();
}
