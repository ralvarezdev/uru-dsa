#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "ansiEsc.h"

using std::cin;
using std::cout;
using std::getline;
using std::invalid_argument;
using std::ostringstream;
using std::out_of_range;
using std::string;

// --- Function Prototypes
void pressEnterToCont(string message, bool warning = false);
string getLower(string word);
bool booleanQuestion(string message);
int getInteger(string message, int low, int high, int exception);
int getChar(string message);

// --- Functions

// Boolean Question
bool booleanQuestion(string message)
{
  string input;
  char c;

  while (true)
  {
    cout << "- " << message << " [y/N] ";
    getline(cin, input);

    c = tolower(input[0]);

    if (c == 'y')
    {
      cout << '\n';
      return true;
    }
    else if (c == 'n')
    {
      cout << '\n';
      return false;
    }

    // Print Error Message
    pressEnterToCont("ERROR: It's a Yes/No Question. You must type 'y', 'Y' or 'n', 'N'", true);
  }
}

// Function to Ask for Integer Input
int getInteger(string message, int low, int high, int exceptionInt = -1)
{
  string temp;
  int amount;

  while (true)
    try // Get Integer
    {
      cout << message << ": ";
      getline(cin, temp);
      amount = stoi(temp);

      // Check if the Number is Out of Range
      if ((amount < low || amount > high) && amount != exceptionInt)
        throw out_of_range("Amount Out of Range");

      return amount;
    }
    catch (const invalid_argument &e)
    {
      pressEnterToCont("ERROR: Invalid Argument. It Must be an Integer", true);
    }
    catch (const out_of_range &e)
    {
      ostringstream stream;

      stream << "\nThe Number is Out of Range"
             << " [" << low << '-' << high << "]";

      pressEnterToCont(stream.str(), true);
    }
}

// Function to Stop the Program Flow while the User doesn't press the ENTER key
void pressEnterToCont(string message, bool warning)
{
  string _;

  printTitle(message, warning);
  getline(cin, _);
}

// Function to Get a Lowercase String
string getLower(string word)
{
  string wordToLower;

  for (int i = 0; i < word.length(); i++)
    wordToLower += tolower(word[i]); // Append Character in Lowercase

  return wordToLower;
}

// Function to Get Character
int getChar(string message)
{
  string input;

  cout << "- " << message;
  getline(cin, input);

  return input[0];
}