#include "MainFrame.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace BMPBildverarbeitung;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	BMPBildverarbeitung::MainFrame form;
	Application::Run(%form);
}

void MainFrame::bwBrightness_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	Filters::ChangeBrightness("Initialimage.bmp");	
}

void MainFrame::bwBrightness_RunWorkerCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
	FilePath = "Test.bmp";
	UpdatePicture();
}

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) {

	this->Close();

}

inline System::Void BMPBildverarbeitung::MainFrame::BSobel_Click(System::Object ^ sender, System::EventArgs ^ e) {
	BackgroundWorker^ bw = gcnew BackgroundWorker();
	bw->DoWork += gcnew DoWorkEventHandler(this, &MainFrame::bwBrightness_DoWork);
	bw->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BMPBildverarbeitung::MainFrame::bwBrightness_RunWorkerCompleted);
	bw->RunWorkerAsync();
	
	groupBox1->Text = "Sobel-Filter";
	BApply->Enabled = true;
		
}

inline System::Void BMPBildverarbeitung::MainFrame::BGauss_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Gauß-Filter";
	BApply->Enabled = true;
}

inline System::Void BMPBildverarbeitung::MainFrame::BHelligkeit_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Helligkeit";
	BApply->Enabled = true;
}

inline System::Void BMPBildverarbeitung::MainFrame::BSkalierung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Skalierung";
	BApply->Enabled = true;
}

inline System::Void BMPBildverarbeitung::MainFrame::BSaettigung_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Sättigung";
	BApply->Enabled = true;
}

Void BMPBildverarbeitung::MainFrame::UpdatePicture()
{
	pictureBox1->Image = Image::FromFile(FilePath);	
}
