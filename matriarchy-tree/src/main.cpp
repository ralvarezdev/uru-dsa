#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "lib/matriarchy/matrTree.h"
#include "lib/terminal/ansiEsc.h"
#include "lib/terminal/input.h"
#include "lib/namespaces.h"

using namespace std;

using namespace terminal;

// --- Function Prototypes
void helpMessage();
void changeCwdToData();

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Change Path to 'src/data'
  changeCwdToData();

  // Declare Matriarchy Tree and Initialize it
  MatrTree *matrTree = new MatrTree();

  // Read 'matriarchy.csv' File and Insert the Corresponding Nodes
  matrTree->readFile();

  // Check if there was an Error while reading the 'matriarchy.csv' File
  if (!matrTree->isValid())
  {
    pressEnterToCont("There was an Error while Reading the 'matriarchy.csv' File", true);
    return -1;
  }

  // - Program Status Variables
  bool exit, confirmation;
  string inputWord;
  int intCmd, timesExec = 0;
  matriarchy::cmds cmd;

  string pressEnterMsg = "Press ENTER to Continue";

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
        cmd = matriarchy::cmds(stoi(inputWord));
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
      // Clear Screen
      cout << terminal::clear;

      // Print Help Message
      helpMessage();

      // Print New Line
      cout << '\n';

      // Get Command
      intCmd = getInteger("Enter Command", 1, matriarchy::cmdNull - 1);
      cmd = matriarchy::cmds(intCmd);
    }

    // Increase Counter
    timesExec++;

    switch (cmd)
    {
    case matriarchy::cmds::parentsTraversal:
      // Print Parents Level Order Traversal
      matrTree->levelOrderParents();
      pressEnterToCont(pressEnterMsg);
      break;

    case matriarchy::cmds::womenTraversal:
      // Print Women Level Order Traversal
      matrTree->levelOrderWomen();
      pressEnterToCont(pressEnterMsg);
      break;

    case matriarchy::cmds::menTraversal:
      // Print Men Level Order Traversal
      matrTree->levelOrderMen();
      pressEnterToCont(pressEnterMsg);
      break;

    case matriarchy::cmds::singleTraversal:
      // Print Single Nodes Level Order Traversal
      matrTree->levelOrderSingle();
      pressEnterToCont(pressEnterMsg);
      break;

    case matriarchy::cmds::noKidsTraversal:
      // Print Couples with No Kids Level Order Traversal
      matrTree->levelOrderNoKids();
      pressEnterToCont(pressEnterMsg);
      break;

    case matriarchy::cmds::cousinsTraversal:
      // Print Cousins Level Order Traversal
      matrTree->levelOrderCousins();
      pressEnterToCont(pressEnterMsg);
      break;

    case matriarchy::cmds::divorceTraversal:
      // Divorce a Given Node
      matrTree->levelOrderDivorce();
      pressEnterToCont(pressEnterMsg);
      break;

    case matriarchy::cmds::help:
      break;

    case matriarchy::cmds::exit:
      // Confirmation Message
      exit = booleanQuestion("Are you SURE to Exit");
      break;

    default:
      // Command not Found
      pressEnterToCont("\nERROR: Command not Found", true);
      break;
    }
  }

  // Deallocate Memory
  delete matrTree;
}

// --- Functions

// Function to Print Help Message in the Terminal
void helpMessage()
{
  cout << clear;
  printTitle("WELCOME TO MATRIARCHY TREE");
  cout << "Matriarchy Tree Manipulation Commands\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::parentsTraversal) << " Parents Traversal\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::womenTraversal) << " Women Traversal\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::menTraversal) << " Men Traversal\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::singleTraversal) << " Single Traversal\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::noKidsTraversal) << " Couples with No Kids Traversal\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::cousinsTraversal) << " Cousins Traversal\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::divorceTraversal) << " Divorce\n"
       << "Other Commands:\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::help) << " Help\n"
       << tab1 << addBrackets<int>(matriarchy::cmds::exit) << " Exit\n";
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