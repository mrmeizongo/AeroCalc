#include "cli.h"
#include <format>
#include <string>
#include <sstream>
using namespace std;

#define DISPLAY(txt) cout << (txt);

string helpTxt =
"\nUsage: "
"\tAeroCalc [option] [...params]"
"\n\tAeroCalc [AileronType] [Wingspan] [FuselageLengthModifier] [NoseLengthModifier] [WingRootChordModifier] [WingTipChordModifier] [HStabAreaModifier] [vStabAreaModifier] [Weight]"
"\nOptions:"
"\n-h, --help\t\t\tPrint command line options"
"\n-w, --wingload\t\t\tCalculate wingload for a given weight, wingpspan, and average mean chord parameters."
"\n-b, b\t\t\t\tSpecify barn type ailerons. Can be used in conjunction with weight and length parameters."
"\n-s, s\t\t\t\tSpecify strip type ailerons. Can be used in conjunction with weight and length parameters."
"\n\nRunning program without arguments uses default values for airplane settings"
"\nWeight values are in grams and length values are in millimeters";

StatusCode cli(int argc, char* argv[], PlaneSettings& _planeSettings)
{
	// C++ programs start with argc being at least 1, and argv[0] being the program name
	// Therefore there is no point in checking for argc <= 0
	if (argc > 11)
	{
		cerr << "Arguments cannot exceed 9" << endl;
		DISPLAY(helpTxt);
		return StatusCode::INVALID_ARG_COUNT;
	}

	string atype = AILERONTYPE;
	float ws = WINGSPAN;
	float flm = FUSELENMODIFIER;
	float nlm = NOSELENMODIFIER;
	float wrcm = WINGROOTCHORDMODIFIER;
	float wtcm = WINGTIPCHORDMODIFIER;
	float hstcm = HSTABTIPCHORDMODIFIER;
	float hsam = HSTABAREAMODIFIER;
	float vsam = VSTABAREAMODIFIER;
	float w = WEIGHT;

	if (argc == 1)
	{
		DISPLAY(
			"Enter plane dimensions."
			"\nLength modifiers are in percentages(0..1), wingspan is in millimeters and weight is in grams."
			"\nLeave input blank and press enter key to use default values."
			"\n");
		atype = getInput("AileronType", atype);
		ws = getInput("Winspan", ws);
		flm = getInput("FuselageLengthModifier", flm);
		nlm = getInput("NoseLengthModifier", nlm);
		wrcm = getInput("WingRootChordModifier", wrcm);
		wtcm = getInput("WingTipChordModifier", wtcm);
		hstcm = getInput("HStabTipChordModifier", hstcm);
		hsam = getInput("HStabAreaModifier", hsam);
		vsam = getInput("VStabAreaModifier", vsam);
		w = getInput("Weight", w);
	}
	else
	{
		try
		{
			if (argc > 1)
			{
				string arg = argv[1];
				if (arg.compare("--help") == 0 || arg.compare("-h") == 0)
				{
					DISPLAY(helpTxt);
					return StatusCode::HELP;
				}
				if (arg.compare("--version") == 0 || arg.compare("-v") == 0)
				{
					DISPLAY(AEROCALC_VERSION);
					return StatusCode::NO_OP;
				}
				if (arg.compare("-b") != 0 && arg.compare("b") != 0 && arg.compare("-s") != 0 && arg.compare("b") != 0)
				{
					DISPLAY(helpTxt);
					return StatusCode::INVALID_ARG;
				}
				atype = arg;
			}
			if (argc > 2)
				ws = stof(argv[2]);
			if (argc > 3)
				flm = stof(argv[3]);
			if (argc > 4)
				nlm = stof(argv[4]);
			if (argc > 5)
				wrcm = stof(argv[5]);
			if (argc > 6)
				wtcm = stof(argv[6]);
			if (argc > 7)
				hstcm = stof(argv[7]);
			if (argc > 8)
				hsam = stof(argv[8]);
			if (argc > 9)
				vsam = stof(argv[9]);
			if (argc > 10)
				w = stof(argv[10]);
		}
		catch (const invalid_argument& e)
		{
			(void)e;
			cerr << "Invalid option." << endl;
			DISPLAY(helpTxt);
			return StatusCode::INVALID_ARG;
		}
	}

	_planeSettings = PlaneSettings(atype, ws, flm, nlm, wrcm, wtcm, hstcm, hsam, vsam, w);
	return StatusCode::OK;
}

float getInput(string textToDisplay, float defaultValue)
{
	float value;
	bool valid = false;
	while (!valid)
	{
		DISPLAY(format("{}({}): ", textToDisplay, defaultValue));
		string input;
		getline(cin, input);
		if (input.empty())
		{
			value = defaultValue;
			valid = true;
		}
		else
		{
			try
			{
				value = stof(input);
				valid = true;
			}
			catch (const invalid_argument& e)
			{
				(void)e;
				valid = false;
			}
		}
	}
	return value;
}

string getInput(string textToDisplay, string defaultValue)
{
	string value;
	bool valid = false;
	while (!valid)
	{
		DISPLAY(format("{}({}): ", textToDisplay, defaultValue));
		string input;
		getline(cin, input);
		if (input.empty())
		{
			value = defaultValue;
			valid = true;
		}
		else
		{
			if (input.compare("-b") == 0 || input.compare("b") == 0 || input.compare("-s") == 0 || input.compare("s") == 0)
			{
				value = input;
				valid = true;
			}
		}
	}
	return value;
}

void wingLoad(float weight, float wingspan, float averageMC)
{
	float wingSurfArea = wingspan * averageMC;
	float wingLoad = (weight / 28.35f) / (wingSurfArea / 92900);
	string wLoad;
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
	DISPLAY(format("Wing load: {:.2f}oz/ft^2 = {}", wingLoad, wLoad));
}