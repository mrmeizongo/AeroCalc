#ifndef _CLI_
#define _CLI_
#include "aerocalc.h"
#include <string>
using std::string;

enum class StatusCode : uint8_t
{
	OK,
	NO_OP,
	HELP,
	INVALID_ARG,
	INVALID_ARG_COUNT
};

// Main cli program. Returns status code after processing input
StatusCode cli(int argc, char* argv[], PlaneSettings& _planeSettings);

// Overloaded utility function to get input from user
string getInput(string textToDisplay, string defaultValue);
float getInput(string textToDisplay, float defaultValue);

// Utility function to calculate wingload
void wingLoad(float _weight = 0.f, float _wingspan = 0.f, float aerodynamicMC = 0.f);
#endif