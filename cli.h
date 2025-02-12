#ifndef _CLI_
#define _CLI_
#include "aerocalc.h"

// Returns false if _planeSettings is unchanged
bool cli(int argc, char* argv[], PlaneSettings& _planeSettings);

// Utility function to get input from user
float getInput(std::string textToDisplay, float defaultValeu);
#endif