#include "cli.h"
#include <string>
#include <sstream>

std::string helpTxt = "Usage: "
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
		std::cerr << "Arguments cannot exceed 7" << std::endl;
		std::cout << helpTxt << std::endl;
		return StatusCode::INVALID_ARG_COUNT;
	}

	try
	{
		switch (argc)
		{
		case 1:
		{
			std::cout << "Enter plane dimensions"
				<< "\nLength modifiers are in percentages(0..1), wingspan is in millimeters and weight is in grams"
				<< "\nLeave input blank and press enter key to use default values"
				<< std::endl;
			std::string input;
			float ws = getInput("Winspan", WINGSPAN);
			float flm = getInput("FuselageLengthModifier", FUSELENMODIFIER);
			float wrcm = getInput("WingRootChordModifier", WINGROOTCHORDMODIFIER);
			float wtcm = getInput("WingTipChordModifier", WINGTIPCHORDMODIFIER);
			float hsam = getInput("HStabAreaModifier", HSTABAREAMODIFIER);
			float vsam = getInput("VStabAreaModifier", VSTABAREAMODIFIER);
			float w = getInput("Weight", WEIGHT);

			std::cout << std::endl;

			_planeSettings = PlaneSettings(ws, flm, wrcm, wtcm, hsam, vsam, w);
			break;
		}
		case 2:
		{
			std::string arg = argv[1];

			if (arg == "--help" || arg == "-h")
			{
				std::cout << helpTxt << std::endl;
				return StatusCode::HELP;
			}

			float wingspan = std::stof(argv[1]);
			_planeSettings = PlaneSettings(wingspan);
			break;
		}
		case 3:
		{
			float wingspan = std::stof(argv[1]);
			float fuseLenModifier = std::stof(argv[2]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier);
			break;
		}
		case 4:
		{
			float wingspan = std::stof(argv[1]);
			float fuseLenModifier = std::stof(argv[2]);
			float wingRootChordModifier = std::stof(argv[3]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier);
			break;
		}
		case 5:
		{
			std::string arg = argv[1];

			if (arg == "--wingload" || arg == "-w")
			{
				float weight = std::stof(argv[2]);
				float wingspan = std::stof(argv[3]);
				float averageMeanChord = std::stof(argv[4]);
				float wingSurfArea = wingspan * averageMeanChord;
				float wingLoad = (weight / 28.35f) / (wingSurfArea / 92900);
				std::string wLoad;
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
				std::cout << "Wing load: " << wingLoad << " oz/ft^2 = " << wLoad << std::endl;
				return StatusCode::NO_OP;
			}

			float wingspan = std::stof(argv[1]);
			float fuseLenModifier = std::stof(argv[2]);
			float wingRootChordModifier = std::stof(argv[3]);
			float wingTipChordModifier = std::stof(argv[4]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier);
			break;
		}
		case 6:
		{
			float wingspan = std::stof(argv[1]);
			float fuseLenModifier = std::stof(argv[2]);
			float wingRootChordModifier = std::stof(argv[3]);
			float wingTipChordModifier = std::stof(argv[4]);
			float hStabAreaModifier = std::stof(argv[5]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier);
			break;
		}
		case 7:
		{
			float wingspan = std::stof(argv[1]);
			float fuseLenModifier = std::stof(argv[2]);
			float wingRootChordModifier = std::stof(argv[3]);
			float wingTipChordModifier = std::stof(argv[4]);
			float hStabAreaModifier = std::stof(argv[5]);
			float vStabAreaModifier = std::stof(argv[6]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier, vStabAreaModifier);
			break;
		}
		case 8:
		{
			float wingspan = std::stof(argv[1]);
			float fuseLenModifier = std::stof(argv[2]);
			float wingRootChordModifier = std::stof(argv[3]);
			float wingTipChordModifier = std::stof(argv[4]);
			float hStabAreaModifier = std::stof(argv[5]);
			float vStabAreaModifier = std::stof(argv[6]);
			float weight = std::stof(argv[7]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier, vStabAreaModifier, weight);
			break;
		}
		default:
			break;
		}
	}
	catch (const std::invalid_argument& e)
	{
		(void)e;
		std::cerr << "Invalid option." << std::endl;
		std::cout << helpTxt << std::endl;
		return StatusCode::INVALID_ARG;
	}

	return StatusCode::OK;
}

float getInput(std::string textToDisplay, float defaultValue)
{
	float value;
	bool valid = false;
	while (!valid)
	{
		std::cout << textToDisplay << "(" << defaultValue << "): ";
		std::string input;
		std::getline(std::cin, input);
		if (input.empty())
		{
			value = defaultValue;
			valid = true;
		}
		else
		{
			for (char const& c : input)
			{
				valid = std::isdigit(c) || c == '.' || c == 'f';
				if (!valid) break;
			}

			if (valid) std::stringstream(input) >> value;
		}
	}
	return value;
}