#pragma once

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

		ResourceManager^ rm = gcnew ResourceManager(assemblyName->Name+".ImageResources", assembly);

	public:
		MainFrame(void)
		{
			InitializeComponent();
			pictureBox1->Image = safe_cast<Image^>(rm->GetObject("InitialImage"));

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
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->dateiToolStripMenuItem,
					this->bearbeitenToolStripMenuItem, this->hilfeToolStripMenuItem
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
					this->bMPSpeichernToolStripMenuItem, this->schließenToolStripMenuItem, this->beendenToolStripMenuItem
			});
			this->dateiToolStripMenuItem->Name = L"dateiToolStripMenuItem";
			this->dateiToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->dateiToolStripMenuItem->Text = L"Datei";
			// 
			// bMPLadenToolStripMenuItem
			// 
			this->bMPLadenToolStripMenuItem->Name = L"bMPLadenToolStripMenuItem";
			this->bMPLadenToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->bMPLadenToolStripMenuItem->Text = L"BMP laden";
			// 
			// bMPSpeichernToolStripMenuItem
			// 
			this->bMPSpeichernToolStripMenuItem->Name = L"bMPSpeichernToolStripMenuItem";
			this->bMPSpeichernToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->bMPSpeichernToolStripMenuItem->Text = L"BMP speichern";
			// 
			// schließenToolStripMenuItem
			// 
			this->schließenToolStripMenuItem->Name = L"schließenToolStripMenuItem";
			this->schließenToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->schließenToolStripMenuItem->Text = L"Schließen";
			// 
			// beendenToolStripMenuItem
			// 
			this->beendenToolStripMenuItem->Name = L"beendenToolStripMenuItem";
			this->beendenToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->beendenToolStripMenuItem->Text = L"Beenden";
			this->beendenToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrame::beendenToolStripMenuItem_Click);
			// 
			// bearbeitenToolStripMenuItem
			// 
			this->bearbeitenToolStripMenuItem->Name = L"bearbeitenToolStripMenuItem";
			this->bearbeitenToolStripMenuItem->Size = System::Drawing::Size(75, 20);
			this->bearbeitenToolStripMenuItem->Text = L"Bearbeiten";
			// 
			// hilfeToolStripMenuItem
			// 
			this->hilfeToolStripMenuItem->Name = L"hilfeToolStripMenuItem";
			this->hilfeToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->hilfeToolStripMenuItem->Text = L"Hilfe";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Location = System::Drawing::Point(13, 28);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1127, 691);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// BSobel
			// 
			this->BSobel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BSobel->Location = System::Drawing::Point(1146, 28);
			this->BSobel->Name = L"BSobel";
			this->BSobel->Size = System::Drawing::Size(100, 23);
			this->BSobel->TabIndex = 2;
			this->BSobel->Text = L"Sobel";
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
			this->BGauss->Text = L"Gauß-Filter";
			this->BGauss->UseVisualStyleBackColor = true;
			this->BGauss->Click += gcnew System::EventHandler(this, &MainFrame::BGauss_Click);
			// 
			// BHelligkeit
			// 
			this->BHelligkeit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BHelligkeit->Location = System::Drawing::Point(1146, 57);
			this->BHelligkeit->Name = L"BHelligkeit";
			this->BHelligkeit->Size = System::Drawing::Size(100, 23);
			this->BHelligkeit->TabIndex = 4;
			this->BHelligkeit->Text = L"Helligkeit";
			this->BHelligkeit->UseVisualStyleBackColor = true;
			this->BHelligkeit->Click += gcnew System::EventHandler(this, &MainFrame::BHelligkeit_Click);
			// 
			// BSaettigung
			// 
			this->BSaettigung->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BSaettigung->Location = System::Drawing::Point(1146, 86);
			this->BSaettigung->Name = L"BSaettigung";
			this->BSaettigung->Size = System::Drawing::Size(100, 23);
			this->BSaettigung->TabIndex = 5;
			this->BSaettigung->Text = L"Sättigung";
			this->BSaettigung->UseVisualStyleBackColor = true;
			this->BSaettigung->Click += gcnew System::EventHandler(this, &MainFrame::BSaettigung_Click);
			// 
			// BSkalierung
			// 
			this->BSkalierung->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->BSkalierung->Location = System::Drawing::Point(1252, 56);
			this->BSkalierung->Name = L"BSkalierung";
			this->BSkalierung->Size = System::Drawing::Size(100, 23);
			this->BSkalierung->TabIndex = 6;
			this->BSkalierung->Text = L"Skalierung";
			this->BSkalierung->UseVisualStyleBackColor = true;
			this->BSkalierung->Click += gcnew System::EventHandler(this, &MainFrame::BSkalierung_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->BApply);
			this->groupBox1->Location = System::Drawing::Point(1146, 543);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(206, 176);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			// 
			// BApply
			// 
			this->BApply->Enabled = false;
			this->BApply->Location = System::Drawing::Point(7, 147);
			this->BApply->Name = L"BApply";
			this->BApply->Size = System::Drawing::Size(193, 23);
			this->BApply->TabIndex = 0;
			this->BApply->Text = L"Anwenden";
			this->BApply->UseVisualStyleBackColor = true;
			// 
			// MainFrame
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1359, 731);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->BSkalierung);
			this->Controls->Add(this->BSaettigung);
			this->Controls->Add(this->BHelligkeit);
			this->Controls->Add(this->BGauss);
			this->Controls->Add(this->BSobel);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainFrame";
			this->ShowIcon = false;
			this->Text = L"BMP - Bildverarbeitung";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void beendenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		this->Close();

	}
private: System::Void BSobel_Click(System::Object^  sender, System::EventArgs^  e) {

	groupBox1->Text = "Sobel-Filter";
	BApply->Enabled = true;
}
private: System::Void BGauss_Click(System::Object^  sender, System::EventArgs^  e) {

	groupBox1->Text = "Gauß-Filter";
	BApply->Enabled = true;
}
private: System::Void BHelligkeit_Click(System::Object^  sender, System::EventArgs^  e) {

	groupBox1->Text = "Helligkeit";
	BApply->Enabled = true;
}
private: System::Void BSkalierung_Click(System::Object^  sender, System::EventArgs^  e) {

	groupBox1->Text = "Skalierung";
	BApply->Enabled = true;
}
private: System::Void BSaettigung_Click(System::Object^  sender, System::EventArgs^  e) {

	groupBox1->Text = "Sättigung";
	BApply->Enabled = true;
}
};
}
