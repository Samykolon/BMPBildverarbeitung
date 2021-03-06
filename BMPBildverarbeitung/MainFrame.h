#pragma once


#include "TurnGrayScale.h"
#include "HSVPixel.h"
#include <iostream>
#include "Convert.h"
#include "EasyBMP.h"


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
	/// Zusammenfassung f�r MainFrame
	/// </summary>
	public ref class MainFrame : public System::Windows::Forms::Form
	{
		
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TrackBar^  TBrightness;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TrackBar^  TSaturation;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  BApply;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;

	private: System::Windows::Forms::OpenFileDialog^  OpenFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  SaveFileDialog;
	private: System::Windows::Forms::PictureBox^  PBOriginal;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::ProgressBar^  ProgressBar;
	private: System::Windows::Forms::Button^  BUndo;
	private: System::Windows::Forms::ToolStripMenuItem^  �berToolStripMenuItem;
	private: System::Windows::Forms::Button^  BDark;
	private: System::Windows::Forms::Button^  BAlphaBlend;
	private: System::Windows::Forms::ColorDialog^  CDAlphaBlend;
	private: System::Windows::Forms::Button^  BNegative;
	private: System::Windows::Forms::ToolTip^  TT;
			
			 String^ FilePath;
			 Boolean IsProcessing;
			 BMP *BMPimage;
	         BMP *UndoImage;
			 BMP *TempImage;
			 property int ScaleNewWidth;
			 property int ScaleNewHeight;
			 property double ValueFactor;
			 property double SaturationFactor;
			 property unsigned char DarkenFactor;
			 property Boolean Saved;

	public:


		MainFrame(void)
		{
			InitializeComponent();
	
			BMPimage = new BMP();
			PBMain->Visible = false;
			PBOriginal->Visible = false;
			DisableButtons();
			PBMain->Image = ConvertBitmap::ToBitmap(BMPimage);
			PBOriginal->Image = ConvertBitmap::ToBitmap(BMPimage);
			Saved = true;
			IsProcessing = false;
			ProgressBar->Visible = false;

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
	private: System::Windows::Forms::ToolStripMenuItem^  schlie�enToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  beendenToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  hilfeToolStripMenuItem;

	private: System::Windows::Forms::PictureBox^  PBMain;

	private: System::Windows::Forms::Button^  BSobel;
	private: System::Windows::Forms::Button^  BGauss;
	private: System::Windows::Forms::Button^  BGrayScale;


	private: System::Windows::Forms::Button^  BScale;
	private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainFrame::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->dateiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bMPLadenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bMPSpeichernToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->schlie�enToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->beendenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hilfeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�berToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PBMain = (gcnew System::Windows::Forms::PictureBox());
			this->BSobel = (gcnew System::Windows::Forms::Button());
			this->BGauss = (gcnew System::Windows::Forms::Button());
			this->BGrayScale = (gcnew System::Windows::Forms::Button());
			this->BScale = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->TBrightness = (gcnew System::Windows::Forms::TrackBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TSaturation = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->BApply = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->OpenFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SaveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->PBOriginal = (gcnew System::Windows::Forms::PictureBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->ProgressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->BUndo = (gcnew System::Windows::Forms::Button());
			this->BDark = (gcnew System::Windows::Forms::Button());
			this->BAlphaBlend = (gcnew System::Windows::Forms::Button());
			this->CDAlphaBlend = (gcnew System::Windows::Forms::ColorDialog());
			this->BNegative = (gcnew System::Windows::Forms::Button());
			this->TT = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PBMain))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TBrightness))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TSaturation))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PBOriginal))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->dateiToolStripMenuItem,
					this->hilfeToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1359, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// dateiToolStripMenuItem
			// 
			this->dateiToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->bMPLadenToolStripMenuItem,
					this->bMPSpeichernToolStripMenuItem, this->schlie�enToolStripMenuItem, this->beendenToolStripMenuItem
			});
			this->dateiToolStripMenuItem->Name = L"dateiToolStripMenuItem";
			this->dateiToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->dateiToolStripMenuItem->Text = L"Datei";
			// 
			// bMPLadenToolStripMenuItem
			// 
			this->bMPLadenToolStripMenuItem->Name = L"bMPLadenToolStripMenuItem";
			this->bMPLadenToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->bMPLadenToolStripMenuItem->Text = L"BMP laden...";
			this->bMPLadenToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrame::bMPLadenToolStripMenuItem_Click);
			// 
			// bMPSpeichernToolStripMenuItem
			// 
			this->bMPSpeichernToolStripMenuItem->Name = L"bMPSpeichernToolStripMenuItem";
			this->bMPSpeichernToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->bMPSpeichernToolStripMenuItem->Text = L"BMP speichern...";
			this->bMPSpeichernToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrame::bMPSpeichernToolStripMenuItem_Click);
			// 
			// schlie�enToolStripMenuItem
			// 
			this->schlie�enToolStripMenuItem->Name = L"schlie�enToolStripMenuItem";
			this->schlie�enToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->schlie�enToolStripMenuItem->Text = L"BMP schlie�en";
			this->schlie�enToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrame::schlie�enToolStripMenuItem_Click);
			// 
			// beendenToolStripMenuItem
			// 
			this->beendenToolStripMenuItem->Name = L"beendenToolStripMenuItem";
			this->beendenToolStripMenuItem->Size = System::Drawing::Size(162, 22);
			this->beendenToolStripMenuItem->Text = L"Beenden";
			this->beendenToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrame::beendenToolStripMenuItem_Click);
			// 
			// hilfeToolStripMenuItem
			// 
			this->hilfeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->�berToolStripMenuItem });
			this->hilfeToolStripMenuItem->Name = L"hilfeToolStripMenuItem";
			this->hilfeToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->hilfeToolStripMenuItem->Text = L"Hilfe";
			// 
			// �berToolStripMenuItem
			// 
			this->�berToolStripMenuItem->Name = L"�berToolStripMenuItem";
			this->�berToolStripMenuItem->Size = System::Drawing::Size(108, 22);
			this->�berToolStripMenuItem->Text = L"�ber...";
			this->�berToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrame::�berToolStripMenuItem_Click);
			// 
			// PBMain
			// 
			this->PBMain->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->PBMain->Location = System::Drawing::Point(13, 28);
			this->PBMain->Name = L"PBMain";
			this->PBMain->Size = System::Drawing::Size(1127, 691);
			this->PBMain->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->PBMain->TabIndex = 1;
			this->PBMain->TabStop = false;
			// 
			// BSobel
			// 
			this->BSobel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BSobel->Location = System::Drawing::Point(1146, 28);
			this->BSobel->Name = L"BSobel";
			this->BSobel->Size = System::Drawing::Size(100, 23);
			this->BSobel->TabIndex = 2;
			this->BSobel->Text = L"Sobel-Filter";
			this->BSobel->UseVisualStyleBackColor = true;
			this->BSobel->Click += gcnew System::EventHandler(this, &MainFrame::BSobel_Click);
			// 
			// BGauss
			// 
			this->BGauss->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BGauss->Location = System::Drawing::Point(1252, 27);
			this->BGauss->Name = L"BGauss";
			this->BGauss->Size = System::Drawing::Size(100, 23);
			this->BGauss->TabIndex = 3;
			this->BGauss->Text = L"Gau�-Filter";
			this->BGauss->UseVisualStyleBackColor = true;
			this->BGauss->Click += gcnew System::EventHandler(this, &MainFrame::BGauss_Click);
			// 
			// BGrayScale
			// 
			this->BGrayScale->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BGrayScale->Location = System::Drawing::Point(1145, 57);
			this->BGrayScale->Name = L"BGrayScale";
			this->BGrayScale->Size = System::Drawing::Size(100, 23);
			this->BGrayScale->TabIndex = 5;
			this->BGrayScale->Text = L"Graustufe";
			this->BGrayScale->UseVisualStyleBackColor = true;
			this->BGrayScale->Click += gcnew System::EventHandler(this, &MainFrame::BGrayScale_Click);
			// 
			// BScale
			// 
			this->BScale->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BScale->Location = System::Drawing::Point(1252, 56);
			this->BScale->Name = L"BScale";
			this->BScale->Size = System::Drawing::Size(100, 23);
			this->BScale->TabIndex = 6;
			this->BScale->Text = L"Skalierung";
			this->BScale->UseVisualStyleBackColor = true;
			this->BScale->Click += gcnew System::EventHandler(this, &MainFrame::BScale_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1150, 167);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Helligkeit";
			// 
			// TBrightness
			// 
			this->TBrightness->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->TBrightness->Location = System::Drawing::Point(1153, 183);
			this->TBrightness->Maximum = 40;
			this->TBrightness->Name = L"TBrightness";
			this->TBrightness->Size = System::Drawing::Size(194, 45);
			this->TBrightness->TabIndex = 9;
			this->TBrightness->TickStyle = System::Windows::Forms::TickStyle::None;
			this->TBrightness->Value = 20;
			this->TBrightness->Scroll += gcnew System::EventHandler(this, &MainFrame::TBrightness_Scroll);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(1150, 251);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(52, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"S�ttigung";
			// 
			// TSaturation
			// 
			this->TSaturation->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->TSaturation->Location = System::Drawing::Point(1153, 267);
			this->TSaturation->Maximum = 40;
			this->TSaturation->Name = L"TSaturation";
			this->TSaturation->Size = System::Drawing::Size(193, 45);
			this->TSaturation->TabIndex = 11;
			this->TSaturation->TickStyle = System::Windows::Forms::TickStyle::None;
			this->TSaturation->Value = 20;
			this->TSaturation->Scroll += gcnew System::EventHandler(this, &MainFrame::TSaturation_Scroll);
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(1150, 211);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(36, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"-100%";
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(1242, 211);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(21, 13);
			this->label4->TabIndex = 13;
			this->label4->Text = L"0%";
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(1313, 211);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(39, 13);
			this->label5->TabIndex = 14;
			this->label5->Text = L"+100%";
			// 
			// BApply
			// 
			this->BApply->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BApply->Location = System::Drawing::Point(1153, 357);
			this->BApply->Name = L"BApply";
			this->BApply->Size = System::Drawing::Size(193, 23);
			this->BApply->TabIndex = 15;
			this->BApply->Text = L"Anwenden";
			this->BApply->UseVisualStyleBackColor = true;
			this->BApply->Click += gcnew System::EventHandler(this, &MainFrame::BApply_Click);
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(1150, 299);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(36, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"-100%";
			// 
			// label7
			// 
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(1242, 299);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(21, 13);
			this->label7->TabIndex = 17;
			this->label7->Text = L"0%";
			// 
			// label8
			// 
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(1313, 299);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(39, 13);
			this->label8->TabIndex = 18;
			this->label8->Text = L"+100%";
			// 
			// OpenFileDialog
			// 
			this->OpenFileDialog->FileName = L"OpenFileDialog";
			// 
			// PBOriginal
			// 
			this->PBOriginal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->PBOriginal->Location = System::Drawing::Point(1145, 512);
			this->PBOriginal->Name = L"PBOriginal";
			this->PBOriginal->Size = System::Drawing::Size(206, 169);
			this->PBOriginal->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->PBOriginal->TabIndex = 19;
			this->PBOriginal->TabStop = false;
			// 
			// label9
			// 
			this->label9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(1146, 494);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(73, 13);
			this->label9->TabIndex = 20;
			this->label9->Text = L"Originales Bild";
			// 
			// ProgressBar
			// 
			this->ProgressBar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ProgressBar->Location = System::Drawing::Point(1153, 386);
			this->ProgressBar->MarqueeAnimationSpeed = 20;
			this->ProgressBar->Name = L"ProgressBar";
			this->ProgressBar->Size = System::Drawing::Size(193, 21);
			this->ProgressBar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->ProgressBar->TabIndex = 21;
			this->ProgressBar->Value = 50;
			// 
			// BUndo
			// 
			this->BUndo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BUndo->Enabled = false;
			this->BUndo->Location = System::Drawing::Point(1153, 328);
			this->BUndo->Name = L"BUndo";
			this->BUndo->Size = System::Drawing::Size(193, 23);
			this->BUndo->TabIndex = 22;
			this->BUndo->Text = L"R�ckg�ngig";
			this->BUndo->UseVisualStyleBackColor = true;
			this->BUndo->Click += gcnew System::EventHandler(this, &MainFrame::BUndo_Click);
			// 
			// BDark
			// 
			this->BDark->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BDark->Location = System::Drawing::Point(1145, 87);
			this->BDark->Name = L"BDark";
			this->BDark->Size = System::Drawing::Size(100, 23);
			this->BDark->TabIndex = 23;
			this->BDark->Text = L"Verdunkeln";
			this->BDark->UseVisualStyleBackColor = true;
			this->BDark->Click += gcnew System::EventHandler(this, &MainFrame::BDark_Click);
			// 
			// BAlphaBlend
			// 
			this->BAlphaBlend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BAlphaBlend->Location = System::Drawing::Point(1252, 87);
			this->BAlphaBlend->Name = L"BAlphaBlend";
			this->BAlphaBlend->Size = System::Drawing::Size(100, 23);
			this->BAlphaBlend->TabIndex = 24;
			this->BAlphaBlend->Text = L"Alpha Blending";
			this->BAlphaBlend->UseVisualStyleBackColor = true;
			this->BAlphaBlend->Click += gcnew System::EventHandler(this, &MainFrame::BAlphaBlend_Click);
			// 
			// BNegative
			// 
			this->BNegative->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BNegative->Location = System::Drawing::Point(1145, 117);
			this->BNegative->Name = L"BNegative";
			this->BNegative->Size = System::Drawing::Size(100, 23);
			this->BNegative->TabIndex = 25;
			this->BNegative->Text = L"Negativ";
			this->BNegative->UseVisualStyleBackColor = true;
			this->BNegative->Click += gcnew System::EventHandler(this, &MainFrame::BNegative_Click);
			// 
			// MainFrame
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1359, 731);
			this->Controls->Add(this->BNegative);
			this->Controls->Add(this->BAlphaBlend);
			this->Controls->Add(this->BDark);
			this->Controls->Add(this->BUndo);
			this->Controls->Add(this->ProgressBar);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->PBOriginal);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->BApply);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->TSaturation);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->TBrightness);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->BScale);
			this->Controls->Add(this->BGrayScale);
			this->Controls->Add(this->BGauss);
			this->Controls->Add(this->BSobel);
			this->Controls->Add(this->PBMain);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MinimumSize = System::Drawing::Size(600, 700);
			this->Name = L"MainFrame";
			this->Text = L"BMP - Bildverarbeitung";
			this->SizeChanged += gcnew System::EventHandler(this, &MainFrame::MainFrame_SizeChanged);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PBMain))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TBrightness))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TSaturation))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PBOriginal))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: void RunWorkerCompleted(Object ^ sender, RunWorkerCompletedEventArgs ^ e);
	private: void bwHSV_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwSobel_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwGauss_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwGrayScale_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwScale_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwDarker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwAlphaBlend_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwNegative_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	private: void bwUndo_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	
	private: System::Void beendenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BSobel_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BGauss_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BScale_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BGrayScale_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BApply_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BUndo_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BDark_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BAlphaBlend_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void BNegative_Click(System::Object^  sender, System::EventArgs^  e);

	private: Void UpdatePicture();
	private: Void DisableButtons();
	private: Void EnableButtons();


	private: System::Void bMPLadenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void bMPSpeichernToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void �berToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void schlie�enToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void TBrightness_Scroll(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TSaturation_Scroll(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MainFrame_SizeChanged(System::Object^  sender, System::EventArgs^  e);
};
}
