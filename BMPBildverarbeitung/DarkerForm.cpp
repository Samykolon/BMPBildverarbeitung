#include "DarkerForm.h"

System::Void BMPBildverarbeitung::DarkerForm::TDarker_ValueChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	TValue = TDarker->Value;
}

System::Void BMPBildverarbeitung::DarkerForm::TDarker_Scroll(System::Object ^ sender, System::EventArgs ^ e)
{
	double value;
	value = TDarker->Value;
	value /= 2.55;
	value = floor(value);
	TTTrackbar->SetToolTip(TDarker, (value.ToString()) + "%");
}
