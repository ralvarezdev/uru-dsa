#include "lib/terminal/ansiEsc.h"
#include "lib/terminal/input.h"
#include "lib/dungeons/dungeons.h"

using namespace terminal;

// --- Function Prototypes
void helpMessage();

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Initialize Dungeons Graph
  Dungeons *dungeons = new Dungeons();

  // - Program Status Variables
  bool exit, confirmation;
  string inputWord;
  int data, timesExec = 0;
  char cmd;

  while (!exit) // Main While Loop of the Program
  {
    // Check if Invoke Command Contains Program's Commands
    if (timesExec == 0 && argc > 1)
      cmd = argv[1][0];
    else
    {
      // Clear Screen
      cout << terminal::clear;

      // Print Help Message
      helpMessage();

      // Print New Line
      cout << '\n';

      // Get Command
      cmd = getChar("Enter Command: ");
    }

    // Increase Counter
    timesExec++;

    switch (cmd)
    {
    case dungeons::cmds::startGame:
      // Start the Game
      // dungeons->playGame();
      break;

    case dungeons::cmds::debugMode:
      // Clear Screen
      cout << terminal::clear;

      // Print Dungeons Debug Information
      printTitle("Debug Information");
      dungeons->printDungeonsInfo();
      pressEnterToCont("Press ENTER to Continue");
      break;

    case dungeons::cmds::help:
      break;

    case dungeons::cmds::exit:
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
  delete dungeons;
}

// --- Functions

// Function to Print Help Message in the Terminal
void helpMessage()
{
  cout << clear;
  printTitle("WELCOME TO DUNGEONS WITHOUT DRAGONS");
  cout << "GAME Commands\n"
       << tab1 << addBrackets<int>(dungeons::cmds::startGame) << " Start the Game\n"
       << tab1 << addBrackets<int>(dungeons::cmds::debugMode) << " Print Graph Info\n"
       << "Other Commands:\n"
       << tab1 << addBrackets<int>(dungeons::cmds::help) << " Help\n"
       << tab1 << addBrackets<int>(dungeons::cmds::exit) << " Exit\n";
}