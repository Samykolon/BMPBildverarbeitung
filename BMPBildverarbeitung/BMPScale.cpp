#include "BMPScale.h"

System::Void BMPBildverarbeitung::BMPScale::CBProportions_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (CBProportions->Checked == true)
		CheckBoxChecked = true;
	else
		CheckBoxChecked = false;
}

System::Void BMPBildverarbeitung::BMPScale::TBWidth_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (IsLoaded) {

		try
		{
			if (CheckBoxChecked)
			{
				Width = System::Convert::ToDouble(TBWidth->Text);
				Height = Width / Proportions;
				Height = floor(Height);
				TBHeight->Text = Height.ToString();
			}
			else
				Width = System::Convert::ToDouble(TBWidth->Text);
		}
		catch (Exception^ ex) {}
	}
}

System::Void BMPBildverarbeitung::BMPScale::TBHeight_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (IsLoaded) {
		try
		{
			if (CheckBoxChecked)
			{
				Height = System::Convert::ToDouble(TBHeight->Text);
				Width = Height * Proportions;
				Width = floor(Width);
				TBWidth->Text = Width.ToString();
			}
			else
				Height = System::Convert::ToDouble(TBHeight->Text);
		}
		catch (Exception^ ex) {}
	}
}
