#ifndef _CLI_
#define _CLI_
#include "aerocalc.h"
#include <string>
using std::string;

#define AEROCALC_VERSION "1.0.0"

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

// Utility function to get input from user
float getInput(string textToDisplay, float defaultValeu);

// Utility function to calculate wingload
void wingLoad(float _weight = 0.f, float _wingspan = 0.f, float averageMC = 0.f);
#endif