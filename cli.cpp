#include "cli.h"
#include <format>
#include <string>
#include <sstream>
#define DISPLAY(txt) cout << (txt);

using namespace std;

string helpTxt =
"Usage: "
"\tAeroCalc [option] [...params]"
"\n\tAeroCalc [Wingspan] [FuselageLengthModifier] [WingRootChordModifier] [WingTipChordModifier] [HStabAreaModifier] [vStabAreaModifier] [Weight]"
"\nOptions:"
"\n-h, --help\t\t\tPrint command line options"
"\n-w, --wingload\t\t\tCalculate wingload for a given weight, wingpspan, and average mean chord parameters."
"\n\nRunning program without arguments uses default values for airplane settings"
"\nWeight values are in grams and length values are in millimeters";

StatusCode cli(int argc, char* argv[], PlaneSettings& _planeSettings)
{
	if (argc > 8)
	{
		cerr << "Arguments cannot exceed 7" << endl;
		DISPLAY(helpTxt);
		return StatusCode::INVALID_ARG_COUNT;
	}

	try
	{
		switch (argc)
		{
		case 1:
		{
			DISPLAY(
				"Enter plane dimensions."
				"\nLength modifiers are in percentages(0..1), wingspan is in millimeters and weight is in grams."
				"\nLeave input blank and press enter key to use default values."
				"\n");
			string input;
			float ws = getInput("Winspan", WINGSPAN);
			float flm = getInput("FuselageLengthModifier", FUSELENMODIFIER);
			float wrcm = getInput("WingRootChordModifier", WINGROOTCHORDMODIFIER);
			float wtcm = getInput("WingTipChordModifier", WINGTIPCHORDMODIFIER);
			float hsam = getInput("HStabAreaModifier", HSTABAREAMODIFIER);
			float vsam = getInput("VStabAreaModifier", VSTABAREAMODIFIER);
			float w = getInput("Weight", WEIGHT);

			_planeSettings = PlaneSettings(ws, flm, wrcm, wtcm, hsam, vsam, w);
			break;
		}
		case 2:
		{
			string arg = argv[1];

			if (arg == "--help" || arg == "-h")
			{
				DISPLAY(helpTxt);
				return StatusCode::HELP;
			}

			if (arg == "--version" || arg == "-v")
			{
				DISPLAY(AEROCALC_VERSION);
				return StatusCode::NO_OP;
			}

			float wingspan = stof(arg);
			_planeSettings = PlaneSettings(wingspan);
			break;
		}
		case 3:
		{
			float wingspan = stof(argv[1]);
			float fuseLenModifier = stof(argv[2]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier);
			break;
		}
		case 4:
		{
			float wingspan = stof(argv[1]);
			float fuseLenModifier = stof(argv[2]);
			float wingRootChordModifier = stof(argv[3]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier);
			break;
		}
		case 5:
		{
			string arg = argv[1];

			if (arg == "--wingload" || arg == "-w")
			{
				wingLoad(stof(argv[2]), stof(argv[3]), stof(argv[4]));
				return StatusCode::NO_OP;
			}

			float wingspan = stof(argv[1]);
			float fuseLenModifier = stof(argv[2]);
			float wingRootChordModifier = stof(argv[3]);
			float wingTipChordModifier = stof(argv[4]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier);
			break;
		}
		case 6:
		{
			float wingspan = stof(argv[1]);
			float fuseLenModifier = stof(argv[2]);
			float wingRootChordModifier = stof(argv[3]);
			float wingTipChordModifier = stof(argv[4]);
			float hStabAreaModifier = stof(argv[5]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier);
			break;
		}
		case 7:
		{
			float wingspan = stof(argv[1]);
			float fuseLenModifier = stof(argv[2]);
			float wingRootChordModifier = stof(argv[3]);
			float wingTipChordModifier = stof(argv[4]);
			float hStabAreaModifier = stof(argv[5]);
			float vStabAreaModifier = stof(argv[6]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier, vStabAreaModifier);
			break;
		}
		case 8:
		{
			float wingspan = stof(argv[1]);
			float fuseLenModifier = stof(argv[2]);
			float wingRootChordModifier = stof(argv[3]);
			float wingTipChordModifier = stof(argv[4]);
			float hStabAreaModifier = stof(argv[5]);
			float vStabAreaModifier = stof(argv[6]);
			float weight = stof(argv[7]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier, vStabAreaModifier, weight);
			break;
		}
		default:
			break;
		}
	}
	catch (const invalid_argument& e)
	{
		(void)e;
		cerr << "Invalid option." << endl;
		DISPLAY(helpTxt);
		return StatusCode::INVALID_ARG;
	}

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
			for (char const& c : input)
			{
				valid = isdigit(c) || c == '.' || c == 'f';
				if (!valid) break;
			}

			if (valid) stringstream(input) >> value;
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