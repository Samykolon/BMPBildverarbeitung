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

//Utilities
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
	double value = THelligkeit->Value;
	double s = TSaturation->Value;
	if (value < 20) {
		value /= 20;
	}
	else if (value > 20) {
		value = 1 + (value / 20);
	}
	else {
		value = 1;
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
	Filters::ChangeHSVValue(*BMPimage, 1, value, s);	
}

inline void MainFrame::bwHSV_RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
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

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) {

	this->Close();

}

inline System::Void BMPBildverarbeitung::MainFrame::BSobel_Click(System::Object ^ sender, System::EventArgs ^ e) {
	
	if (!IsProcessing) {
		IsProcessing = true;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwSobel_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::bwSobel_RunWorkerCompleted);
		bw->RunWorkerAsync();	
		groupBox1->Text = "Sobel-Filter";
		BApply->Enabled = true;
	}	
	
		
}

inline System::Void BMPBildverarbeitung::MainFrame::BGauss_Click(System::Object ^ sender, System::EventArgs ^ e) {

	if (!IsProcessing) {
		IsProcessing = true;
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwGauss_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::bwGauss_RunWorkerCompleted);
		bw->RunWorkerAsync();
		groupBox1->Text = "Gauß-Filter";
		BApply->Enabled = true;
	}

	
	
}

inline System::Void BMPBildverarbeitung::MainFrame::BHelligkeit_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Helligkeit";
	BApply->Enabled = true;
	//Test to measure method time
	Utilities::Benchmark bench = Utilities::Benchmark();
	bench.StartTimer("TurnGrayScale");

//	auto watch = Stopwatch::StartNew();
	Filters::TurnToGrayScale(*BMPimage);
	bench.StopTimer();

//	MessageBox::Show(watch->ElapsedMilliseconds.ToString());
}

inline System::Void BMPBildverarbeitung::MainFrame::BSkalierung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	BMPScale^ sc = gcnew BMPScale((BMPimage->TellWidth()).ToString(), (BMPimage->TellHeight()).ToString());
	double breite, hoehe;
	int nbreite, nhoehe;
	if (sc->ShowDialog(this) == ::DialogResult::OK)
	{
		breite = floor(sc->breite);
		hoehe = floor(sc->hoehe);
		nbreite = System::Convert::ToInt32(breite);
		nhoehe = System::Convert::ToInt32(hoehe);
		Filters::ScaleWithNN(*BMPimage, nhoehe, nbreite);
		UpdatePicture();
				
	}

}

inline System::Void BMPBildverarbeitung::MainFrame::BSaettigung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Sättigung";
	BApply->Enabled = true;
	Filters::TurnToGrayScaleOptimized(*BMPimage);
	UpdatePicture();
	//Filters::ApplyGaussFilterBW("BestesBild.bmp");
}

inline Void BMPBildverarbeitung::MainFrame::UpdatePicture()
{
	pictureBox1->Image = ConvertBitmap::ToBitmap(BMPimage);
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
	double value = THelligkeit->Value;
	double s = TSaturation->Value;
	if (value < 20) {
		value /= 20;
	}
	else if (value > 20) {
		value = 1 + (value / 20);
	}
	else {
		value = 1;
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
	Filters::ChangeHSVValue(*BMPimage, 1, s, value);
	UpdatePicture();
}

System::Void BMPBildverarbeitung::MainFrame::bMPLadenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->FileName = "";
	openFileDialog1->DefaultExt = L".bmp";
	openFileDialog1->AddExtension;
	openFileDialog1->Filter = L"BMP-Datei (*.bmp)|*.bmp|DIP-Datei (*.dip)|*.dip";
	try {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			FilePath = openFileDialog1->FileName;

			msclr::interop::marshal_context context;
			BMPimage->ReadFromFile(context.marshal_as<const char*>(FilePath));

			pictureBox1->Image = ConvertBitmap::ToBitmap(BMPimage);
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Ungültiges Dateiformat/Datei konnte nicht gelesen werden");
	}
	
}
System::Void BMPBildverarbeitung::MainFrame::bMPSpeichernToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	saveFileDialog1->DefaultExt = L".bmp";
	saveFileDialog1->AddExtension;
	saveFileDialog1->Filter = L"BMP-Datei (*.bmp)|*.bmp";
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if (BMPimage != nullptr)
		{
			FilePath = saveFileDialog1->FileName;
			msclr::interop::marshal_context context;
			BMPimage->WriteToFile(context.marshal_as<const char*>(FilePath));
		}

	}
}

