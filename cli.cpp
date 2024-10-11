#include "cli.h"
#include <string>

std::string helpTxt = "Usage:\tAeroCalc [option]"
"\n\tAeroCalc [Wingspan] [FuselageLengthModifier] [WingRootChordModifier] [WingTipChordModifier] [HStabAreaModifier] [vStabAreaModifier] [Weight]"
"\nOptions:"
"\n-h, --help\t\t\tPrint command line options"
"\n\nRunning program without arguments uses default values for airplane settings";


bool cli(int argc, char* argv[], PlaneSettings& _planeSettings)
{
	std::string arg = argv[1];
	if (arg == "--help" || arg == "-h")
	{
		std::cout << helpTxt << std::endl;
		return false;
	}
	else if (argc > 8)
	{
		std::cerr << "Arguments cannot exceed 7" << std::endl;
		std::cout << helpTxt << std::endl;
		return false;
	}
	else if (argc == 2)
	{
		float wingspan = (float)std::atof(argv[1]);
		_planeSettings = PlaneSettings(wingspan);
	}
	else if (argc == 3)
	{
		float wingspan = (float)std::atof(argv[1]);
		float fuseLenModifier = (float)std::atof(argv[2]);
		_planeSettings = PlaneSettings(wingspan, fuseLenModifier);
	}
	else if (argc == 4)
	{
		float wingspan = (float)std::atof(argv[1]);
		float fuseLenModifier = (float)std::atof(argv[2]);
		float wingRootChordModifier = (float)std::atof(argv[3]);
		_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier);
	}
	else if (argc == 5)
	{
		float wingspan = (float)std::atof(argv[1]);
		float fuseLenModifier = (float)std::atof(argv[2]);
		float wingRootChordModifier = (float)std::atof(argv[3]);
		float wingTipChordModifier = (float)std::atof(argv[4]);
		_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier);
	}
	else if (argc == 6)
	{
		float wingspan = (float)std::atof(argv[1]);
		float fuseLenModifier = (float)std::atof(argv[2]);
		float wingRootChordModifier = (float)std::atof(argv[3]);
		float wingTipChordModifier = (float)std::atof(argv[4]);
		float hStabAreaModifier = (float)std::atof(argv[5]);
		_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier);
	}
	else if (argc == 7)
	{
		float wingspan = (float)std::atof(argv[1]);
		float fuseLenModifier = (float)std::atof(argv[2]);
		float wingRootChordModifier = (float)std::atof(argv[3]);
		float wingTipChordModifier = (float)std::atof(argv[4]);
		float hStabAreaModifier = (float)std::atof(argv[5]);
		float vStabAreaModifier = (float)std::atof(argv[6]);
		_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier, vStabAreaModifier);
	}
	else if (argc == 8)
	{
		float wingspan = (float)std::atof(argv[1]);
		float fuseLenModifier = (float)std::atof(argv[2]);
		float wingRootChordModifier = (float)std::atof(argv[3]);
		float wingTipChordModifier = (float)std::atof(argv[4]);
		float hStabAreaModifier = (float)std::atof(argv[5]);
		float vStabAreaModifier = (float)std::atof(argv[6]);
		float weight = (float)std::atof(argv[7]);
		_planeSettings = PlaneSettings(wingspan, fuseLenModifier, wingRootChordModifier, wingTipChordModifier, hStabAreaModifier, vStabAreaModifier, weight);
	}

	return true;
}