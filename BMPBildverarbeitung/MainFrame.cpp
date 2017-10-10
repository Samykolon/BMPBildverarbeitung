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

inline void MainFrame::bwHSV_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	IsProcessing = true;
	double v = TBrightness->Value;
	double s = TSaturation->Value;
	if (v < 20) {
		v /= 20;
	}
	else if (v > 20) {
		v /= 20;
	}
	else {
		v = 1;
	}
	if (s < 20) {
		s /= 20;
	}
	else if (s > 20) {
		s = 1 + (s / 20);
	}
	else {
		s = 1;
	}
	Filters::ChangeHSVValue(*BMPimage, 1, v, s);
	TBrightness->Value = 20;
	TSaturation->Value = 20;
}

inline void MainFrame::bwHSV_RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) 
{
	UpdatePicture();
	IsProcessing = false;
}

void BMPBildverarbeitung::MainFrame::bwSobel_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::ApplySobel(*BMPimage);	
}

void BMPBildverarbeitung::MainFrame::bwSobel_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e)
{
	UpdatePicture();
	IsProcessing = false;
	ProgressBar->Visible = false;
}

void BMPBildverarbeitung::MainFrame::bwGauss_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::ApplyGaussFilterRGB(*BMPimage);
}

void BMPBildverarbeitung::MainFrame::bwGauss_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e)
{
	UpdatePicture();
	IsProcessing = false;
}

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->Close();
}

inline System::Void BMPBildverarbeitung::MainFrame::BSobel_Click(System::Object ^ sender, System::EventArgs ^ e) 
{	
	if (!IsProcessing) {
		IsProcessing = true;
		ProgressBar->Visible = true;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwSobel_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::bwSobel_RunWorkerCompleted);
		bw->RunWorkerAsync();	
	}			
}

inline System::Void BMPBildverarbeitung::MainFrame::BGauss_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	if (!IsProcessing) {
		IsProcessing = true;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwGauss_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::bwGauss_RunWorkerCompleted);
		bw->RunWorkerAsync();
	}
}

inline System::Void BMPBildverarbeitung::MainFrame::BHelligkeit_Click(System::Object ^ sender, System::EventArgs ^ e) 
{
	// Test to measure method time
	Utilities::Benchmark bench = Utilities::Benchmark();
	bench.StartTimer("TurnGrayScale");

	// auto watch = Stopwatch::StartNew();
	Filters::TurnToGrayScale(*BMPimage);
	bench.StopTimer();

//	MessageBox::Show(watch->ElapsedMilliseconds.ToString());
}

inline System::Void BMPBildverarbeitung::MainFrame::BSkalierung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	BMPScale^ sc = gcnew BMPScale((BMPimage->TellWidth()).ToString(), (BMPimage->TellHeight()).ToString());
	double oldWidth, oldHeight;
	int newWidth, newHeight;
	if (sc->ShowDialog(this) == ::DialogResult::OK)
	{
		oldWidth = floor(sc->Width);
		oldHeight = floor(sc->Height);
		newWidth = System::Convert::ToInt32(oldWidth);
		newHeight = System::Convert::ToInt32(oldHeight);
		Filters::ScaleWithNN(*BMPimage, newHeight, newWidth);
		UpdatePicture();				
	}
}

inline System::Void BMPBildverarbeitung::MainFrame::BSaettigung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	Filters::TurnToGrayScaleOptimized(*BMPimage);
	UpdatePicture();
	//Filters::ApplyGaussFilterBW("BestesBild.bmp");
}

inline Void BMPBildverarbeitung::MainFrame::UpdatePicture()
{
	PBMain->Image = ConvertBitmap::ToBitmap(BMPimage);
}

inline System::Void BMPBildverarbeitung::MainFrame::backgroundWorker1_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e) {

	
}

inline System::Void BMPBildverarbeitung::MainFrame::applyWorker_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e) {

}

System::Void BMPBildverarbeitung::MainFrame::BApply2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//if (!IsProcessing) {
	//	BackgroundWorker^ bw = gcnew BackgroundWorker();
	//	bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwHSV_DoWork);
	//	bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::bwHSV_RunWorkerCompleted);
	//	bw->RunWorkerAsync();
	//	IsProcessing = true;
	//}

	if (!IsProcessing) {
		applyWorker->RunWorkerAsync();
	}


	msclr::interop::marshal_context context;
	double v = TBrightness->Value;
	double s = TSaturation->Value;
	if (v < 20) {
		v /= 20;
	}
	else if (v > 20) {
		v /= 20;
	}
	else {
		v = 1;
	}
	if (s < 20) {
		s /= 20;
	}
	else if (s > 20) {
		s /= 20;

	}
	else {
		s = 1;
	}
	Filters::ChangeHSVValue(*BMPimage, 1, s, v);
	TBrightness->Value = 20;
	TSaturation->Value = 20;
	UpdatePicture();
}

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

			PBMain->Image = ConvertBitmap::ToBitmap(BMPimage);
			PBOriginal->Image = ConvertBitmap::ToBitmap(BMPimage);
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Ungültiges Dateiformat/Datei konnte nicht gelesen werden");
	}
	
}
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

