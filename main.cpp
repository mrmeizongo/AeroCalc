// AeroCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include "aerocalc.h"
#include "cli.h"

int main(int argc, char* argv[])
{
	PlaneConfig config;
	StatusCode status = cli(argc, argv, config);

	switch (status)
	{
	case StatusCode::OK:
	{
		AeroCalc plane = AeroCalc(config);
		std::cout << std::fixed << std::setprecision(2);
		std::cout << plane << std::endl;
		return 0;
	}
	case StatusCode::HELP:
	case StatusCode::NO_OP:
		return 0;
	case StatusCode::INVALID_ARG:
		return 1;
	case StatusCode::INVALID_ARG_COUNT:
		return 2;
	default:
		return 3;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
