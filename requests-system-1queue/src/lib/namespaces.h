#include <string>

using std::string;

#ifndef NAMESPACES_H
#define NAMESPACES_H

namespace ascii
{
  const int intDiff = 48; // ASCII Code Difference between Chars and Integers
}

namespace files
{
  const char sep = ','; // Separators
  const int newLine = '\n';
}

namespace terminal
{
  // - ANSI Escape Code
  const string reset = "\x1b[0m"; // Reset Terminal Text Format to Default
  const string clear = "\033c";   // Clear Terminal

  // - Format Constants
  const string tab1 = string(3, ' '); // String with 3 whitespaces
  const string tab2 = string(8, ' '); // String with 8 whitespaces
  const bool applyBg = true;          // Add Customed Background Color
  const bool applyFg = true;          // Add Customed Foreground Color

  // --- Color Command Created Using ralvarezdev's Minigrep. URL: https://github.com/ralvarezdev/minigrep

  // - Normal State
  const string sgrBg = "\x1b[48;2;248;249;250m"; // Command to Change Text Background Color
  const string sgrFg = "\x1b[38;2;166;30;77m";   // Command to Change Text Foreground Color

  // - Warning (On Error)
  const string sgrBgError = sgrFg;
  const string sgrFgError = sgrBg;

  // - Number of Characters
  const int nChar = 100; // Max Number of Characters being Printed on Each Line
  const int nFirstName = 16;
  const int nLastName = 16;
  const int nTitle = 20;
  const int nDescription = 30;
  const int nPriority = 18;
  const int nColumn = 15;
}

namespace requests
{
  // Enums Should be at the Beginning
  // - Priority
  enum priority
  {
    priorityNull,
    alumni,
    administration,
    associateProfessor,
    professor,
    subdirectory,
    directory
  };

  // - Commands
  enum cmds
  {
    printAll = 1,
    pushRequest,
    popRequest,
    help,
    exit,
    cmdNull
  };

  // - Minimum and Maximum Priority
  const int minPriority = priority::alumni;
  const int maxPriority = priority::directory;

  // - Filename
  const string requestsFilename = "requests.csv";
}

#endif