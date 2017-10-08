#include "MainFrame.h"
#include <msclr\marshal.h>
#include <chrono>
#include "HSVPixel.h"
#include "ChangeBrightness.h"
#include "ChangeHSVValue.h"
#include "ApplySobel.h"
#include "ApplyGaussFilterBW.h"
#include "ApplyGaussRGB.h"
#include "ScaleWithNN.h"

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

//inline void MainFrame::bwHSV_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
//{
//	IsProcessing = true;
//	msclr::interop::marshal_context context;
//	Filters::ApplySobel(context.marshal_as<const char*>(FilePath));
//}
//
//inline void MainFrame::bwHSV_RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
//	FilePath = "Test.bmp";
//	UpdatePicture();
//	IsProcessing = false;
//}
//
//void BMPBildverarbeitung::MainFrame::bwSobel_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
//{
//	throw gcnew System::NotImplementedException();
//}
//
//void BMPBildverarbeitung::MainFrame::bwSobel_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e)
//{
//	throw gcnew System::NotImplementedException();
//}
//
//void BMPBildverarbeitung::MainFrame::bwGauss_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
//{
//	throw gcnew System::NotImplementedException();
//}
//
//void BMPBildverarbeitung::MainFrame::bwGauss_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e)
//{
//	throw gcnew System::NotImplementedException();
//}

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) {

	this->Close();

}

inline System::Void BMPBildverarbeitung::MainFrame::BSobel_Click(System::Object ^ sender, System::EventArgs ^ e) {
	
	/*if (!IsProcessing) {
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwBrightness_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::bwBrightness_RunWorkerCompleted);
		bw->RunWorkerAsync();
		IsProcessing = true;
	}*/
	groupBox1->Text = "Sobel-Filter";
	BApply->Enabled = true;
		
}

inline System::Void BMPBildverarbeitung::MainFrame::BGauss_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Gauß-Filter";
	BApply->Enabled = true;
	msclr::interop::marshal_context context;
	Filters::ChangeBrightness(BMPimage, 2);
	pictureBox1->Image = ConvertBitmap::ToBitmap(BMPimage);
}

inline System::Void BMPBildverarbeitung::MainFrame::BHelligkeit_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Helligkeit";
	BApply->Enabled = true;
	//Test to measure method time
	
	msclr::interop::marshal_context context;
	auto watch = Stopwatch::StartNew();
	Filters::TurnBlackAndWhite(context.marshal_as<const char*>(FilePath));
	watch->Stop();

	MessageBox::Show(watch->ElapsedMilliseconds.ToString());
}

inline System::Void BMPBildverarbeitung::MainFrame::BSkalierung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Skalierung";
	BApply->Enabled = true;
	msclr::interop::marshal_context context;
	Filters::ChangeHSVValue(context.marshal_as<const char*>(FilePath), 1, 1, 1);
}

inline System::Void BMPBildverarbeitung::MainFrame::BSaettigung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Sättigung";
	BApply->Enabled = true;
	Filters::ScaleWithNN("BestesBild.bmp", 300, 300);
}

inline Void BMPBildverarbeitung::MainFrame::UpdatePicture()
{
	pictureBox1->Image = Image::FromFile(FilePath);	
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
		s = 1 + (s / 20);
	}
	else {
		s = 1;
	}
	Filters::ChangeHSVValue(context.marshal_as<const char*>(FilePath), 1, value, s);
	UpdatePicture();
}
