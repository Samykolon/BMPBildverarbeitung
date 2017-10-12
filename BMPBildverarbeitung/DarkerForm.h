#pragma once

#include <math.h>

namespace BMPBildverarbeitung {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für DarkerForm
	/// </summary>
	public ref class DarkerForm : public System::Windows::Forms::Form
	{
	public:

		property int TValue;


		DarkerForm(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~DarkerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  BOK;
	protected:
	private: System::Windows::Forms::Button^  BCancel;
	private: System::Windows::Forms::TrackBar^  TDarker;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ToolTip^  TTTrackbar;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->BOK = (gcnew System::Windows::Forms::Button());
			this->BCancel = (gcnew System::Windows::Forms::Button());
			this->TDarker = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TTTrackbar = (gcnew System::Windows::Forms::ToolTip(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TDarker))->BeginInit();
			this->SuspendLayout();
			// 
			// BOK
			// 
			this->BOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->BOK->Location = System::Drawing::Point(12, 64);
			this->BOK->Name = L"BOK";
			this->BOK->Size = System::Drawing::Size(75, 23);
			this->BOK->TabIndex = 0;
			this->BOK->Text = L"OK";
			this->BOK->UseVisualStyleBackColor = true;
			// 
			// BCancel
			// 
			this->BCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->BCancel->Location = System::Drawing::Point(194, 64);
			this->BCancel->Name = L"BCancel";
			this->BCancel->Size = System::Drawing::Size(75, 23);
			this->BCancel->TabIndex = 1;
			this->BCancel->Text = L"Abbrechen";
			this->BCancel->UseVisualStyleBackColor = true;
			// 
			// TDarker
			// 
			this->TDarker->LargeChange = 25;
			this->TDarker->Location = System::Drawing::Point(12, 13);
			this->TDarker->Maximum = 255;
			this->TDarker->Name = L"TDarker";
			this->TDarker->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TDarker->Size = System::Drawing::Size(260, 45);
			this->TDarker->SmallChange = 5;
			this->TDarker->TabIndex = 2;
			this->TDarker->TickFrequency = 5;
			this->TDarker->TickStyle = System::Windows::Forms::TickStyle::None;
			this->TDarker->Value = 255;
			this->TDarker->Scroll += gcnew System::EventHandler(this, &DarkerForm::TDarker_Scroll);
			this->TDarker->ValueChanged += gcnew System::EventHandler(this, &DarkerForm::TDarker_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(21, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"0%";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(239, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"100%";
			// 
			// DarkerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(281, 99);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TDarker);
			this->Controls->Add(this->BCancel);
			this->Controls->Add(this->BOK);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"DarkerForm";
			this->Text = L"Verdunkeln";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TDarker))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void TDarker_ValueChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TDarker_Scroll(System::Object^  sender, System::EventArgs^  e);
};
}
