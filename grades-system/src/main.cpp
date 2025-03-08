#include <string>
#include <iostream>
#include <filesystem>

#include "lib/terminal/cols.h"
#include "lib/terminal/input.h"
#include "lib/students/students.h"

using namespace std;

// --- Function Prototypes
void helpMessage();
void changeCwdToData();

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Change Path to 'src/data'
  changeCwdToData();

  // Students Header
  Col cols[11] = {
      Col("Id", terminal::nId),
      Col("First Name", terminal::nFirstName),
      Col("Last Name", terminal::nLastName),
      Col("Gender", terminal::nGender),
      Col("Prom", terminal::nProm),
      Col("OOP", terminal::nCourse),
      Col("DSA", terminal::nCourse),
      Col("DB", terminal::nCourse),
      Col("Math", terminal::nCourse),
      Col("Stats", terminal::nCourse)};

  // Create Title Linked List
  ColLinkedList *titleList = new ColLinkedList(cols, 11, Col());

  // Create Student Linked List
  StudentLinkedList *studentList = new StudentLinkedList();

  // Read students.csv
  studentList->readFile();

  // - Program Status Variables
  bool exit, confirmation;
  string inputWord;
  int id, pos, intCmd, timesExec = 0;
  students::cmds cmd;

  while (!exit) // Main While Loop of the Program
  {
    // Check if Invoke Command Contains Program's Commands
    if (timesExec == 0 && argc > 1)
    {
      // Checks if it's a Command
      inputWord = argv[1];
      try
      {
        // Try to Get Command
        cmd = students::cmds(stoi(inputWord));
      }
      catch (...)
      {
        // Throw Error Message
        pressEnterToCont("ERROR: Command not Found", true);
        break;
      }
    }
    else
    {
      // Print Help Message
      helpMessage();

      // Print New Line
      cout << '\n';

      // Get Command
      intCmd = getInteger("Enter Command", 1, cmds::cmdNull);
      cmd = cmds(intCmd);
    }

    // Increase Counter
    timesExec++;

    switch (cmd)
    {
    case students::printAll:
      // Clear Terminal
      cout << clear;

      // Print Columns Header
      titleList->print();

      // Print Students
      studentList->print();

      // Print New Line
      cout << '\n';

      pressEnterToCont("Press ENTER to Continue");
      break;

    case students::printTop10:
      // Clear Terminal
      cout << clear;

      // Print Columns Header
      titleList->print();

      // Print Students
      studentList->print(10);

      // Print New Line
      cout << '\n';

      pressEnterToCont("Press ENTER to Continue");
      break;

    case students::generateStudentFile:
      // Ask for Student ID
      id = getInteger("Enter Student ID", 1, studentList->getLength());

      // Get Student Position in Linked List
      pos = studentList->linearSearch(id);

      // Student not Found
      if (pos == -1)
      {
        pressEnterToCont("ERROR: Student not Found", true);
        break;
      }

      // Generate Student File
      studentList->generateStudentFile(pos);
      break;

    case students::removeStudent:
      // Ask for Student ID
      id = getInteger("Enter Student ID to Remove", 1, studentList->getLength());

      // Get Student Position in Linked List
      pos = studentList->linearSearch(id);

      // Student not Found
      if (pos == -1)
      {
        pressEnterToCont("ERROR: Student not Found", true);
        break;
      }

      // Confirmation Message
      cout << "\n\n";
      if (booleanQuestion("Is this the Student you want to Remove?"))
      {
        studentList->removeAt(pos);
        studentList->overwriteCSV();
      }
      break;

    case students::help:
      break;

    case students::exit:
      // Confirmation Message
      exit = booleanQuestion("Are you SURE to Exit");
      break;

    default:
      // Command not Found
      pressEnterToCont("ERROR: Command not Found", true);
      break;
    }
  }

  // Deallocate Memory
  delete titleList, studentList;
}

// --- Functions

// Function to Print Help Message in the Terminal
void helpMessage()
{
  cout << clear;
  printTitle("WELCOME TO EDUCA V2.0");
  cout << "Database Manipulation Commands\n"
       << tab1 << addBrackets<int>(students::printAll) << " Print Students\n"
       << tab1 << addBrackets<int>(students::printTop10) << " Print Top 10 Students\n"
       << tab1 << addBrackets<int>(students::generateStudentFile) << " Generate Student File\n"
       << tab1 << addBrackets<int>(students::removeStudent) << " Remove Student\n"
       << "Other Commands:\n"
       << tab1 << addBrackets<int>(students::help) << " Help\n"
       << tab1 << addBrackets<int>(students::exit) << " Exit\n";
}

// Function to Change Current Working Directory to 'src/data'
void changeCwdToData()
{
  try
  {
    filesystem::path mainCppPath = __FILE__;              // Path to main.cpp File
    filesystem::path srcPath = mainCppPath.parent_path(); // Path to 'src' Folder

    filesystem::path dataDir = "data";
    filesystem::path dataPath = srcPath / dataDir; // Concatenate srcPath with DataDir to get the FUll Path to the .csv Files

    filesystem::current_path(dataPath); // Change cwd to '.../src/data'
  }
  catch (...)
  {
    pressEnterToCont("Error: main.cpp File is not Inside 'src' Folder", true);
  }
}