#include <sstream>
#include <fstream>

#include "../../../../submodules/udemy-dsa-cpp/data-structures/stack/base.h"
#include "matrNode.h"
#include "../terminal/input.h"

using std::getline;
using std::ifstream;
using std::stringstream;

#ifndef MATR_TREE
#define MATR_TREE

// MATRIARCHY TREE CLASS

class MatrTree
{
protected:
  MatrNodePtr root = NULL;
  bool valid = true;

  // Protected Methods
  void setInvalid();

public:
  // Constructors
  MatrTree(){};

  // Destructor
  virtual ~MatrTree()
  {
    MatrNodePtr n, children[3];
    MatrPerson *t;

    // Initialize Queue that will Store All the Nodes whose Memory will be Deallocated
    QueueLinkedList<MatrNodePtr> *nodes = new QueueLinkedList<MatrNodePtr>(NULL);

    // Get Root Node
    n = this->root;
    nodes->push(n);

    while (!nodes->isEmpty())
    {
      // Get First Node
      n = nodes->dequeue();

      // Get n's Children
      children[0] = n->lChild;
      children[1] = n->mChild;
      children[2] = n->rChild;

      for (int i = 0; i < 3; i++)
      {
        // Check if the Child Exists
        if (children[i] == NULL)
          continue;

        // Set Mother Attribute as NULL
        children[i]->mother = NULL;

        // Push n's Child
        nodes->enqueue(children[i]);
      }

      // Deallocate Parent Data and Node
      t = n->data;
      n->data = NULL;
      delete t;
      delete n;
    }

    // Deallocate Memory
    delete nodes;
  }

  // Public Methods
  bool isValid();
  void readFile();
  void levelOrderParents() { root->levelOrderParents(); };
  void levelOrderWomen() { root->levelOrderWomen(); };
  void levelOrderMen() { root->levelOrderMen(); };
  void levelOrderSingle() { root->levelOrderSingle(); };
  void levelOrderNoKids() { root->levelOrderNoKids(); };
  void levelOrderCousins() { root->levelOrderCousins(); };
  void levelOrderDivorce() { root->levelOrderDivorce(); };
};

// Getters

// Method to Check if the Tree is Valid or not
bool MatrTree::isValid()
{
  return this->valid;
}

// Setters

// Method to Set the Tree as Invalid
void MatrTree::setInvalid()
{
  this->valid = false;
}

// Method to Read matriarchy.csv File
void MatrTree::readFile()
{
  bool isMotherConsanguinity = false;
  int nodePos, partnerNodeId;
  string name, partnerName, motherName;
  MatrPerson *rootPartnerData, *motherData, *childData;
  MatrNodePtr t, motherNode, grandMotherNode, childNode;
  matriarchy::genders gender;

  string line, word, genderStr;
  int nodeCounter, wordCounter, lineCounter, genderSepIndex;

  // Stack that Contains the Nodes to Insert
  StackLinkedList<MatrNodePtr> *nodes = new StackLinkedList<MatrNodePtr>(NULL);

  ifstream matriarchyCSV(matriarchy::matriarchyFilename);

  if (!matriarchyCSV.is_open()) // Couldn't Access to matriarchyCSV
  {
    matriarchyCSV.close();
    pressEnterToCont("Error: File Not Found. Press ENTER to go Back to Main Menu", true);

    // Set the Tree as Invalid. There was an error with the 'matriarchy.csv' File
    this->setInvalid();
    return;
  }

  // Ignore Header
  getline(matriarchyCSV, line);

  lineCounter = 0;
  while (getline(matriarchyCSV, line)) // Get Nodes
    try
    {
      if (line.length() == 0)
        continue;

      stringstream file(line);

      wordCounter = 0;
      while (getline(file, word, files::nodeSep))
      {
        if (word.length() == 0)
          continue;

        // Get Name
        genderSepIndex = word.find(files::genderSep);
        name = word.substr(0, genderSepIndex);

        // Get Gender
        genderStr = word.substr(genderSepIndex + 1, 1);
        gender = (genderStr == "W") ? matriarchy::woman : matriarchy::man;

        if (lineCounter > 0)
        {
          if (wordCounter == 0)
            // Get the Mother's Partner Name
            partnerName = name;

          else if (wordCounter == 1)
          {
            // Get the Mother Name
            motherName = name;

            // Check if the Mother has Consanguinity with the Grandmother
            while (!nodes->isEmpty())
            {
              // Get Stack's Top Node
              t = nodes->pop();

              if (t->data->getName() == partnerName)
              {
                isMotherConsanguinity = false;
                break;
              }

              else if (t->data->getName() == motherName)
              {
                isMotherConsanguinity = true;
                break;
              }

              // Check if the Stack is Empty
              if (nodes->isEmpty())
                // Set the Tree as Invalid. There was an error with the 'matriarchy.csv' File
                this->setInvalid();
            }

            // If She has Consanguinity with the Grandmother, Add its Partner Relationship
            if (isMotherConsanguinity)
            {
              motherNode = t;
              MatrPerson *partnerData = motherNode->data;

              // Set Partner's Data
              MatrPerson *partnerDataPtr = new MatrPerson(partnerData->getNodeId(), partnerName, false, matriarchy::man, partnerData);
              motherNode->data->setPartner(partnerDataPtr);
            }

            // If She doesn't have Consanguinity with the Grandmother, Replace his Partner Node with her
            else
            {
              // Get Partner's Data and Partner's Mother Node
              MatrPerson *partnerData = t->data;
              partnerNodeId = t->data->getNodeId();
              grandMotherNode = t->mother;

              // Get Node Position
              if (grandMotherNode->lChild->data->getNodeId() == partnerNodeId)
                nodePos = 0;

              else if (grandMotherNode->mChild->data->getNodeId() == partnerNodeId)
                nodePos = 1;

              else if (grandMotherNode->rChild->data->getNodeId() == partnerNodeId)
                nodePos = 2;

              // Remove the Partner Node Relationship with his Mother
              t->makeOrphan();

              // Create the Mother Object
              motherData = new MatrPerson(partnerData->getNodeId(), motherName, false, matriarchy::woman, partnerData);

              // Set the Relationship
              partnerData->setPartner(motherData);

              // Create Mother Node
              motherNode = new MatrNode(motherData, grandMotherNode);

              // Put the New Node Back to its Mother
              if (nodePos == 0)
                grandMotherNode->lChild = motherNode;

              else if (nodePos == 1)
                grandMotherNode->mChild = motherNode;

              else if (nodePos == 2)
                grandMotherNode->rChild = motherNode;
            }
          }

          else
          {
            // Create the Next Generation Nodes
            childData = new MatrPerson(nodeCounter++, name, true, gender);

            // Create Child Node
            childNode = new MatrNode(childData, motherNode);

            // Set the Mother-Child Relationship
            if (wordCounter == 2)
              motherNode->lChild = childNode;

            else if (wordCounter == 3)
              motherNode->mChild = childNode;

            else
              motherNode->rChild = childNode;

            // Push to Stack
            nodes->push(childNode);
          }
        }

        else if (lineCounter == 0 && wordCounter > 1)
        {
          // Create the First Generation Nodes Objects
          childData = new MatrPerson(nodeCounter++, name, true, gender);

          // Create Child Node
          childNode = new MatrNode(childData, motherNode);

          // Set the Mother-Child Relationship
          if (wordCounter == 2)
            motherNode->lChild = childNode;

          else if (wordCounter == 3)
            motherNode->mChild = childNode;

          else
            motherNode->rChild = childNode;

          // Push to Stack
          nodes->push(childNode);
        }

        else if (lineCounter == 0 && wordCounter < 2)
          if (wordCounter == 0)
            // Create the Root Partner Object
            rootPartnerData = new MatrPerson(nodeCounter, name, false, matriarchy::man);

          else
          {
            // Create the Root Mother Object
            motherData = new MatrPerson(nodeCounter++, name, true, matriarchy::woman, rootPartnerData);

            // Set the Relationship
            rootPartnerData->setPartner(motherData);

            // Create the Root Mother Node
            motherNode = new MatrNode(motherData);

            // Set the Root Mother Node
            this->root = motherNode;

            // Push to Stack
            nodes->push(motherNode);
          }

        wordCounter++;
      }
      lineCounter++;
    }
    catch (...)
    {
      // It will Ignore the Line that was Read from matriarchy.csv
    }

  matriarchyCSV.close();
}

#endif