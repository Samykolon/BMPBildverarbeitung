#pragma once

namespace BMPBildverarbeitung {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für BMPClosePrompt
	/// </summary>
	public ref class BMPClosePrompt : public System::Windows::Forms::Form
	{
	public:
		BMPClosePrompt(void)
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
		~BMPClosePrompt()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Button^  BSave;
	private: System::Windows::Forms::Button^  BDismiss;
	private: System::Windows::Forms::Button^  BCancel;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BSave = (gcnew System::Windows::Forms::Button());
			this->BDismiss = (gcnew System::Windows::Forms::Button());
			this->BCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(32, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(219, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Möchten SIe das bearbeitete Bild speichern\?";
			// 
			// BSave
			// 
			this->BSave->DialogResult = System::Windows::Forms::DialogResult::Yes;
			this->BSave->Location = System::Drawing::Point(13, 60);
			this->BSave->Name = L"BSave";
			this->BSave->Size = System::Drawing::Size(75, 23);
			this->BSave->TabIndex = 1;
			this->BSave->Text = L"Speichern";
			this->BSave->UseVisualStyleBackColor = true;
			// 
			// BDismiss
			// 
			this->BDismiss->DialogResult = System::Windows::Forms::DialogResult::No;
			this->BDismiss->Location = System::Drawing::Point(104, 59);
			this->BDismiss->Name = L"BDismiss";
			this->BDismiss->Size = System::Drawing::Size(75, 23);
			this->BDismiss->TabIndex = 2;
			this->BDismiss->Text = L"Verwerfen";
			this->BDismiss->UseVisualStyleBackColor = true;
			// 
			// BCancel
			// 
			this->BCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->BCancel->Location = System::Drawing::Point(197, 59);
			this->BCancel->Name = L"BCancel";
			this->BCancel->Size = System::Drawing::Size(75, 23);
			this->BCancel->TabIndex = 3;
			this->BCancel->Text = L"Abbrechen";
			this->BCancel->UseVisualStyleBackColor = true;
			// 
			// BMPClosePrompt
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 95);
			this->Controls->Add(this->BCancel);
			this->Controls->Add(this->BDismiss);
			this->Controls->Add(this->BSave);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"BMPClosePrompt";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Warnung";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
