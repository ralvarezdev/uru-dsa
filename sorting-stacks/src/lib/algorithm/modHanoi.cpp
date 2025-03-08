#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "modHanoi.h"
#include "../namespaces.h"
#include "../terminal/ansiEsc.h"

using std::cout;
using std::fill;
using std::left;
using std::ostringstream;
using std::setfill;
using std::setw;

using namespace terminal;
using namespace stacks;
using namespace lists;

// --- Global Variables
int fromIndexLen, toIndexLen;
string separator;

// --- Functions Prototypes
void modHanoi(int nNodes, int stackLen, int *maxLen, int mainIndex, int auxIndex, int mainAuxIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);
void moveAtoB(int stackLen, int *maxLen, int sleepFor, int fromIndex, int toIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists);
void printStacks(NumberDoublyPtr *stacks, int stackLen, int maxLen, int sleepFor, int listIndexToCheck, int nodeIndexToCheck);

// --- Functions

// Modified Version of Hanoi Solution Algorithm, Adapted to this Practice Problem
// A: mainIndex, B: auxIndex, C: mainAuxIndex
void modHanoi(int nNodes, int stackLen, int *maxLen, int mainIndex, int auxIndex, int mainAuxIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists)
{
  if (nNodes > 0)
  {
    // Move Last Node from A to B
    modHanoi(nNodes - 1, stackLen, maxLen, mainIndex, mainAuxIndex, auxIndex, stacks, lists);

    // Move Last Node from A to C
    moveAtoB(stackLen, maxLen, stacks::sleepHanoi, mainIndex, mainAuxIndex, stacks, lists);

    // Move Last Node from B to C
    modHanoi(nNodes - 1, stackLen, maxLen, auxIndex, mainIndex, mainAuxIndex, stacks, lists);
  }
}

// Function to Move Top Node from A Stack to B Stack
void moveAtoB(int stackLen, int *maxLen, int sleepFor, int fromIndex, int toIndex, NumberStackPtr *stacks, NumberDoublyPtr *lists)
{
  int numberStack, numberList;

  // Remove Top Node from Current Stack
  numberStack = stacks[fromIndex]->pop();
  numberList = lists[fromIndex]->remove();

  /*
    // Check Stack and List Length, and if Node was Removed
    cout << "Stack and List " << fromIndex + 1 << " Length: "
         << lists[fromIndex]->getLength() << ' ' << stacks[fromIndex]->getLength() << '\n'
         << "Stack and List " << fromIndex + 1 << " Node: "
         << numberStack << ' ' << numberList << '\n';
  */

  // Push Top Node from Current Stack to Stack at mainAuxIndex
  stacks[toIndex]->push(numberStack);
  lists[toIndex]->push(numberList);

  // Check Stacks at fromIndex and to Index Length
  fromIndexLen = stacks[fromIndex]->getLength();
  toIndexLen = stacks[toIndex]->getLength();

  // Check if Stack at fromIndex is Decrementing
  if (fromIndexLen + 1 == *maxLen && toIndexLen + 1 <= *maxLen)
    *maxLen -= 1;
  // Check if Stack at toIndex has a Length Greater than maxLen
  else if (toIndexLen > *maxLen)
    *maxLen = toIndexLen;
  // Stack Completely Sorted
  else if (toIndexLen == stackLen)
    *maxLen = stackLen;

  // Print Stacks
  printStacks(lists, stackLen, *maxLen, sleepFor);
}

// Function to Print Stacks
void printStacks(NumberDoublyPtr *lists, int stackLen, int maxLen, int sleepFor, int listIndexToCheck, int nodeIndexToCheck)
{
  // Array Used to Check if the Given Stack has a Length Greater or Equal to Current Level
  bool greaterLength[stacks::nStacks];
  fill(greaterLength, greaterLength + stacks::nStacks, false);

  // Get Lists Length
  int listsLength[stacks::nStacks];
  for (int n = 0; n < stacks::nStacks; n++)
    listsLength[n] = lists[n]->getLength();

  // Current Node Level that's being Printed from All Stacks that have that Length
  int currLevel = stackLen * 2 + 1;

  // Stacks Content
  ostringstream content, dataHeader;

  // Stacks Data Title
  dataHeader << left
             << setw(terminal::nNumber) << setfill(' ') << "Stacks"
             << setw(terminal::nLength) << setfill(' ') << "Length"
             << setw(terminal::nTop) << setfill(' ') << "Top";

  // Add Header
  content << terminal::clear
          << printTitle(dataHeader.str(), false, true)
          << left;

  for (int n = 0; n < stacks::nStacks; n++)
  {
    content << setw(terminal::nNumber) << setfill(' ') << n + 1
            << setw(terminal::nLength) << setfill(' ') << lists[n]->getLength();

    if (lists[n]->isEmpty())
      content << "NULL\n";
    else
      content << setw(terminal::nTop) << setfill(' ') << lists[n]->get(0) << '\n';
  }
  content << "\nMax Length: " << maxLen << "\n\n";

  // Loop Over All Stack Levels
  for (; currLevel > 0; currLevel--)
  {
    // Print Separator
    if (currLevel == stackLen)
    {
      // Create Separator
      if (separator.length() == 0)
      {
        ostringstream tempSep;

        for (int n = 0; n < stacks::nStacks; n++)
        {
          if (n != 0)
            tempSep << terminal::tab1;

          tempSep << stacks::cornerSep
                  << string(stacks::maxDigits + 2 * stacks::borderSep, horSep)
                  << stacks::cornerSep;
        }

        // Set Separator
        separator = tempSep.str();
      }
      content << separator << '\n';
    }

    // Print Stack Level which has a Length Equal or Greater than Current Level
    for (int n = 0; n < stacks::nStacks; n++)
    {
      // Check if Current Stack has a Length Equal or Geater than Current Level
      if (!greaterLength[n])
        greaterLength[n] = listsLength[n] >= currLevel;

      if (n != 0)
        content << terminal::tab1;

      // Current Stack have less Nodes than Current Level
      if (!greaterLength[n])
      {
        // Add Whitespaces
        content << string(stacks::maxDigits + stacks::borderSep * 2 + 2, ' ');
        continue;
      }

      // Add Node Value
      content << stacks::nodeBorder
              << string(stacks::borderSep, ' ')
              << setw(stacks::maxDigits) << setfill(' ')
              << lists[n]->get(listsLength[n] - currLevel);

      // Add Visual Guide to Visualize Linear Search
      if (listIndexToCheck == n && currLevel - 1 == nodeIndexToCheck)
        content << lists::linearHead << string(stacks::borderSep - 1, lists::linearBody);
      else
        content << string(stacks::borderSep, ' ');

      content << stacks::nodeBorder;
    }

    content << '\n';
  }

  // Print Content
  cout << content.str();

  // Sleep for n Milliseconds
  if (sleepFor != 0)
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor));
}