#include <string>
#include <iostream>
#include <filesystem>

#include "lib/terminal/cols.h"
#include "lib/terminal/input.h"
#include "lib/requests/requests.h"

using namespace std;

/*
NOTE: In this Practice, we're Challenged to Create a Requests System that's Sorted by Priority and by Order of Arrival,
with the Less Amount of Queues and Auxiliary Data Structures
*/

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
  Col cols[5] = {
      Col("First Name", terminal::nFirstName),
      Col("Last Name", terminal::nLastName),
      Col("Title", terminal::nTitle),
      Col("Description", terminal::nDescription),
      Col("Priority", terminal::nPriority)};

  // Create Title Linked List
  ColLinkedList *titleList = new ColLinkedList(cols, 5, Col());

  // Create Requests Queue Linked List
  RequestQueueLinkedList *requestsQueue = new RequestQueueLinkedList();

  // Read requests.csv
  requestsQueue->readFile();

  // - Program Status Variables
  bool exit, confirmation;
  string inputWord, firstName, lastName, title, description, errMessage1, errMessage2;
  int intCmd, timesExec = 0, priorityNumber, columnDiff;

  ostringstream content;

  Request *newRequest, topRequest;
  requests::cmds cmd;
  requests::priority priority;

  // - Characters Restricted
  const int length1 = 1;
  const int length2 = 1;
  char restrictions1[length1] = {','};
  char restrictions2[length2] = {'"'};

  // Maximum Number of Characters per Line Minus Characters for Given Column
  columnDiff = terminal::nChar - terminal::nColumn;

  // Error Message
  errMessage1 = "Cannot Contain Any Commas";
  errMessage2 = "Cannot Contain Any Double Quotes";

  while (!exit) // Main While Loop of the Program
  {
    // Check if Invoke Command Contains Program's Commands
    if (timesExec == 0 && argc > 1)
    { // Checks if it's a Command
      inputWord = argv[1];
      try
      {
        // Try to Get Command
        cmd = requests::cmds(stoi(inputWord));
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
    case requests::printAll:
      // Clear Terminal
      cout << clear;

      // Print Columns Header
      titleList->print();

      // Print Students
      requestsQueue->print();

      // Print New Line
      cout << '\n';

      pressEnterToCont("Press ENTER to Continue");
      break;

    case requests::pushRequest:
      cout << terminal::clear;
      printTitle("Insert New Request");
      cout << '\n';

      // Get First Name
      firstName = getString("First Name", restrictions1, length1, errMessage1);

      // Get Last Name
      lastName = getString("Last Name", restrictions1, length1, errMessage1);

      // Get Title
      title = getString("Title", restrictions1, length1, errMessage1);

      // Get Description
      description = getString("Description", restrictions2, length2, errMessage2);

      // First Name Can't Contain Commas
      if (description.find(',') != string::npos)
      {
        // Add Double Quote to the Beggining and End of this String
        description.insert(0, "\"");
        description += '"';
      }

      // Print Different Priorities
      cout << '\n';
      printTitle("Priority");
      cout << '\n'
           << setw(terminal::nPriority) << setfill(' ') << "Directory: "
           << requests::priority::directory << '\n'
           << setw(terminal::nPriority) << setfill(' ') << "Subdirectory: "
           << requests::priority::subdirectory << '\n'
           << setw(terminal::nPriority) << setfill(' ') << "Professor: "
           << requests::priority::professor << '\n'
           << setw(terminal::nPriority) << setfill(' ') << "Assoc. Professor: "
           << requests::priority::associateProfessor << '\n'
           << setw(terminal::nPriority) << setfill(' ') << "Administration: "
           << requests::priority::administration << '\n'
           << setw(terminal::nPriority) << setfill(' ') << "Alumni: "
           << requests::priority::alumni << "\n\n";

      // Get Request Priority
      priorityNumber = getInteger("Priority", minPriority, maxPriority);
      priority = requests::priority(priorityNumber);

      // Call Request Constructor
      newRequest = new Request(firstName, lastName, title, description, priority);

      // Insert Request
      requestsQueue->insertByPriority(*newRequest);

      // Overwrite requests.csv
      requestsQueue->overwriteCSV();

      break;

    case requests::popRequest:
      // Clear Stream
      content.str("");
      content.clear();

      // Set Text Alignment to the Left
      content << left;

      cout << terminal::clear;
      printTitle("Top Request");

      // Pop First Request from requestsQueue
      topRequest = requestsQueue->pop();

      // Print Top Request Data
      content << '\n'
              << setw(terminal::nColumn) << setfill(' ') << "First Name"
              << topRequest.getFirstName() << '\n'
              << setw(terminal::nColumn) << setfill(' ') << "Last Name"
              << topRequest.getLastName() << '\n';

      // - Title
      title = topRequest.getTitle();
      content << setw(terminal::nColumn) << setfill(' ') << "Title";

      if (title.length() < columnDiff)
        content << title << '\n';
      else
        content << title.substr(0, columnDiff - 4) << "... \n";

      // - Description
      description = topRequest.getDescription();
      content << setw(terminal::nColumn) << setfill(' ') << "Description";

      // Check if Description Contains Some Commas
      if (description.find(',') != string::npos)
        // Remove Double Quotes
        description = description.substr(1, description.length() - 2);

      if (description.length() < columnDiff)
        content << description << '\n';
      else
        content << description.substr(0, columnDiff - 4) << "... \n";

      content << setw(terminal::nColumn) << setfill(' ') << "Priority"
              << topRequest.getPriorityStr() << "\n\n";

      // Print Data
      cout << content.str();

      // Ask to Overwrite CSV
      if (booleanQuestion("Do you want to Save Changes to requests.csv File?"))
        requestsQueue->overwriteCSV();
      break;

    case requests::help:
      break;

    case requests::exit:
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
  delete titleList, requestsQueue;
}

// --- Functions

// Function to Print Help Message in the Terminal
void helpMessage()
{
  cout << clear;
  printTitle("WELCOME TO FLASH ACADEMIC REQUESTS SYSTEM");
  cout << "Database Manipulation Commands\n"
       << tab1 << addBrackets<int>(requests::printAll) << " Print Requests\n"
       << tab1 << addBrackets<int>(requests::pushRequest) << " Add Request at the End\n"
       << tab1 << addBrackets<int>(requests::popRequest) << " Get First Request\n"
       << "Other Commands:\n"
       << tab1 << addBrackets<int>(requests::help) << " Help\n"
       << tab1 << addBrackets<int>(requests::exit) << " Exit\n";
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