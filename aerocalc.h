#ifndef _AEROCALC_
#define _AEROCALC_
#include <iostream>

// Default values
constexpr float WINGSPAN = 1200.0f;
constexpr float FUSELENMODIFIER = 0.75f;
constexpr float WINGROOTCHORDMODIFIER = 0.1667f;
constexpr float WINGTIPCHORDMODIFIER = 1.0f;
constexpr float HSTABAREAMODIFIER = 0.225f;
constexpr float VSTABAREAMODIFIER = 0.1125f;
constexpr float WEIGHT = 1000.0f;

// Struct to hold plane dimensions
struct PlaneSettings
{
	float wingspan;
	float fuseLenModifier;
	float wingRootChordModifier;
	float wingTipChordModifier;
	float hStabAreaModifier;
	float vStabAreaModifier;
	float weight;

	/*
	* Wingspan, FuselageLengthModifier, WingRootChordModifier, WingTipChordModifier, Weight
	* Defaults:
	* Wingspan = 1200 mm
	* FuselageLength = FuseLenModifier(0...1) is 75% of wingspan
	* WingRootChord = WingRootChordModifier(0...1) is 16.67% of wingspan or 1/6 of wingspan
	* WingTipChord = WingTipChordModifier(0...1) is 100% of wingRootChord
	* HorizontalStabArea = HStabAreaModifier(0...1) is 22.5% of winspan area
	* VerticalStabArea = VStabAreaModifier(0...1) is 11.25% of winspan area
	* Weight = 1000 grams (Estimate used for approximating wing load)
	*/
	PlaneSettings(float _wingspan = WINGSPAN, float _fuseLenModifier = FUSELENMODIFIER,
		float _wingRootChordModifier = WINGROOTCHORDMODIFIER, float _wingTipChordModifier = WINGTIPCHORDMODIFIER,
		float _hStabAreaModifier = HSTABAREAMODIFIER, float _vStabAreaModifier = VSTABAREAMODIFIER, float _weight = WEIGHT)
		:wingspan(_wingspan), fuseLenModifier(_fuseLenModifier), wingRootChordModifier(_wingRootChordModifier),
		wingTipChordModifier(_wingTipChordModifier), hStabAreaModifier(_hStabAreaModifier), vStabAreaModifier(_vStabAreaModifier), weight(_weight) {}
};

class AeroCalc
{
public:
	AeroCalc(PlaneSettings _planeSettings = PlaneSettings());
	friend std::ostream& operator<<(std::ostream& os, const AeroCalc& obj);

private:
	float wingspan;	// Length of wing * 2
	float wingRootChord;	// Wing root chord
	float wingTipChord; // Wing tip chord
	float aileronSurfArea;	// Area of 1 aileron. 6% of total wing surface area for barn door type and 4% for strip type
	float aileronChord;	// 25% of wing chord for barn door type and 10% for strip type
	float aileronLen;	// Aileron length
	float averageMeanChord; // Average mean chord i.e. (root chord + tip chord) / 2
	float aspectRatio;	// Wing to chord ratio
	float wingSurfArea;	// Total wing surface area
	float fuseLen;	// Fuselage length(inches) from back of prop washer to vertical stabilizer hinge line
	float weight;	// Airplane weight(grams)
	float noseLen;	// Nose length i.e. back of prop washer to wing leading edge
	float tailLen;	// Tail length i.e. wing trailing edge to vertical stabilizer hinge line
	float hStabArea;	// Horizontal stabilizer total surface area
	float hStabSpan;	// Horizontal stabilizer length
	float hStabChord;	// Horizontal stabilizer chord
	float vStabArea;	// Vertical stabilizer total area
	float vStabHeight;	// Vertical stabilizer height
	float vStabWidth;	// Vertical stabilizer width
	float elevChord;	// Elevator chord
	float rudWidth;	// Rudder width
	float wingLoad;	// Wing load i.e. airplane weight(in oz) divided by wing surface area(in square ft)
	std::string wLoad;	// wing load category i.e. very low, low, moderate, high, very high
	std::string AR;	// aspect ratio i.e. low, mid and high
};
#endif