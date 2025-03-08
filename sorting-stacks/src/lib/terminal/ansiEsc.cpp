#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "../namespaces.h"

using std::cout;
using std::left;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;

using namespace terminal;

// --- Functions Prototypes
string printTitle(string message, bool warning = false, bool returnStr = false);

// --- Functions

// Function to Print Title with Customed Colors
string printTitle(string message, bool warning, bool returnStr)
{
  string sgr; // String that Stores the SGR Command to Change the Text Format
  ostringstream content;

  if (terminal::applyBg)
    sgr.append((!warning) ? sgrBg : sgrBgError);
  if (terminal::applyFg)
    sgr.append((!warning) ? sgrFg : sgrFgError);

  // Title Content
  content << sgr << setw(nChar) << setfill(' ') << left << message << reset << '\n';

  // Return Content String
  if (returnStr)
    return content.str();

  // Print Content
  cout << content.str();
  // Return Empty String
  return "";
}