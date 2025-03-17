#include "aerocalc.h"
#include <cmath>

// Helper function calculate mean aerodynamic chord (MAC)
static float calculateMAC(float root, float tip)
{
	float mac = (2.f / 3.f) * (((root + tip) - ((root * tip)/(root + tip))) / 1);
	return mac;
}

static float getMacLocation(float span, float root, float tip)
{
	float macLoc = (span / 6) * ((root + (2 * tip)) / (root + tip));
	return macLoc;
}

AeroCalc::AeroCalc(PlaneSettings _planeSettings)
{
	// Length measurements are in millimeters and weight is in grams
	// Wing calculations
	wingspan = _planeSettings.wingspan;	// Airplane wingspan
	weight = _planeSettings.weight;	// Airplane weight
	wingRootChord = wingspan * _planeSettings.wingRootChordModifier;	// Wing root chord length. Default modifier value is 16.67% of wingspan
	wingTipChord = wingRootChord * _planeSettings.wingTipChordModifier;	//Wing tip chord length. Default modifier value is 100% of wing root chord
	wingRootChord += wingRootChord - wingTipChord;	// Adjust the wing root chord to account for any taper to maintain the wing area
	wingMAC = calculateMAC(wingRootChord, wingTipChord);	// Mean aerodynamic chord length. This takes into account the root and tip chord length
	wingMACLoc = getMacLocation(wingspan, wingRootChord, wingTipChord);	// Location of the MAC
	cg = 0.25f * wingMAC;	// Center of gravity/ lift. This is calculated from the leading of wing to 25% of the wing mean aerodynamic chord
	wingSurfArea = wingspan * wingMAC;	// Total wing surface area
	wingLoad = (weight / 28.35f) / (wingSurfArea / 92900);	// Wing load. oz/ft^2
	aspectRatio = (float)std::pow(wingspan, 2) / wingSurfArea;	// Aspect ratio.  It's a measure of how long and narrow an airplane's wings are.

	// Aileron calculations
	aileronSurfArea = 0.05f * wingSurfArea;	// Aileron surface area. 5% of total wing surface area for each aileron
	float aileronChordModifier = 0.25f;	// Aileron chord modifier. 25% of wing MAC(default) for barn door type and 10% for strip type
	if (_planeSettings.aileronType == "-s" || _planeSettings.aileronType == "s")
		aileronChordModifier = 0.1f;
	aileronChord = aileronChordModifier * wingMAC;	// Aileron chord length
	aileronSpan = aileronSurfArea / aileronChord;	// Aileron span

	// Horizontal stabilizer calculations
	hStabArea = _planeSettings.hStabAreaModifier * wingSurfArea;	// Horizontal stabilizer area. Default modifier value is 22.5% of wing area
	hStabRootChord = sqrtf((hStabArea / 3));	// Horizontal stabilizer root chord is square root of 1/3 the total horizontal stabilizer area
	hStabTipChord = hStabRootChord * _planeSettings.hStabTipChordModifier;	// Horizontal stabilizer tip chord. The modifier value can used to taper the horizontal stabilizer
	hStabRootChord += hStabRootChord - hStabTipChord;	// Adjust the horizontal stabilizer root chord to account for any taper to maintain the horizontal stab area
	hStabMAC = calculateMAC(hStabRootChord, hStabTipChord);	// Horizontal stabilizer mean aerodynamic chord
	hStabSpan = hStabArea / hStabMAC;	// Horizontal stabilizer span
	hStabMACLoc = getMacLocation(hStabSpan, hStabRootChord, hStabTipChord);	// Location of the MAC
	elevChord = 0.25f * hStabRootChord;	// Elevator chord. 25% of horizontal stabilizer root chord

	// Fuselage calculations
	fuseLen = wingspan * _planeSettings.fuseLenModifier;	// Fuselage length. Default modifier value is 70% of wingspan
	noseLen = (fuseLen * _planeSettings.noseLenModifier);	// Nose length. Default modifier value is 21% of fuselage length 
	noseMoment = noseLen + (wingMAC * 0.25f);	// Nose moment arm. Back of prop to 25% forward of wing aerodynamic mean chord
	tailLen = fuseLen - (noseLen + wingRootChord);	// Tail length. Wing trailing edge to vertical stabilizer hinge line

	// Vertical stabilizer calculations
	vStabArea = _planeSettings.vStabAreaModifier * hStabArea;	// Vertical stabilizer area. Default modifier value is 50% of horizontal stab area
	vStabWidth = 1.1f * sqrtf(vStabArea);	// Vertical stabilizer width. 1.1 times the square root of the total vertical stabilizer area
	vStabHeight = vStabArea / vStabWidth;	// Vertical stabilizer height
	rudWidth = vStabWidth / 2.0f;	// Rudder width. Half of vertical stabilizer width for a little extra rudder authority

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

	if (aspectRatio > 12)
		AR = "High";
	else if (aspectRatio > 6)
		AR = "Moderate";
	else
		AR = "Low";
}

ostream& operator<<(ostream& os, const AeroCalc& obj) {
	os << "\nPlane Dimensions"
		<< "\n----------------"
		<< "\nWingspan: " << obj.wingspan << "mm"
		<< "\nFuselage length: " << obj.fuseLen << "mm"
		<< "\nNose length: " << obj.noseLen << "mm"
		<< "\nNose Moment: " << obj.noseMoment << "mm"
		<< "\nTail length: " << obj.tailLen << "mm"
		<< "\nAirplane weight: " << obj.weight << " grams"
		<< "\nWing root chord: " << obj.wingRootChord << "mm"
		<< "\nWing tip chord: " << obj.wingTipChord << "mm"
		<< "\nWing mean aerodynamic chord: " << obj.wingMAC << "mm"
		<< "\nWing mean aerodynamic chord location from root: " << obj.wingMACLoc << "mm"
		<< "\nCenter of gravity: " << obj.cg << "mm"
		<< "\nTotal wing surface area: " << obj.wingSurfArea << "sq/mm"
		<< "\nWing load: " << obj.wingLoad << "oz/ft^2" << " = " << obj.wLoad
		<< "\nAspect ratio: " << (int)obj.aspectRatio << ":1"  << " = " << obj.AR
		<< "\nAileron chord: " << obj.aileronChord << "mm"
		<< "\nAileron length: " << obj.aileronSpan << "mm"
		<< "\nAileron surface area: " << obj.aileronSurfArea << " sq/mm"
		<< "\nHorizontal stab span: " << obj.hStabSpan << "mm"
		<< "\nHorizontal stab root chord: " << obj.hStabRootChord << "mm"
		<< "\nHorizontal stab tip chord: " << obj.hStabTipChord << "mm"
		<< "\nHorizontal stab mean aerodynamic chord: " << obj.hStabMAC << "mm"
		<< "\nHorizontal stab mean aerodynamic chord location from root: " << obj.hStabMACLoc << "mm"
		<< "\nHorizontal stab area: " << obj.hStabArea << "sq/mm"
		<< "\nElevator chord: " << obj.elevChord << "mm"
		<< "\nVertical stab height: " << obj.vStabHeight << "mm"
		<< "\nVertical stab width: " << obj.vStabWidth << "mm"
		<< "\nRudder width: " << obj.rudWidth << "mm"
		<< "\nVertical stab area: " << obj.vStabArea << "sq/mm";
	return os;
}