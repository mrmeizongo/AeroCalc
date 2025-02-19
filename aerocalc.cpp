#include <cmath>
#include "aerocalc.h"

AeroCalc::AeroCalc(PlaneSettings _planeSettings)
{
	wingspan = _planeSettings.wingspan;
	weight = _planeSettings.weight;
	wingRootChord = wingspan * _planeSettings.wingRootChordModifier;
	wingTipChord = wingRootChord * _planeSettings.wingTipChordModifier;
	averageMeanChord = (wingRootChord + wingTipChord) / 2.0f;
	aspectRatio = wingspan / averageMeanChord;
	wingSurfArea = wingspan * averageMeanChord;
	aileronSurfArea = 0.06f * wingSurfArea;
	aileronChord = 0.25f * averageMeanChord;
	aileronLen = aileronSurfArea / aileronChord;
	wingLoad = (weight / 28.35f) / (wingSurfArea / 92900);
	fuseLen = wingspan * _planeSettings.fuseLenModifier;
	noseLen = (fuseLen * 0.21f);
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

	if (wingLoad > 20)
		wLoad = "Very High";
	else if (wingLoad >= 16)
		wLoad = "High";
	else if (wingLoad >= 12)
		wLoad = "Moderate";
	else if (wingLoad >= 10)
		wLoad = "Low";
	else
		wLoad = "Very Low";

	if (aspectRatio > 12)
		AR = "High";
	else if (aspectRatio > 6)
		AR = "Moderate";
	else
		AR = "Low";
}

std::ostream& operator<<(std::ostream& os, const AeroCalc& obj) {
	os << "Plane Dimensions"
		<< "\n----------------"
		<< "\nWingspan: " << obj.wingspan << "mm"
		<< "\nFuselage length: " << obj.fuseLen << "mm"
		<< "\nNose length: " << obj.noseLen << "mm"
		<< "\nTail length: " << obj.tailLen << "mm"
		<< "\nAirplane weight: " << obj.weight << " grams"
		<< "\nWing root chord: " << obj.wingRootChord << "mm"
		<< "\nWing tip chord: " << obj.wingTipChord << "mm"
		<< "\nAverage mean chord: " << obj.averageMeanChord << "mm"
		<< "\nTotal wing surface area: " << obj.wingSurfArea << "sq/mm"
		<< "\nWing load: " << obj.wingLoad << " oz/ft^2" << " = " << obj.wLoad
		<< "\nAspect ratio: " << obj.aspectRatio << " = " << obj.AR
		<< "\nAileron chord: " << obj.aileronChord << "mm"
		<< "\nAileron length: " << obj.aileronLen << "mm"
		<< "\nAileron surface area: " << obj.aileronSurfArea << " sq/mm"
		<< "\nHorizontal stab span: " << obj.hStabSpan << "mm"
		<< "\nHorizontal stab chord: " << obj.hStabChord << "mm"
		<< "\nElevator chord: " << obj.elevChord << "mm"
		<< "\nHorizontal stab area: " << obj.hStabArea << "sq/mm"
		<< "\nVertical stab height: " << obj.vStabHeight << "mm"
		<< "\nVertical stab width: " << obj.vStabWidth << "mm"
		<< "\nRudder width: " << obj.rudWidth << "mm"
		<< "\nVertical stab area: " << obj.vStabArea << "sq/mm";
	return os;
}