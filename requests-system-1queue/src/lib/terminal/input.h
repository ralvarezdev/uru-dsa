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
string getString(string askMessage, char restrictions[], int length, string errMessage);

// --- Templates

// Template to Return a String that's Surrounded by Brackets
template <typename T>
string addBrackets(T message)
{
  string addedBrackets;

  if (typeid(T) == typeid(const int))          // Checks if it's an Integer
    addedBrackets += message + ascii::intDiff; // Works fine if Message is an Integer
  else
    addedBrackets = message; // Message is of type String

  addedBrackets.insert(0, 1, '[');

  return addedBrackets.insert(addedBrackets.length(), 1, ']');
}

#endif