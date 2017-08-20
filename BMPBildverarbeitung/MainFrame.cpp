#include "MainFrame.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	BMPBildverarbeitung::MainFrame form;
	Application::Run(%form);
}

inline System::Void BMPBildverarbeitung::MainFrame::beendenToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) {

	this->Close();

}

inline System::Void BMPBildverarbeitung::MainFrame::BSobel_Click(System::Object ^ sender, System::EventArgs ^ e) {

	groupBox1->Text = "Sobel-Filter";
	BApply->Enabled = true;
	Filters::ChangeBrightness("InitialImage.bmp");
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
