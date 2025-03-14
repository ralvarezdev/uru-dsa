#include <string>
#include <typeinfo>

#include "../namespaces.h"

using std::string;

#ifndef INPUT_H
#define INPUT_H

// --- Functions
void pressEnterToCont(string message, bool warning = false);
string getLower(string word);
bool booleanQuestion(string message);
int getInteger(string message, int low, int high, int exception);
int getChar(string message);

// --- Templates

// Template to Return a String that's Surrounded by Brackets
template <typename T>
string addBrackets(T message)
{
  string addedBrackets;

  char cc = 4;
  int c = char(4);

  if (typeid(T) == typeid(const int)) // Checks if it's an Integer
    addedBrackets += message;
  else
    addedBrackets = message; // Message is of type String

  addedBrackets.insert(0, 1, '[');

  return addedBrackets.insert(addedBrackets.length(), 1, ']');
}

#endif