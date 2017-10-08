#pragma once


#include "TurnBlackAndWhite.h"
#include "HSVPixel.h"
#include <iostream>
#include "Convert.h"


namespace BMPBildverarbeitung {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Resources;
	using namespace System::Reflection;


	/// <summary>
	/// Zusammenfassung für MainFrame
	/// </summary>
	public ref class MainFrame : public System::Windows::Forms::Form
	{
		Assembly^ assembly = Assembly::GetExecutingAssembly();
		AssemblyName^ assemblyName = assembly->GetName();
		ResourceManager^ rm = gcnew ResourceManager(assemblyName->Name + ".ImageResources", assembly);

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TrackBar^  THelligkeit;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TrackBar^  TSaturation;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  BApply2;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;

			 String^ FilePath;
	private: System::ComponentModel::BackgroundWorker^  applyWorker;

			 Boolean IsProcessing;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
			 BMP *BMPimage;

	public:
		MainFrame(void)
		{
			InitializeComponent();
			//pictureBox1->Image = safe_cast<Image^>(rm->GetObject("InitialImage"));

			BMPimage = new BMP();
			BMPimage->ReadFromFile("Initialimage.bmp");
			pictureBox1->Image = ConvertBitmap::ToBitmap(BMPimage);

			FilePath = L"Initialimage.bmp";
			IsProcessing = false;
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~MainFrame()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  dateiToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bMPLadenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bMPSpeichernToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  schließenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  beendenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bearbeitenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hilfeToolStripMenuItem;

	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private: System::Windows::Forms::Button^  BSobel;
	private: System::Windows::Forms::Button^  BGauss;
	private: System::Windows::Forms::Button^  BHelligkeit;
	private: System::Windows::Forms::Button^  BSaettigung;
	private: System::Windows::Forms::Button^  BSkalierung;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  BApply;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->dateiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bMPLadenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bMPSpeichernToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->schließenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->beendenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bearbeitenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hilfeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->BSobel = (gcnew System::Windows::Forms::Button());
			this->BGauss = (gcnew System::Windows::Forms::Button());
			this->BHelligkeit = (gcnew System::Windows::Forms::Button());
			this->BSaettigung = (gcnew System::Windows::Forms::Button());
			this->BSkalierung = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->BApply = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->THelligkeit = (gcnew System::Windows::Forms::TrackBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TSaturation = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->BApply2 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->applyWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->THelligkeit))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TSaturation))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->dateiToolStripMenuItem,
					this->bearbeitenToolStripMenuItem, this->hilfeToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1812, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// dateiToolStripMenuItem
			// 
			this->dateiToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->bMPLadenToolStripMenuItem,
					this->bMPSpeichernToolStripMenuItem, this->schließenToolStripMenuItem, this->beendenToolStripMenuItem
			});
			this->dateiToolStripMenuItem->Name = L"dateiToolStripMenuItem";
			this->dateiToolStripMenuItem->Size = System::Drawing::Size(57, 24);
			this->dateiToolStripMenuItem->Text = L"Datei";
			// 
			// bMPLadenToolStripMenuItem
			// 
			this->bMPLadenToolStripMenuItem->Name = L"bMPLadenToolStripMenuItem";
			this->bMPLadenToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->bMPLadenToolStripMenuItem->Text = L"BMP laden";
			this->bMPLadenToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrame::bMPLadenToolStripMenuItem_Click);
			// 
			// bMPSpeichernToolStripMenuItem
			// 
			this->bMPSpeichernToolStripMenuItem->Name = L"bMPSpeichernToolStripMenuItem";
			this->bMPSpeichernToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->bMPSpeichernToolStripMenuItem->Text = L"BMP speichern";
			// 
			// schließenToolStripMenuItem
			// 
			this->schließenToolStripMenuItem->Name = L"schließenToolStripMenuItem";
			this->schließenToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->schließenToolStripMenuItem->Text = L"Schließen";
			// 
			// beendenToolStripMenuItem
			// 
			this->beendenToolStripMenuItem->Name = L"beendenToolStripMenuItem";
			this->beendenToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->beendenToolStripMenuItem->Text = L"Beenden";
			this->beendenToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrame::beendenToolStripMenuItem_Click);
			// 
			// bearbeitenToolStripMenuItem
			// 
			this->bearbeitenToolStripMenuItem->Name = L"bearbeitenToolStripMenuItem";
			this->bearbeitenToolStripMenuItem->Size = System::Drawing::Size(93, 24);
			this->bearbeitenToolStripMenuItem->Text = L"Bearbeiten";
			// 
			// hilfeToolStripMenuItem
			// 
			this->hilfeToolStripMenuItem->Name = L"hilfeToolStripMenuItem";
			this->hilfeToolStripMenuItem->Size = System::Drawing::Size(53, 24);
			this->hilfeToolStripMenuItem->Text = L"Hilfe";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Location = System::Drawing::Point(17, 34);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1503, 850);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// BSobel
			// 
			this->BSobel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BSobel->Location = System::Drawing::Point(1528, 34);
			this->BSobel->Margin = System::Windows::Forms::Padding(4);
			this->BSobel->Name = L"BSobel";
			this->BSobel->Size = System::Drawing::Size(133, 28);
			this->BSobel->TabIndex = 2;
			this->BSobel->Text = L"Sobel";
			this->BSobel->UseVisualStyleBackColor = true;
			this->BSobel->Click += gcnew System::EventHandler(this, &MainFrame::BSobel_Click);
			// 
			// BGauss
			// 
			this->BGauss->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BGauss->Location = System::Drawing::Point(1669, 33);
			this->BGauss->Margin = System::Windows::Forms::Padding(4);
			this->BGauss->Name = L"BGauss";
			this->BGauss->Size = System::Drawing::Size(133, 28);
			this->BGauss->TabIndex = 3;
			this->BGauss->Text = L"Gauß-Filter";
			this->BGauss->UseVisualStyleBackColor = true;
			this->BGauss->Click += gcnew System::EventHandler(this, &MainFrame::BGauss_Click);
			// 
			// BHelligkeit
			// 
			this->BHelligkeit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BHelligkeit->Location = System::Drawing::Point(1528, 70);
			this->BHelligkeit->Margin = System::Windows::Forms::Padding(4);
			this->BHelligkeit->Name = L"BHelligkeit";
			this->BHelligkeit->Size = System::Drawing::Size(133, 28);
			this->BHelligkeit->TabIndex = 4;
			this->BHelligkeit->Text = L"Helligkeit";
			this->BHelligkeit->UseVisualStyleBackColor = true;
			this->BHelligkeit->Click += gcnew System::EventHandler(this, &MainFrame::BHelligkeit_Click);
			// 
			// BSaettigung
			// 
			this->BSaettigung->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BSaettigung->Location = System::Drawing::Point(1528, 106);
			this->BSaettigung->Margin = System::Windows::Forms::Padding(4);
			this->BSaettigung->Name = L"BSaettigung";
			this->BSaettigung->Size = System::Drawing::Size(133, 28);
			this->BSaettigung->TabIndex = 5;
			this->BSaettigung->Text = L"Sättigung";
			this->BSaettigung->UseVisualStyleBackColor = true;
			this->BSaettigung->Click += gcnew System::EventHandler(this, &MainFrame::BSaettigung_Click);
			// 
			// BSkalierung
			// 
			this->BSkalierung->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BSkalierung->Location = System::Drawing::Point(1669, 69);
			this->BSkalierung->Margin = System::Windows::Forms::Padding(4);
			this->BSkalierung->Name = L"BSkalierung";
			this->BSkalierung->Size = System::Drawing::Size(133, 28);
			this->BSkalierung->TabIndex = 6;
			this->BSkalierung->Text = L"Skalierung";
			this->BSkalierung->UseVisualStyleBackColor = true;
			this->BSkalierung->Click += gcnew System::EventHandler(this, &MainFrame::BSkalierung_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->BApply);
			this->groupBox1->Location = System::Drawing::Point(1528, 668);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4);
			this->groupBox1->Size = System::Drawing::Size(275, 217);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			// 
			// BApply
			// 
			this->BApply->Enabled = false;
			this->BApply->Location = System::Drawing::Point(9, 181);
			this->BApply->Margin = System::Windows::Forms::Padding(4);
			this->BApply->Name = L"BApply";
			this->BApply->Size = System::Drawing::Size(257, 28);
			this->BApply->TabIndex = 0;
			this->BApply->Text = L"Anwenden";
			this->BApply->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1533, 174);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 17);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Helligkeit";
			// 
			// THelligkeit
			// 
			this->THelligkeit->Location = System::Drawing::Point(1537, 193);
			this->THelligkeit->Margin = System::Windows::Forms::Padding(4);
			this->THelligkeit->Maximum = 40;
			this->THelligkeit->Name = L"THelligkeit";
			this->THelligkeit->Size = System::Drawing::Size(259, 56);
			this->THelligkeit->TabIndex = 9;
			this->THelligkeit->TickStyle = System::Windows::Forms::TickStyle::None;
			this->THelligkeit->Value = 20;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(1533, 277);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(68, 17);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Sättigung";
			// 
			// TSaturation
			// 
			this->TSaturation->Location = System::Drawing::Point(1537, 297);
			this->TSaturation->Margin = System::Windows::Forms::Padding(4);
			this->TSaturation->Maximum = 40;
			this->TSaturation->Name = L"TSaturation";
			this->TSaturation->Size = System::Drawing::Size(257, 56);
			this->TSaturation->TabIndex = 11;
			this->TSaturation->TickStyle = System::Windows::Forms::TickStyle::None;
			this->TSaturation->Value = 20;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(1533, 228);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(49, 17);
			this->label3->TabIndex = 12;
			this->label3->Text = L"-100%";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(1656, 228);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(28, 17);
			this->label4->TabIndex = 13;
			this->label4->Text = L"0%";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(1751, 228);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(52, 17);
			this->label5->TabIndex = 14;
			this->label5->Text = L"+100%";
			// 
			// BApply2
			// 
			this->BApply2->Location = System::Drawing::Point(1537, 407);
			this->BApply2->Margin = System::Windows::Forms::Padding(4);
			this->BApply2->Name = L"BApply2";
			this->BApply2->Size = System::Drawing::Size(257, 28);
			this->BApply2->TabIndex = 15;
			this->BApply2->Text = L"Anwenden";
			this->BApply2->UseVisualStyleBackColor = true;
			this->BApply2->Click += gcnew System::EventHandler(this, &MainFrame::BApply2_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(1533, 336);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(49, 17);
			this->label6->TabIndex = 16;
			this->label6->Text = L"-100%";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(1656, 336);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(28, 17);
			this->label7->TabIndex = 17;
			this->label7->Text = L"0%";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(1751, 336);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(52, 17);
			this->label8->TabIndex = 18;
			this->label8->Text = L"+100%";
			// 
			// applyWorker
			// 
			this->applyWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainFrame::applyWorker_DoWork);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Bitmap |*.bmp";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainFrame::openFileDialog1_FileOk);
			// 
			// MainFrame
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1812, 900);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->BApply2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->TSaturation);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->THelligkeit);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->BSkalierung);
			this->Controls->Add(this->BSaettigung);
			this->Controls->Add(this->BHelligkeit);
			this->Controls->Add(this->BGauss);
			this->Controls->Add(this->BSobel);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MainFrame";
			this->ShowIcon = false;
			this->Text = L"BMP - Bildverarbeitung";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->THelligkeit))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TSaturation))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	
	/*private: void bwHSV_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwHSV_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e);
	private: void bwSobel_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwSobel_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e);
	private: void bwGauss_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwGauss_RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e);*/


	private: System::Void beendenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BSobel_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BGauss_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BHelligkeit_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BSkalierung_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BSaettigung_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BApply2_Click(System::Object^  sender, System::EventArgs^  e);

	private: Void UpdatePicture();

	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void applyWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
private: System::Void bMPLadenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
};
}
