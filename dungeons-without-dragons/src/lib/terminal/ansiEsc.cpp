#include <iomanip>
#include <iostream>
#include <string>

#include "../namespaces.h"

using std::cout;
using std::left;
using std::setfill;
using std::setw;
using std::string;

using namespace terminal;

// --- Functions Prototypes
void printTitle(string message, bool warning= false);

// --- Functions

// Function to Print Title with Customed Colors
void printTitle(string message, bool warning )
{
  string sgr; // String that Stores the SGR Command to Change the Text Format

  if (terminal::applyBg)
    sgr.append((!warning) ? sgrBg : sgrBgError);
  if (terminal::applyFg)
    sgr.append((!warning) ? sgrFg : sgrFgError);

  cout << sgr << setw(nChar) << setfill(' ') << left << message << reset << '\n';
}