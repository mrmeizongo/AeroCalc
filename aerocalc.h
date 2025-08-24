#ifndef _AEROCALC_
#define _AEROCALC_
#include <iostream>
#include <string>
using std::string;
using std::ostream;

#define AEROCALC_VERSION "1.0.0"

// Default values
#define AILERONTYPE "-b"
#define WINGSPAN 1200.0f
#define FUSELENMODIFIER 0.7f
#define NOSELENMODIFIER 0.25f
#define WINGROOTCHORDMODIFIER 0.1667f
#define WINGTIPCHORDMODIFIER 1.0f
#define HSTABAREAMODIFIER 0.225f
#define HSTABTIPCHORDMODIFIER 1.0f
#define VSTABAREAMODIFIER 0.5f
#define WEIGHT 1000.0f

// Struct to hold plane dimensions
struct PlaneSettings
{
	string aileronType;
	float wingspan;
	float fuseLenModifier;
	float noseLenModifier;
	float wingRootChordModifier;
	float wingTipChordModifier;
	float hStabTipChordModifier;
	float hStabAreaModifier;
	float vStabAreaModifier;
	float weight;

	/*
	* AileronType, Wingspan, FuselageLengthModifier, WingRootChordModifier, WingTipChordModifier, Weight
	* Defaults:
	* AileronType = -b
	* Wingspan = 1200 mm
	* FuselageLength = FuseLenModifier(0...1) is 75% of wingspan
	* NoseLength = NoseLenModifier(0...1) is 21% of fuselage length
	* WingRootChord = WingRootChordModifier(0...1) is 16.67% of wingspan or 1/6 of wingspan
	* WingTipChord = WingTipChordModifier(0...1) is 100% of wingRootChord
	* HorizontalStabArea = HStabAreaModifier(0...1) is 22.5% of winspan area
	* VerticalStabArea = VStabAreaModifier(0...1) is 11.25% of winspan area
	* Weight = 1000 grams (Estimate used for approximating wing load)
	*/
	PlaneSettings()
		: aileronType(""), wingspan(0.f), fuseLenModifier(0.f),
		noseLenModifier(0.f), wingRootChordModifier(0.f),
		wingTipChordModifier(0.f), hStabTipChordModifier(0.f),
		hStabAreaModifier(0.f), vStabAreaModifier(0.f), weight(0.f) {
	}

	PlaneSettings(string _aileronType, float _wingspan, float _fuseLenModifier, float _noseLenModifier,
		float _wingRootChordModifier, float _wingTipChordModifier, float _hStabTipChordModifier,
		float _hStabAreaModifier, float _vStabAreaModifier, float _weight)
		: aileronType(_aileronType), wingspan(_wingspan), fuseLenModifier(_fuseLenModifier),
		noseLenModifier(_noseLenModifier), wingRootChordModifier(_wingRootChordModifier),
		wingTipChordModifier(_wingTipChordModifier), hStabTipChordModifier(_hStabTipChordModifier),
		hStabAreaModifier(_hStabAreaModifier), vStabAreaModifier(_vStabAreaModifier), weight(_weight) {
	}
};

class AeroCalc
{
public:
	AeroCalc(PlaneSettings _planeSettings = PlaneSettings());
	friend ostream& operator<<(ostream& os, const AeroCalc& obj);

private:
	float wingspan;	// Length of wing * 2
	float wingRootChord;	// Wing root chord
	float wingTipChord; // Wing tip chord
	float aileronSurfArea;	// Area of 1 aileron. 6% of total wing surface area for barn door type and 4% for strip type
	float aileronChord;	// 25% of wing chord for barn door type and 10% for strip type
	float aileronSpan;	// Aileron span
	float wingMAC; // Mean aerodynamic chord i.e. (root chord + tip chord) / 2
	float wingMACLoc;	// Where on the span the MAC is located
	float cg;	// Center of gravity i.e. from leading edge of wing to 25% of wing mean aerodynamic chord
	float aspectRatio;	// Wing to chord ratio
	float wingSurfArea;	// Total wing surface area
	float fuseLen;	// Fuselage length(inches) from back of prop washer to vertical stabilizer hinge line
	float weight;	// Airplane weight(grams)
	float noseLen;	// Nose length i.e. back of prop washer to wing leading edge
	float noseMoment;	// Nose moment arm i.e. back of prop washer to 1/4(25%) forward of wing aerodynamic mean chord
	float tailLen;	// Tail length i.e. wing trailing edge to vertical stabilizer hinge line
	float hStabArea;	// Horizontal stabilizer total surface area
	float hStabSpan;	// Horizontal stabilizer length
	float hStabRootChord;	// Horizontal stabilizer root chord
	float hStabTipChord;	// Horizontal stabilizer tip chord
	float hStabMAC;	// Horizontal stabilizer mean aerodynamic chord
	float hStabMACLoc;	// Where on the span the MAC is loacted
	float vStabArea;	// Vertical stabilizer total area
	float vStabHeight;	// Vertical stabilizer height
	float vStabWidth;	// Vertical stabilizer width
	float elevChord;	// Elevator chord
	float rudWidth;	// Rudder width
	float wingLoad;	// Wing load i.e. airplane weight(in oz) divided by wing surface area(in square ft)
	string wLoad;	// wing load category i.e. very low, low, moderate, high, very high
	string AR;	// aspect ratio i.e. low, mid and high
};
#endif