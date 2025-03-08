#include <iostream>
#include <filesystem>

#include "lib/emergency/emergency.h"

using namespace std;

// --- Function Prototypes
void changeCwdToData();

int main()
{
  // Move to 'src/data' Directory
  changeCwdToData();

  // Initialize Emergency Queue
  EmergencyQueue *q = new EmergencyQueue(Emergency(-1, -1));

  // Read File from unknown.txt
  q->readFile();

  // Print Emergencies
  q->print();

  return 0;
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
    cout << "Couldn't Get to Data Directory\n";
  }
}