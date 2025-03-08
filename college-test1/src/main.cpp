#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "../../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/number.h"
#include "../../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/character.h"
#include "../../submodules/udemy-dsa-cpp/data-structures/doubly-linked-lists/number.h"
#include "../../submodules/udemy-dsa-cpp/data-structures/circular-doubly-linked-lists/number.h"

using namespace std;

// --- Function Prototypes
void changeCwdToData();

int main()
{
  // Move to 'src/data' Directory
  changeCwdToData();

  // Initialize Data Structures
  NumberSingleLinkedList<float> *singleList = new NumberSingleLinkedList<float>();
  NumberDoublyLinkedList<float> *doublyList = new NumberDoublyLinkedList<float>();
  NumberCircularDoublyLinkedList<float> *circularList = new NumberCircularDoublyLinkedList<float>();
  CharacterSingleLinkedList *wordList = new CharacterSingleLinkedList();

  string line, word, wordSubstr, _;
  float number;

  // Reading First File
  fstream part1("part1.txt");

  if (!part1.is_open()) // Couldn't Access to part1
  {
    part1.close();
    cout << "Part1 File Not Found";
    getline(cin, _);
    return -1; // End this Function
  }

  // - Read Line by Line
  const char sep = '-';
  char lastChar;
  int count;

  // Get Single Linked List
  getline(part1, line);

  stringstream singleStream(line);

  count = 0;

  cout << "Reading Single Linked List Stream:\n";
  while (getline(singleStream, word, sep))
  {
    // cout << word << '\n';
    try
    {
      if (count != 0)
        wordSubstr = word.substr(1, word.length());
      else
        wordSubstr = word;

      number = stof(wordSubstr);
      singleList->pushBack(number);
    }
    catch (...)
    {
      cout << "Number Couldn't be Pushed Back to Single Linked List\n";
    }
    count++;
  }

  // Print Data Structures
  cout << "\nSingle Linked List:\n";
  singleList->print();

  // Get Doubly Linked List
  getline(part1, line);

  stringstream doublyStream(line);

  count = 0;

  cout << "Reading Doubly Linked List Stream:\n";
  while (getline(doublyStream, word, sep))
  {
    // cout << word << '\n';
    try
    {
      if (count != 0)
        wordSubstr = word.substr(1, word.length() - 1);
      else
        wordSubstr = word.substr(0, word.length() - 1);

      number = stof(wordSubstr);
      doublyList->pushBack(number);
    }
    catch (...)
    {
      cout << "Number Couldn't be Pushed Back to Doubly Linked List\n";
    }
    count++;
  }

  // Print Data Structures
  cout << "\nDoubly Linked List:\n";
  doublyList->print();

  // Get Circular Linked List
  getline(part1, line);

  stringstream circularStream(line);

  count = 0;

  cout << "Reading Circular Linked List Stream:\n";
  while (getline(circularStream, word, sep))
  {
    // cout << word << '\n';
    try
    {
      if (count != 0)
        wordSubstr = word.substr(1, word.length());
      else
        wordSubstr = word;

      number = stof(wordSubstr);

      // If No Node has the Same value as Number, Insert Node to Circular Linked List
      if (count == 0 || !circularList->linearSearch(number))
        circularList->pushBack(number);
    }
    catch (...)
    {
      cout << "Number Couldn't be Pushed Back to Circular Linked List\n";
    }
    count++;
  }

  // Print Data Structures
  cout << "\nCircular Linked List:\n";
  circularList->print();

  // Move Nodes Data from Single and Doubly Linked Lists to Circular Linked List
  while (!singleList->isEmpty())
  {
    number = singleList->remove();
    circularList->pushBack(number);
  }

  while (!doublyList->isEmpty())
  {
    number = doublyList->remove();
    circularList->pushBack(number);
  }

  // Print Data Structures after Moving Data from Single and Doubly Lists to Circular One
  cout << "\nMoving Nodes to Circular Linked List\n";

  cout << "\nSingle Linked List:\n";
  singleList->print();

  cout << "\nDoubly Linked List:\n";
  doublyList->print();

  cout << "\nCircular Linked List:\n";
  circularList->print();

  // Reading Second File

  fstream part2("part2.txt");
  while (getline(part2, line))
  {
    stringstream file(line);

    while (getline(file, word, ' '))
    {
      // Check Word Last Character
      lastChar = word.at(word.length() - 1);
      if (lastChar == ',' || lastChar == '.')
        // Remove Character from String
        word = word.substr(0, word.length() - 1);

      wordList->insertionSort(word);
    }
  }

  // Print Data Structures
  cout << "\nWord Single Linked List:\n";
  wordList->print();

  // Remove Words with a Length less than 3
  cout << "\nRemoving Word with Less than 3 Letters:\n";
  wordList->removeLength(false, 3);
  wordList->print();

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