#include "MainFrame.h"
#include <msclr\marshal.h>
#include <chrono>
#include "HSVPixel.h"
#include "ChangeBrightness.h"

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

inline void MainFrame::bwBrightness_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	msclr::interop::marshal_context context;
	Filters::TurnBlackAndWhite(context.marshal_as<const char*>(FilePath));
}

inline void MainFrame::bwBrightness_RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
	FilePath = "Test.bmp";
	UpdatePicture();
	IsProcessing = false;
}

void BMPBildverarbeitung::MainFrame::bwSobel_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	throw gcnew System::NotImplementedException();
}

void BMPBildverarbeitung::MainFrame::bwSobel_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e)
{
	throw gcnew System::NotImplementedException();
}

void BMPBildverarbeitung::MainFrame::bwGauss_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	throw gcnew System::NotImplementedException();
}

void BMPBildverarbeitung::MainFrame::bwGauss_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e)
{
	throw gcnew System::NotImplementedException();
}

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) {

	this->Close();

}

inline System::Void BMPBildverarbeitung::MainFrame::BSobel_Click(System::Object ^ sender, System::EventArgs ^ e) {
	
	if (!IsProcessing) {
		BackgroundWorker^ bw = gcnew BackgroundWorker();
		bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwBrightness_DoWork);
		bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::bwBrightness_RunWorkerCompleted);
		bw->RunWorkerAsync();
		IsProcessing = true;
	}
	groupBox1->Text = "Sobel-Filter";
	BApply->Enabled = true;
		
}

inline System::Void BMPBildverarbeitung::MainFrame::BGauss_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Gauß-Filter";
	BApply->Enabled = true;
	msclr::interop::marshal_context context;
	Filters::ChangeBrightness(context.marshal_as<const char*>(FilePath));
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
}

inline System::Void BMPBildverarbeitung::MainFrame::BSaettigung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Sättigung";
	BApply->Enabled = true;
}

inline Void BMPBildverarbeitung::MainFrame::UpdatePicture()
{
	pictureBox1->Image = Image::FromFile(FilePath);	
}
