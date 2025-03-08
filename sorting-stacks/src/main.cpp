#include <string>
#include <random>
#include <iostream>

#include "lib/namespaces.h"
#include "lib/algorithm/modHanoi.h"
#include "lib/terminal/ansiEsc.h"
#include "lib/terminal/input.h"
#include "../../submodules/udemy-dsa-cpp/data-structures/stack/number.h"
#include "../../submodules/udemy-dsa-cpp/data-structures/doubly-linked-lists/number.h"

/*
NOTE: For this practice, it's required to sort 3 stacks (I tried to expand this number by N stacks),
with 3 nodes each (I also tried to expand by N nodes). We're only allowed to get last node data at given stack.
My algorithm to solve this problem is based on the Hanoi Tower Problem. Because we will only know last node at each stack,
I'll need at least two linked lists to sort the stack. However, I create the same number of linked lists as stacks,
to print faster each node at each stack.
*/

/*
Stack Representation

| 2   |
| 999 |
| 3   |
| 25  |
| 1   |
| 66  |
*/

using std::cin;
using std::cout;
using std::random_device;
using std::uniform_int_distribution;

using namespace stacks;

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Length of the Biggest Stack. Auxiliary Stacks Used to Sort Current Stack
  int maxLen, auxIndex, mainAuxIndex;

  // Random Number Generator
  random_device rd;

  // Print Title
  printTitle("SORTING STACKS PROBLEM");
  cout << '\n';

  // Ask for Number of Nodes for each Stack
  const int stackLen = getInteger("Enter the Number of Nodes for each Stack", stacks::minNodes, stacks::maxNodes);

  // Variable that Stores the Length of the Biggest Stack
  maxLen = stackLen;

  // Check nStacks
  if (stacks::nStacks < stacks::minStacks)
  {
    pressEnterToCont("ERROR: This Algorithm Requires at Least 3 Stacks to Sort them", true);
    return -1;
  }
  if (stacks::nStacks > stacks::maxStacks)
  {
    pressEnterToCont("WARNING: nStacks is too Big. Stacks could Look Wrong because of Terminal Width", true);
    pressEnterToCont("- If you're Sure about your Choice, Modify maxStacks in stacks Namespace, and Run this Program Again", true);
    return -1;
  }

  // Create Stacks and Doubly Linked List
  NumberStackPtr *stacksArray = new NumberStackPtr[stacks::nStacks];
  NumberDoublyPtr *listsArray = new NumberDoublyPtr[stacks::nStacks];

  // Random Integer Distribution
  uniform_int_distribution<int> dist(stacks::minNodeValue, stacks::maxNodeValue);

  int random;
  NumberStackPtr stack;
  NumberDoublyPtr list;

  for (int n = 0; n < stacks::nStacks; n++)
  {
    // Create Stack and Doubly Linked List
    stack = new NumberStackLinkedList<int>();
    list = new NumberDoublyLinkedList<int>();

    // Create Random Nodes Values for Each
    for (int i = 0; i < stackLen; i++)
    {
      // Generate Random Node Values
      random = dist(rd);

      // Print Data Structures Length
      /*
      cout << random << ' ' << (*stack).getLength() << ' ' << (*list).getLength() << '\n';
      */

      // Push Random Node Value to Stack and Doubly Linked List
      stack->push(random);
      list->push(random);
    }

    // Added Stack and Doubly Linked List to their Corresponding Array
    stacksArray[n] = stack;
    listsArray[n] = list;
  }

  /*
    // Print and Top Node's Value
    for (int n = 0; n < stacks::nStacks; n++)
      cout << "Stack " << n + 1 << ": " << stacksArray[n]->top() << '\n';
  */

  // Initial State
  printStacks(listsArray, maxLen, stackLen, stacks::sleepNoMove);

  // Asks to Continue
  cout << string(terminal::nNewLines, '\n');
  pressEnterToCont("Press Enter to Continue");

  // Loop Over Stacks
  for (int currStack = 0; currStack < stacks::nStacks; currStack++)
  {
    // Sort Last Stack
    if (currStack + 1 == stacks::nStacks)
    {
      // Third to Last Stack
      mainAuxIndex = currStack - 2;
      // Second to Last Stack
      auxIndex = currStack - 1;
    }
    // Sort Second to Last Stack
    else if (currStack + 2 == stacks::nStacks)
    {
      // Third to Last Stack
      mainAuxIndex = currStack - 1;
      // Last Stack
      auxIndex = currStack + 1;
    }
    else
    {
      // Second Stack Next to the One to be Sorted
      mainAuxIndex = currStack + 2;
      // Stack Next to the One to be Sorted
      auxIndex = currStack + 1;
    }

    /*
    // Check Stack Indexes Used by the Algoritm
    cout << "Current Stack Index: " << currStack << "\nMain Auxiliary Stack Index: " << mainAuxIndex << "\nAuxiliary Stack Index: " << auxIndex << '\n';
    */

    // First Iteration
    moveAtoB(stackLen, &maxLen, stacks::sleepMove, currStack, mainAuxIndex, stacksArray, listsArray);

    int currStackTop, currStackLen = stackLen - 1;

    // Sort Stack Until All Nodes are Pushed to Current Stack Again
    while (currStackLen != stackLen)
    {
      // Get Current Stack Top Node's Value
      currStackTop = stacksArray[currStack]->top();

      // Visualize Comparison
      printStacks(listsArray, stackLen, maxLen, stacks::sleepRead, currStack, currStackLen - 1);

      // All Nodes have been Popped from Current Stack. Perform Last Iteration
      if (currStackLen == 0)
      {
        // Move Nodes from Stack at mainAuxIndex, through Stack at auxIndex, to Current Stack
        modHanoi(stackLen, stackLen, &maxLen, mainAuxIndex, auxIndex, currStack, stacksArray, listsArray);
        break;
      }

      // Current Stack Top Node is the Biggest One
      if (currStackLen == 1 && currStackTop >= listsArray[mainAuxIndex]->get(maxLen - stackLen - 1))
      {
        // Visualize Comparison
        printStacks(listsArray, stackLen, maxLen, stacks::sleepRead, mainAuxIndex, stackLen);

        // Move Nodes from Stack at mainAuxIndex, through Stack at auxIndex, to Current Stack
        modHanoi(stackLen - 1, stackLen, &maxLen, mainAuxIndex, auxIndex, currStack, stacksArray, listsArray);
        break;
      }

      // Current Stack Top Node's Value is Less than Stack at mainAuxIndex Top Node's Value
      if (currStackTop <= stacksArray[mainAuxIndex]->top())
      {
        // Visualize Comparison
        printStacks(listsArray, stackLen, maxLen, stacks::sleepRead, mainAuxIndex, maxLen - 1);

        // Move from Current Stack to Stack at mainAuxIndex
        moveAtoB(stackLen, &maxLen, stacks::sleepMove, currStack, mainAuxIndex, stacksArray, listsArray);
      }
      // Current Stack Top Node's Value is Grater than Stack at mainAuxIndex Top Node's Value, but Just One Iteration has been Performed
      else if (maxLen == stackLen + 1)
      {
        // Move from Stack at mainAuxIndex to Stack at auxIndex
        moveAtoB(stackLen, &maxLen, stacks::sleepMove, mainAuxIndex, auxIndex, stacksArray, listsArray);
        // Move from Current Stack to Stack at mainAuxIndex
        moveAtoB(stackLen, &maxLen, stacks::sleepMove, currStack, mainAuxIndex, stacksArray, listsArray);
        // Move from Stack at auxIndex to Stack at mainAuxIndex
        moveAtoB(stackLen, &maxLen, stacks::sleepMove, auxIndex, mainAuxIndex, stacksArray, listsArray);
      }
      else
      {
        // Counter to Check at which Level Should be Placed the Disk
        int nNodes;

        // Only Compare Nodes that were Popped from Current Stack
        for (nNodes = 2; nNodes <= maxLen - stackLen; nNodes++)
        {
          // Visualize Linear Search
          printStacks(listsArray, stackLen, maxLen, stacks::sleepRead, mainAuxIndex, maxLen - nNodes);

          if (listsArray[mainAuxIndex]->get(nNodes - 1) >= currStackTop)
            break;
        }

        // Move nNodes from Stack at mainAuxIndex to Stack at auxIndex
        modHanoi(nNodes - 1, stackLen, &maxLen, mainAuxIndex, currStack, auxIndex, stacksArray, listsArray);

        // Move Current Stack Top Node to Stack at mainAuxIndex
        moveAtoB(stackLen, &maxLen, stacks::sleepMove, currStack, mainAuxIndex, stacksArray, listsArray);

        // Move nNodes from Stack at auxIndex to Stack at mainAuxIndex
        modHanoi(nNodes - 1, stackLen, &maxLen, auxIndex, currStack, mainAuxIndex, stacksArray, listsArray);
      }

      // Update currStackLen
      currStackLen = stacksArray[currStack]->getLength();
    };
  }

  // End Message
  cout << string(terminal::nNewLines, '\n');
  pressEnterToCont("COMPLETED");

  // Deallocate Memory
  delete[] stacksArray, listsArray;
}