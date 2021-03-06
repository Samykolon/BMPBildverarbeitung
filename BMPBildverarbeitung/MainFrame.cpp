#include "MainFrame.h"
#include "AboutForm.h"
#include "DarkerForm.h"
#include "BMPClosePrompt.h"
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

//#define BENCHMARK


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
	this->Cursor = Cursors::Default;
	EnableButtons();
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

// BackgroundWorker for the GrayScale-Process

void BMPBildverarbeitung::MainFrame::bwGrayScale_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::TurnToGrayScaleOptimized(*BMPimage);
	UpdatePicture();
}

// BackgroundWorker for the Scaling-Process

void BMPBildverarbeitung::MainFrame::bwScale_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::ScaleWithNNSIMD(*BMPimage, ScaleNewHeight, ScaleNewWidth);	
	UpdatePicture();

}

// BackgroundWorker for the Darken-Process

void BMPBildverarbeitung::MainFrame::bwDarker_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::DarkenSIMD(*BMPimage, DarkenFactor);
	UpdatePicture();
}

// BackgroundWorker for the Alpha-Blending-Process

void BMPBildverarbeitung::MainFrame::bwAlphaBlend_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	RGBApixel AlphaBlendPixel;
	Color c = CDAlphaBlend->Color;
	AlphaBlendPixel.Alpha = 78;
	AlphaBlendPixel.Blue = c.B;
	AlphaBlendPixel.Green = c.G;
	AlphaBlendPixel.Red = c.R;
	Filters::AlphaBlend(*BMPimage, AlphaBlendPixel);
	UpdatePicture();
}

// BackgroundWorker for the Picture-Negative-Process

void BMPBildverarbeitung::MainFrame::bwNegative_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::CalculateNegative(*BMPimage);
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
		DisableButtons();
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		this->Cursor = Cursors::AppStarting;
		if (UndoImage != nullptr)
			delete UndoImage;
		UndoImage = new BMP(*BMPimage);
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwSobel_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
		BUndo->Enabled = true;
		Saved = false;
	}
}

// Button-Click-Event for the Button "Gau�-Filter"

inline System::Void BMPBildverarbeitung::MainFrame::BGauss_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {
		DisableButtons();
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		this->Cursor = Cursors::AppStarting;
		if (UndoImage != nullptr)
			delete UndoImage;
		UndoImage = new BMP(*BMPimage);
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwGauss_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
		BUndo->Enabled = true;
		Saved = false;
	}
}

// Button-Click-Event for the Button "Skalierung"

inline System::Void BMPBildverarbeitung::MainFrame::BScale_Click(System::Object ^ sender, System::EventArgs ^ e) {

	BMPScale^ sc = gcnew BMPScale((BMPimage->TellWidth()).ToString(), (BMPimage->TellHeight()).ToString());
	double oldWidth, oldHeight;

	if (!IsProcessing) {

		if (sc->ShowDialog(this) == ::DialogResult::OK)
		{
			DisableButtons();
			oldWidth = floor(sc->Width);
			oldHeight = floor(sc->Height);
			ScaleNewWidth = System::Convert::ToInt32(oldWidth);
			ScaleNewHeight = System::Convert::ToInt32(oldHeight);
			IsProcessing = true;
			ProgressBar->Visible = true;
			ProgressBar->Style = ProgressBarStyle::Continuous;
			ProgressBar->Style = ProgressBarStyle::Marquee;
			this->Cursor = Cursors::AppStarting;
			if (UndoImage != nullptr)
				delete UndoImage;
			UndoImage = new BMP(*BMPimage);
			BackgroundWorker^ bw = gcnew BackgroundWorker();
			bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwScale_DoWork);
			bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
			bw->RunWorkerAsync();
			BUndo->Enabled = true;
			Saved = false;
		}
	}

}

// Button-Click-Event for the Button "Graustufe"

inline System::Void BMPBildverarbeitung::MainFrame::BGrayScale_Click(System::Object ^ sender, System::EventArgs ^ e) {

	if (!IsProcessing) {
		DisableButtons();
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		this->Cursor = Cursors::AppStarting;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		if (UndoImage != nullptr)
			delete UndoImage;
		UndoImage = new BMP(*BMPimage);
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwGrayScale_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
		BUndo->Enabled = true;
		Saved = false;
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
	bMPSpeichernToolStripMenuItem->Enabled = false;
	schlie�enToolStripMenuItem->Enabled = false;
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
	bMPSpeichernToolStripMenuItem->Enabled = true;
	schlie�enToolStripMenuItem->Enabled = true;
}



// Button-Click-Event for the Button "Anwenden"

System::Void BMPBildverarbeitung::MainFrame::BApply_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		this->Cursor = Cursors::AppStarting;
		ValueFactor = TBrightness->Value;
		SaturationFactor = TSaturation->Value;
		DisableButtons();
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
		BUndo->Enabled = true;
		Saved = false;
		TBrightness->Value = 20;
		TSaturation->Value = 20;

	}
}

// Button-Click-Event for the Button "R�ckg�ngig"

System::Void BMPBildverarbeitung::MainFrame::BUndo_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		this->Cursor = Cursors::AppStarting;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwUndo_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
		BUndo->Enabled = false;
		Saved = true;
	}
}

// Button-Click-Event for the Button "Verdunkeln"

System::Void BMPBildverarbeitung::MainFrame::BDark_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	DarkerForm^ DF = gcnew DarkerForm();
	
	if (!IsProcessing) {

		if (DF->ShowDialog(this) == ::DialogResult::OK)
		{
			DisableButtons();
			DarkenFactor = DF->TValue;
			IsProcessing = true;
			ProgressBar->Visible = true;
			ProgressBar->Style = ProgressBarStyle::Continuous;
			ProgressBar->Style = ProgressBarStyle::Marquee;
			this->Cursor = Cursors::AppStarting;

			if (UndoImage != nullptr)
				delete UndoImage;

			UndoImage = new BMP(*BMPimage);
			BackgroundWorker^ bw = gcnew BackgroundWorker();
			bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwDarker_DoWork);
			bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
			bw->RunWorkerAsync();
			BUndo->Enabled = true;
			Saved = false;
		}
	}
}

// Button-Click-Event for the Button "Alpha-Blending"

System::Void BMPBildverarbeitung::MainFrame::BAlphaBlend_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {

		if (CDAlphaBlend->ShowDialog() == ::DialogResult::OK)
		{
			DisableButtons();
			IsProcessing = true;
			ProgressBar->Visible = true;
			ProgressBar->Style = ProgressBarStyle::Continuous;
			ProgressBar->Style = ProgressBarStyle::Marquee;
			this->Cursor = Cursors::AppStarting;

			if (UndoImage != nullptr)
				delete UndoImage;

			UndoImage = new BMP(*BMPimage);
			BackgroundWorker^ bw = gcnew BackgroundWorker();
			bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwAlphaBlend_DoWork);
			bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
			bw->RunWorkerAsync();
			BUndo->Enabled = true;
			Saved = false;
		}
	}
}

// Button-Click-Event for the Button "Negativ"

System::Void BMPBildverarbeitung::MainFrame::BNegative_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!IsProcessing) {
		DisableButtons();
		IsProcessing = true;
		ProgressBar->Visible = true;
		ProgressBar->Style = ProgressBarStyle::Continuous;
		ProgressBar->Style = ProgressBarStyle::Marquee;
		this->Cursor = Cursors::AppStarting;
		BackgroundWorker^ bw = gcnew BackgroundWorker();

		if (UndoImage != nullptr)
			delete UndoImage;

		UndoImage = new BMP(*BMPimage);
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwNegative_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::RunWorkerCompleted);
		bw->RunWorkerAsync();
		BUndo->Enabled = true;
		Saved = false;
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
			PBMain->Visible = true;
			PBOriginal->Visible = true;
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
			Saved = true;
		}

	}
}

// Click-Event for the "�ber..." Menulistitem

System::Void BMPBildverarbeitung::MainFrame::�berToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	AboutForm^ AF = gcnew AboutForm();
	AF->ShowDialog();
}

// Click-Event for the "BMP schlie�en" Menulistitem

System::Void BMPBildverarbeitung::MainFrame::schlie�enToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (Saved) {
		PBMain->Image = nullptr;
		PBOriginal->Image = nullptr;
		DisableButtons();
	}
	else {

		BMPClosePrompt^ CP = gcnew BMPClosePrompt();
		CP->ShowDialog();
		if (CP->DialogResult == ::DialogResult::Yes) {

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
					Saved = true;
					PBMain->Image = nullptr;
					PBOriginal->Image = nullptr;
					DisableButtons();
				}
			}
		}
		
		else if (CP->DialogResult == ::DialogResult::No) {

			PBMain->Image = nullptr;
			PBOriginal->Image = nullptr;
			DisableButtons();

		}


	}
}

// Tooltip for the Trackbar "Helligkeit"

System::Void BMPBildverarbeitung::MainFrame::TBrightness_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	double value;
	value = TBrightness->Value;
	if (value > 20 || value < 20) {
		value -= 20;
		value *= 5;
	}	
	else
		value = 0;

	value = floor(value);
	TT->SetToolTip(TBrightness, (value.ToString()) + "%");
}

// Tooltip for the Trackbar "S�ttigung"

System::Void BMPBildverarbeitung::MainFrame::TSaturation_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	double value;
	value = TSaturation->Value;
	if (value > 20 || value < 20) {
		value -= 20;
		value *= 5;
	}
	else
		value = 0;

	value = floor(value);
	TT->SetToolTip(TSaturation, (value.ToString()) + "%");
}

// Control PictureBox SizeMode

System::Void BMPBildverarbeitung::MainFrame::MainFrame_SizeChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	int PBWidht = PBMain->Size.Width;
	int PBHeight = PBMain->Size.Height;
	int PictureWidth = BMPimage->TellWidth();
	int PictureHeight = BMPimage->TellHeight();

	if ((PictureWidth > PBWidht) || (PictureHeight > PBHeight))             // Preventing the PictureBox-Zoom from zooming an image smaller than the PictureBox itself
		PBMain->SizeMode = PictureBoxSizeMode::Zoom;
	else
		PBMain->SizeMode = PictureBoxSizeMode::Normal;
}

// Closing form

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->Close();
}
