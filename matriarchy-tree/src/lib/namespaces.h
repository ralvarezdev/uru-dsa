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
  // Separators
  const char nodeSep = ' ';
  const char genderSep = ':';
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
  const string sgrBg = "\x1b[48;2;201;42;42m";   // Command to Change Text Background Color
  const string sgrFg = "\x1b[38;2;255;255;255m"; // Command to Change Text Foreground Color

  // - Warning (On Error)
  const string sgrBgError = "\x1b[48;2;33;37;41m";
  const string sgrFgError = "\x1b[38;2;255;255;255m";

  // - Number of Characters
  const int nLevel = 10;
  const int nMotherId = 15;
  const int nNodeId = 10;
  const int nName = 20;
  const int nGender = 10;
  const int nStatus = 10;
  const int nConsanguinity = 15;

  // Max Number of Characters being Printed on Each Line
  const int nChar = nLevel + nMotherId + nNodeId + nName * 2 + nGender + nStatus + nConsanguinity;
}

namespace matriarchy
{
  // - Commands
  enum cmds
  {
    parentsTraversal = 1,
    womenTraversal,
    menTraversal,
    singleTraversal,
    noKidsTraversal,
    cousinsTraversal,
    divorceTraversal,
    help,
    exit,
    cmdNull
  };

  // NOTE: Please, don't Judge me by the Genders. These are just Requirements that I received. I'm not Against the LGBTQ+ Community
  // - Genders
  enum genders
  {
    woman,
    man,
    genderNull,
  };

  // - Level Order Traversals
  enum traversals
  {
    parents,
    women,
    men,
    single,
    noKids,
    cousins,
    divorce
  };

  // - Married Statuses Abbreviations
  const int singleAbbr = 'S';
  const int marriedAbbr = 'M';

  // - Gender Abbreviations
  const int womanAbbr = 'W';
  const int manAbbr = 'M';

  // - Consanguinity Abbreviations
  const int consanguinityAbbr = 'Y';
  const int affinityAbbr = 'N';

  // - Filename
  const string matriarchyFilename = "matriarchy.csv";
}

#endif