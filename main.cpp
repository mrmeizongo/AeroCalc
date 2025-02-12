// AeroCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include "aerocalc.h"
#include "cli.h"

int main(int argc, char* argv[])
{
	PlaneSettings planeSettings;

	if (!cli(argc, argv, planeSettings)) return 1;

	AeroCalc plane = AeroCalc(planeSettings);
	std::cout << std::fixed << std::setprecision(2);
	std::cout << plane << std::endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
