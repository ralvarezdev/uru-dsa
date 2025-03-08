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
  const string sgrBg = "\x1b[48;2;153;204;255m"; // Command to Change Text Background Color
  const string sgrFg = "\x1b[38;2;32;32;32m";    // Command to Change Text Foreground Color

  // - Warning (On Error)
  const string sgrBgError = "\x1b[48;2;255;153;153m";
  const string sgrFgError = "\x1b[38;2;32;32;32m";

  // - Number of Characters
  const int nChar = 100; // Max Number of Characters being Printed on Each Line
  const int nId = 5;
  const int nFirstName = 16;
  const int nLastName = 16;
  const int nEmail = 12;
  const int nGender = 8;
  const int nProm = 10;
  const int nCourse = 5;
}

namespace students
{
  // Enums Should be at the Beginning
  // - Genders
  enum genders
  {
    female,
    male,
    nonBinary,
    genderNull
  };

  // - Commands
  enum cmds
  {
    printAll = 1,
    printTop10,
    generateStudentFile,
    removeStudent,
    help,
    exit,
    cmdNull
  };

  // - Number of Courses
  const int nCourses = 5;

  // - Filename
  const string studentsFilename = "students.csv";
}

#endif