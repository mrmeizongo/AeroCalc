#ifndef _CLI_
#define _CLI_
#include "aerocalc.h"

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
float getInput(std::string textToDisplay, float defaultValeu);
#endif