// Header-File for the Scaling-Window

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
	/// Zusammenfassung für Scale
	/// </summary>
	public ref class BMPScale : public System::Windows::Forms::Form
	{		

	public:
		property Boolean CheckBoxChecked;
		property double Width;
		property double Height;
		property double Proportions;
		property Boolean IsLoaded;
		property Boolean EditWidth;
		property Boolean EditHeight;
		
		BMPScale(void)
		{
			InitializeComponent();			
		}

		BMPScale(String^ _width, String^ _height)
		{
			IsLoaded = false;
			InitializeComponent();
			CheckBoxChecked = true;
			TBWidth->Text = _width;
			TBHeight->Text = _height;
			Width = System::Convert::ToDouble(TBWidth->Text);
			Height = System::Convert::ToDouble(TBHeight->Text);
			Proportions = Width / Height; 
			IsLoaded = true;
			EditWidth = false;
			EditHeight = false;
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~BMPScale()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  TBWidth;
	private: System::Windows::Forms::TextBox^  TBHeight;
	private: System::Windows::Forms::CheckBox^  CBProportions;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->TBWidth = (gcnew System::Windows::Forms::TextBox());
			this->TBHeight = (gcnew System::Windows::Forms::TextBox());
			this->CBProportions = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(12, 108);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Abbrechen";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button2->Location = System::Drawing::Point(144, 108);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"OK";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// TBWidth
			// 
			this->TBWidth->Location = System::Drawing::Point(13, 12);
			this->TBWidth->Name = L"TBWidth";
			this->TBWidth->Size = System::Drawing::Size(100, 20);
			this->TBWidth->TabIndex = 2;
			this->TBWidth->TextChanged += gcnew System::EventHandler(this, &BMPScale::TBWidth_TextChanged);
			this->TBWidth->Enter += gcnew System::EventHandler(this, &BMPScale::TBWidth_Enter);
			this->TBWidth->Leave += gcnew System::EventHandler(this, &BMPScale::TBWidth_Leave);
			// 
			// TBHeight
			// 
			this->TBHeight->Location = System::Drawing::Point(119, 12);
			this->TBHeight->Name = L"TBHeight";
			this->TBHeight->Size = System::Drawing::Size(100, 20);
			this->TBHeight->TabIndex = 3;
			this->TBHeight->TextChanged += gcnew System::EventHandler(this, &BMPScale::TBHeight_TextChanged);
			this->TBHeight->Enter += gcnew System::EventHandler(this, &BMPScale::TBHeight_Enter);
			this->TBHeight->Leave += gcnew System::EventHandler(this, &BMPScale::TBHeight_Leave);
			// 
			// CBProportions
			// 
			this->CBProportions->AutoSize = true;
			this->CBProportions->Checked = true;
			this->CBProportions->CheckState = System::Windows::Forms::CheckState::Checked;
			this->CBProportions->Location = System::Drawing::Point(46, 59);
			this->CBProportions->Name = L"CBProportions";
			this->CBProportions->Size = System::Drawing::Size(144, 17);
			this->CBProportions->TabIndex = 4;
			this->CBProportions->Text = L"Proportionen beibehalten";
			this->CBProportions->UseVisualStyleBackColor = true;
			this->CBProportions->CheckedChanged += gcnew System::EventHandler(this, &BMPScale::CBProportions_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(186, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Höhe";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 39);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(34, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Breite";
			// 
			// BMPScale
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(233, 143);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->CBProportions);
			this->Controls->Add(this->TBHeight);
			this->Controls->Add(this->TBWidth);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"BMPScale";
			this->Text = L"Scale";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CBProportions_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TBWidth_TextChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TBHeight_TextChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TBWidth_Enter(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TBWidth_Leave(System::Object^  sender, System::EventArgs^  e);
	private: System::Void TBHeight_Enter(System::Object^  sender, System::EventArgs^  e);
    private: System::Void TBHeight_Leave(System::Object^  sender, System::EventArgs^  e);
};
}
