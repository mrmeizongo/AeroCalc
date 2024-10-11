// AeroCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include "aerocalc.h"
#include "cli.h"

PlaneSettings _planeSettings;

float getInput(std::string textToDisplay, float defaultValeu);

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		if(!cli(argc, argv, _planeSettings)) return 1;
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
