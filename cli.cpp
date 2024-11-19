#include "cli.h"
#include <string>

std::string helpTxt = "Usage:\tAeroCalc [option] [...params]"
"\n\tAeroCalc [Wingspan] [FuselageLengthModifier] [WingRootChordModifier] [WingTipChordModifier] [HStabAreaModifier] [vStabAreaModifier] [Weight]"
"\nOptions:"
"\n-h, --help\t\t\tPrint command line options"
"\n-w, --wingload\t\t\tCalculate wingload for a given weight, wingpspan, and average mean chord parameters"
"\n\nRunning program without arguments uses default values for airplane settings"
"\nWeight values are in grams and length values are in millimeters";


bool cli(int argc, char* argv[], PlaneSettings& _planeSettings)
{
	std::string arg = argv[1];
	if (arg == "--help" || arg == "-h")
	{
		std::cout << helpTxt << std::endl;
		return false;
	}
	else if (arg == "--wingload" || arg == "-w")
	{
		if (argc != 5)
		{
			std::cout << helpTxt << std::endl;
			return false;
		}
		float weight = (float)std::atof(argv[2]);
		float wingspan = (float)std::atof(argv[3]);
		float averageMeanChord = (float)std::atof(argv[4]);
		float wingSurfArea = wingspan * averageMeanChord;
		float wingLoad = (weight / 28.35f) / (wingSurfArea / 144);
		std::cout << "Wing load: " << wingLoad << " oz/ft^2" << std::endl;
		return false;
	}
	else if (argc > 8)
	{
		std::cerr << "Arguments cannot exceed 7" << std::endl;
		std::cout << helpTxt << std::endl;
		return false;
	}
	else
	{
		//std::string aileronType = argv[1];
		// TODO aileron

		switch (argc)
		{
		case 2:
		{
			float wingspan = (float)std::atof(argv[1]);
			_planeSettings = PlaneSettings(wingspan);
			break;
		}
		case 3:
		{
			float wingspan = (float)std::atof(argv[1]);
			float fuseLenModifier = (float)std::atof(argv[2]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier);
			break;
		}
		case 4:
		{
			float wingspan = (float)std::atof(argv[1]);
			float fuseLenModifier = (float)std::atof(argv[2]);
			float wingRootChordModifier = (float)std::atof(argv[3]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier);
			break;
		}
		case 5:
		{
			float wingspan = (float)std::atof(argv[1]);
			float fuseLenModifier = (float)std::atof(argv[2]);
			float wingRootChordModifier = (float)std::atof(argv[3]);
			float wingTipChordModifier = (float)std::atof(argv[4]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier);
			break;
		}
		case 6:
		{
			float wingspan = (float)std::atof(argv[1]);
			float fuseLenModifier = (float)std::atof(argv[2]);
			float wingRootChordModifier = (float)std::atof(argv[3]);
			float wingTipChordModifier = (float)std::atof(argv[4]);
			float hStabAreaModifier = (float)std::atof(argv[5]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier);
			break;
		}
		case 7:
		{
			float wingspan = (float)std::atof(argv[1]);
			float fuseLenModifier = (float)std::atof(argv[2]);
			float wingRootChordModifier = (float)std::atof(argv[3]);
			float wingTipChordModifier = (float)std::atof(argv[4]);
			float hStabAreaModifier = (float)std::atof(argv[5]);
			float vStabAreaModifier = (float)std::atof(argv[6]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier, vStabAreaModifier);
			break;
		}
		case 8:
		{
			float wingspan = (float)std::atof(argv[1]);
			float fuseLenModifier = (float)std::atof(argv[2]);
			float wingRootChordModifier = (float)std::atof(argv[3]);
			float wingTipChordModifier = (float)std::atof(argv[4]);
			float hStabAreaModifier = (float)std::atof(argv[5]);
			float vStabAreaModifier = (float)std::atof(argv[6]);
			float weight = (float)std::atof(argv[7]);
			_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier, vStabAreaModifier, weight);
			break;
		}
		default:
			break;
		}
	}

	return true;
}