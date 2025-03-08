#include <string>
#include <typeinfo>

#include "../namespaces.h"

using std::string;

using namespace ascii;

#ifndef INPUT_H
#define INPUT_H

// --- Functions
void pressEnterToCont(string message, bool warning = false);
bool booleanQuestion(string message);
int getInteger(string message, int low, int high);

#endif