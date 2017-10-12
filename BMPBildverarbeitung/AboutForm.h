#pragma once

namespace BMPBildverarbeitung {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für AboutForm
	/// </summary>
	public ref class AboutForm : public System::Windows::Forms::Form
	{
	public:
		AboutForm(void)
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
		~AboutForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  BClose;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;

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
			this->BClose = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// BClose
			// 
			this->BClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->BClose->Location = System::Drawing::Point(100, 179);
			this->BClose->Name = L"BClose";
			this->BClose->Size = System::Drawing::Size(75, 23);
			this->BClose->TabIndex = 0;
			this->BClose->Text = L"OK";
			this->BClose->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(77, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(125, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"BMP-Bildbearbeitung";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(47, 43);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(191, 26);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Copyright © 2017 Hannes Krumbiegel, \r\nFlorian Köhler, Samuel Dressel";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(48, 118);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(181, 39);
			this->label3->TabIndex = 3;
			this->label3->Text = L"EasyBMP C++ Library\r\neasybmp.sourceforge.net\r\nCopyright © 2005-2006 Paul Macklin";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(105, 86);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(69, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Version 1.0.0";
			// 
			// AboutForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(277, 217);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->BClose);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AboutForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Über...";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
