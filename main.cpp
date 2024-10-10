// AeroCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include "aerocalc.h"

PlaneSettings _planeSettings;

float getInput(std::string textToDisplay, float defaultValeu);
std::string helpTxt = "Usage:\tAeroCalc [option]"
"\n\tAeroCalc [Wingspan] [FuselageLengthModifier] [WingRootChordModifier] [WingTipChordModifier] [HStabAreaModifier] [vStabAreaModifier] [Weight]"
"\nOptions:"
"\n-h, --help\t\t\tPrint command line options"
"\n\nRunning program without arguments uses default values for airplane settings";

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::string arg = argv[1];
		if (arg == "--help" || arg == "-h")
		{
			std::cout << helpTxt << std::endl;
			return 0;
		}
		else if (argc > 8)
		{
			std::cerr << "Arguments cannot exceed 7" << std::endl;
			std::cout << helpTxt << std::endl;
			return 1;
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
	}
	else
	{
		std::cout << "Enter plane dimensions"
			<< "\nLength modifiers are in percentages(0..1), wingspan is in inches and weight is in grams"
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
	}

	AeroCalc plane = AeroCalc(_planeSettings);
	std::cout << std::fixed << std::setprecision(2);
	std::cout << plane << std::endl;

	return 0;
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
