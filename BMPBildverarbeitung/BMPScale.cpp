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

		if (EditWidth)
		{

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
}

System::Void BMPBildverarbeitung::BMPScale::TBHeight_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (IsLoaded) {

		if (EditHeight)
		{
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
}

System::Void BMPBildverarbeitung::BMPScale::TBWidth_Enter(System::Object ^ sender, System::EventArgs ^ e)
{
	EditWidth = true;
	EditHeight = false;
}

System::Void BMPBildverarbeitung::BMPScale::TBWidth_Leave(System::Object ^ sender, System::EventArgs ^ e)
{
	EditWidth = false;
	EditHeight = false;
}

System::Void BMPBildverarbeitung::BMPScale::TBHeight_Enter(System::Object ^ sender, System::EventArgs ^ e)
{
	EditWidth = false;
	EditHeight = true;
}

System::Void BMPBildverarbeitung::BMPScale::TBHeight_Leave(System::Object ^ sender, System::EventArgs ^ e)
{
	EditWidth = false;
	EditHeight = false;
}
