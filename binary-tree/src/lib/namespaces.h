#include <string>

using std::string;

#ifndef NAMESPACES_H
#define NAMESPACES_H

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
  const string sgrBg = "\x1b[48;2;153;204;255m"; // Command to Change Text Background Color
  const string sgrFg = "\x1b[38;2;32;32;32m";    // Command to Change Text Foreground Color

  // - Warning (On Error)
  const string sgrBgError = "\x1b[48;2;255;153;153m";
  const string sgrFgError = "\x1b[38;2;32;32;32m";

  // - Number of Characters
  const int nChar = 100; // Max Number of Characters being Printed on Each Line
}

namespace binaryTrees
{
  // Enums Should be at the Beginning
  // - Binary Tree Commands
  namespace cmds
  {
    const int binInit = 'i';
    const int binInsert = 'a';
    const int binRemove = 'r';
    const int binPrint = 'p';
    const int binSearchInit = 'I';
    const int binSearchInsert = 'A';
    const int binSearchRemove = 'R';
    const int binSearchFind = 'F';
    const int binSearchPrint = 'P';
    const int help = 'h';
    const int exit = 'e';
  };

  // Range for Node's Data
  const int minData = 1;
  const int maxData = 999;

  // Error
  const int error = -1;
}

#endif