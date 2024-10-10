#include "aerocalc.h"
#include <cmath>

AeroCalc::AeroCalc(PlaneSettings _planeSettings)
{
	wingspan = _planeSettings.wingspan;
	weight = _planeSettings.weight;
	wingRootChord = wingspan * _planeSettings.wingRootChordModifier;
	wingTipChord = wingRootChord * _planeSettings.wingTipChordModifier;
	averageMeanChord = (wingRootChord + wingTipChord) / 2.0f;
	aspectRatio = wingspan / averageMeanChord;
	wingSurfArea = wingspan * averageMeanChord;
	wingLoad = (weight / 28.35f) / (wingSurfArea / 144);
	fuseLen = wingspan * _planeSettings.fuseLenModifier;
	noseLen = (fuseLen * 0.21f) - (0.25f * averageMeanChord);
	tailLen = fuseLen - (noseLen + wingRootChord);
	hStabArea = _planeSettings.hStabAreaModifier * wingSurfArea;
	float tempH = hStabArea / 3;
	hStabChord = sqrtf(tempH);
	hStabSpan = hStabArea / hStabChord;
	vStabArea = _planeSettings.vStabAreaModifier * wingSurfArea;
	vStabWidth = 1.1f * sqrtf(vStabArea);
	vStabHeight = vStabArea / vStabWidth;
	elevChord = 0.25f * hStabChord;
	rudWidth = vStabWidth / 2.0f;

	if (wingLoad < 10)
		wLoad = "Very Low";
	else if (wingLoad >= 10 && wingLoad <= 12)
		wLoad = "Low";
	else if (wingLoad > 12 && wingLoad < 16)
		wLoad = "Moderate";
	else if (wingLoad >= 16 && wingLoad <= 20)
		wLoad = "High";
	else
		wLoad = "Very High";
}

std::ostream& operator<<(std::ostream& os, const AeroCalc& obj) {
	os << "Plane Dimensions"
		<< "\n----------------"
		<< "\nWingspan: " << obj.wingspan << " inches"
		<< "\nFuselage length: " << obj.fuseLen << " inches"
		<< "\nAirplane weight: " << obj.weight << " grams"
		<< "\nWing load: " << obj.wingLoad << " oz/ft^2" << " = " << obj.wLoad
		<< "\nWing root chord: " << obj.wingRootChord << " inches"
		<< "\nWing tip chord: " << obj.wingTipChord << " inches"
		<< "\nAverage mean chord: " << obj.averageMeanChord << " inches"
		<< "\nTotal wing surface area: " << obj.wingSurfArea << " square inches"
		<< "\nAspect ratio: " << obj.aspectRatio
		<< "\nHorizontal stab area: " << obj.hStabArea
		<< "\nHorizontal stab span: " << obj.hStabSpan
		<< "\nHorizontal stab chord: " << obj.hStabChord
		<< "\nElevator chord: " << obj.elevChord
		<< "\nVertical stab area: " << obj.vStabArea
		<< "\nVertical stab height: " << obj.vStabHeight
		<< "\nVertical stab width: " << obj.vStabWidth
		<< "\nRudder width: " << obj.rudWidth;
	return os;
}