#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "../../submodules/udemy-dsa-cpp/data-structures/binary-search-tree/number.h"
#include "../../submodules/udemy-dsa-cpp/data-structures/binary-tree/number.h"
#include "../../submodules/udemy-dsa-cpp/data-structures/queue/base.h"

#include "lib/terminal/ansiEsc.h"
#include "lib/terminal/input.h"
#include "lib/namespaces.h"

using namespace std;

using namespace terminal;

// --- Function Prototypes
void helpMessage();
void emptyQueue(QueueLinkedList<int> *);
void getPreorderNodesData(QueueLinkedList<int> *);

int main(int argc, char **argv)
{
  // Desynchronize C++ Streams from C I/O Operations to Increase Performance
  std::ios::sync_with_stdio(false);

  // Declare Binary Tree and Binary Search Tree
  NumberBinaryTree<int> *binTree = NULL;
  NumberBinarySearchTree<int> *binSearchTree = NULL;
  QueueLinkedList<int> q(binaryTrees::error);

  // - Program Status Variables
  bool exit, confirmation;
  string inputWord;
  int data, timesExec = 0;
  char cmd;

  string binNotInit = "\nBinary Tree hasn't been Initialized";
  string binSearchNotInit = "\nBinary Search Tree hasn't been Initialized";

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
    case binaryTrees::cmds::binInit:
      // Clear Binary Tree
      if (binTree != NULL)
        delete binTree;

      // Clear Screen
      cout << terminal::clear;

      // Initialize Binary Tree
      binTree = new NumberBinaryTree<int>(binaryTrees::error);
      break;

    case binaryTrees::cmds::binInsert:
      // Check if Binary Tree has been Initialized
      if (binTree == NULL)
      {
        pressEnterToCont(binNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Ask for Node's Data
      data = getInteger("Enter Node's Data", binaryTrees::minData, binaryTrees::maxData, binaryTrees::error);

      // Check if the Data is Valid
      if (data == binaryTrees::error)
        break;

      // Insert Nodes
      binTree->insert(data);
      break;

    case binaryTrees::cmds::binRemove:
      // Check if Binary  Tree has been Initialized
      if (binTree == NULL)
      {
        pressEnterToCont(binNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Remove Node Interactively
      binTree->remove();

      break;

    case binaryTrees::cmds::binPrint:
      // Check if Binary Tree has been Initialized
      if (binTree == NULL)
      {
        pressEnterToCont(binNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Print Preorder, Inorder and Postorder Traversals
      printTitle("Binary Tree Traversals");
      binTree->preorder();
      binTree->inorder();
      binTree->postorder();

      pressEnterToCont("\nPress ENTER to Continue");
      break;

    case binaryTrees::cmds::binSearchInit:
      // Clear Binary Search Tree
      if (binSearchTree != NULL)
        delete binSearchTree;

      // Clear Screen
      cout << terminal::clear;

      // Asks if the User wants to Add Some Nodes
      confirmation = booleanQuestion("Do you want to Insert Some Nodes?");

      // Initialize Binary Search Tree with No Nodes
      if (!confirmation)
      {
        binSearchTree = new NumberBinarySearchTree<int>(binaryTrees::error);
        break;
      }

      // Ask for Nodes' Data
      getPreorderNodesData(&q);

      // Initialize Binary Search Tree
      binSearchTree = new NumberBinarySearchTree<int>(&q, binaryTrees::error);

      break;

    case binaryTrees::cmds::binSearchInsert:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Ask for Nodes' Data
      getPreorderNodesData(&q);

      // Insert Nodes
      binSearchTree->insert(&q);
      break;

    case binaryTrees::cmds::binSearchRemove:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Ask for Nodes' Data
      getPreorderNodesData(&q);

      // Remove Nodes
      binSearchTree->remove(&q);

      break;

    case binaryTrees::cmds::binSearchFind:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Ask for Node's Data
      data = getInteger("Enter Node's Data", binaryTrees::minData, binaryTrees::maxData, binaryTrees::error);

      // Check if Binary Search Tree Contains Node's Data
      if (binSearchTree->search(data))
      {
        pressEnterToCont("Data Found in Binary Search Tree");
        break;
      }

      pressEnterToCont("Data not Found in Binary Search Tree");
      break;

    case binaryTrees::cmds::binSearchPrint:
      // Check if Binary Search Tree has been Initialized
      if (binSearchTree == NULL)
      {
        pressEnterToCont(binSearchNotInit, true);
        break;
      }

      // Clear Screen
      cout << terminal::clear;

      // Print Preorder, Inorder and Postorder Traversals
      printTitle("Binary Search Tree Traversals");
      binSearchTree->preorder();
      binSearchTree->inorder();
      binSearchTree->postorder();

      pressEnterToCont("\nPress ENTER to Continue");
      break;

    case binaryTrees::cmds::help:
      break;

    case binaryTrees::cmds::exit:
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
  delete binTree, binSearchTree;
}

// --- Functions

// Function to Print Help Message in the Terminal
void helpMessage()
{
  cout << clear;
  printTitle("WELCOME TO BINARY XTREE");
  cout << "Binary Tree Manipulation Commands\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binInit) << " Initialize Tree\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binInsert) << " Insert Node\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binRemove) << " Remove Node\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binPrint) << " Print Inorder, Preorder, Postorder\n"
       << "Binary Search Tree Manipulation Commands\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binSearchInit) << " Initialize Tree\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binSearchInsert) << " Insert Node\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binSearchRemove) << " Remove Node\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binSearchFind) << " Search Node\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::binSearchPrint) << " Print Inorder, Preorder, Postorder\n"
       << "Other Commands:\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::help) << " Help\n"
       << tab1 << addBrackets<int>(binaryTrees::cmds::exit) << " Exit\n";
}

// Function to Empty Queue
void emptyQueue(QueueLinkedList<int> *q)
{
  // Empty Queue
  while (!q->isEmpty())
    q->dequeue();
}

// Function to Ask for Nodes' Data
void getPreorderNodesData(QueueLinkedList<int> *q)
{
  // Clear Queue
  if (!q->isEmpty())
    emptyQueue(q);

  ostringstream msg;
  int data;

  msg << "Enter Nodes' Data to Insert in Preorder. Enter '"
      << binaryTrees::error
      << "' to Stop Asking for Input";

  // Print Help Message
  printTitle(msg.str());

  while (true)
  {
    // Ask for Node's Data
    data = getInteger("Enter Node's Data", binaryTrees::minData, binaryTrees::maxData, binaryTrees::error);

    // Stop Asking for Input
    if (data == binaryTrees::error)
      break;

    // Push Data to Queue
    q->enqueue(data);
  }
}