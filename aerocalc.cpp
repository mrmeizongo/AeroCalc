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
	wingLoad = (weight / 28.35f) / (wingSurfArea / 92900);
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
		<< "\nWingspan: " << obj.wingspan << "mm"
		<< "\nFuselage length: " << obj.fuseLen << "mm"
		<< "\nNose length: " << obj.noseLen << "mm"
		<< "\nTail length: " << obj.tailLen << "mm"
		<< "\nAirplane weight: " << obj.weight << " grams"
		<< "\nWing load: " << obj.wingLoad << " oz/ft^2" << " = " << obj.wLoad
		<< "\nWing root chord: " << obj.wingRootChord << "mm"
		<< "\nWing tip chord: " << obj.wingTipChord << "mm"
		<< "\nAverage mean chord: " << obj.averageMeanChord << "mm"
		<< "\nTotal wing surface area: " << obj.wingSurfArea << "sq/mm"
		<< "\nAspect ratio: " << obj.aspectRatio
		<< "\nHorizontal stab area: " << obj.hStabArea << "sq/mm"
		<< "\nHorizontal stab span: " << obj.hStabSpan << "mm"
		<< "\nHorizontal stab chord: " << obj.hStabChord << "mm"
		<< "\nElevator chord: " << obj.elevChord << "mm"
		<< "\nVertical stab area: " << obj.vStabArea << "sq/mm"
		<< "\nVertical stab height: " << obj.vStabHeight << "mm"
		<< "\nVertical stab width: " << obj.vStabWidth << "mm"
		<< "\nRudder width: " << obj.rudWidth << "mm";
	return os;
}