#include <iostream>
#include <iomanip>
#include <sstream>

#include "../../../../submodules/udemy-dsa-cpp/data-structures/queue/base.h"
#include "../terminal/cols.h"
#include "../terminal/input.h"
#include "../namespaces.h"

using std::cin;
using std::cout;
using std::getline;
using std::ostringstream;
using std::setfill;
using std::setw;

using namespace terminal;
using namespace matriarchy;

#ifndef MATR_NODE
#define MATR_NODE

// MATRIARCHY PERSON CLASS

class MatrPerson
{
private:
  int nodeId;
  string name;
  bool consanguinity;
  matriarchy::genders gender = matriarchy::genders::genderNull;
  MatrPerson *partner = NULL;

public:
  // Constructors
  MatrPerson();
  MatrPerson(int, string, bool, matriarchy::genders, MatrPerson *);

  // Public Methods
  int getNodeId();
  string getName();
  bool getConsanguinity();
  matriarchy::genders getGender();
  MatrPerson *getPartner();
  void setPartner(MatrPerson *);
};

// MATRIARCHY NODE CLASS
// Self-Referential Structure

class MatrNode
{
protected:
  // Protected Methods
  void addRootHeaderToStream(ostringstream *);
  void addRootDataToStream(ostringstream *, int, MatrPerson *);
  void addChildHeaderToStream(ostringstream *);
  void addChildDataToStream(ostringstream *, int, int, MatrPerson *);

  MatrNode *searchNode(int *, QueueLinkedList<MatrNode *> *, string);
  void levelOrder(MatrNode *, matriarchy::traversals);
  void levelOrderParents(int, QueueLinkedList<MatrNode *> *, ostringstream *);
  void levelOrderWomen(int, QueueLinkedList<MatrNode *> *, ostringstream *);
  void levelOrderMen(int, QueueLinkedList<MatrNode *> *, ostringstream *);
  void levelOrderSingle(int, QueueLinkedList<MatrNode *> *, ostringstream *);
  void levelOrderNoKids(int, QueueLinkedList<MatrNode *> *, ostringstream *);

public:
  MatrNode *mother = NULL;
  MatrPerson *data = NULL;
  MatrNode *lChild = NULL; // Left Child
  MatrNode *mChild = NULL; // Middle Child
  MatrNode *rChild = NULL; // Right Child

  // Constructors
  MatrNode();
  MatrNode(MatrPerson *);
  MatrNode(MatrPerson *, MatrNode *);

  // Public Methods
  void makeOrphan();
  void levelOrderParents() { this->levelOrder(this, matriarchy::parents); };
  void levelOrderWomen() { this->levelOrder(this, matriarchy::women); };
  void levelOrderMen() { this->levelOrder(this, matriarchy::men); };
  void levelOrderSingle() { this->levelOrder(this, matriarchy::single); };
  void levelOrderNoKids() { this->levelOrder(this, matriarchy::noKids); };
  void levelOrderCousins() { this->levelOrder(this, matriarchy::cousins); };
  void levelOrderDivorce() { this->levelOrder(this, matriarchy::divorce); };
};

// MatrNodePtr Definition
using MatrNodePtr = MatrNode *;

// MARTIARCHY PERSON CLASS

// Matriarchy Person Class Constructor
MatrPerson::MatrPerson()
{
  return;
}

MatrPerson::MatrPerson(int nodeId, string name, bool consanguinity, matriarchy::genders gender, MatrPerson *partner = NULL)
{
  // Assign Data
  this->nodeId = nodeId;
  this->consanguinity = consanguinity;
  this->name = name;
  this->gender = gender;
  this->partner = partner;
}

// Getters

// Method to Get Node ID
int MatrPerson::getNodeId()
{
  return this->nodeId;
}

// Method to Get Name
string MatrPerson::getName()
{
  return this->name;
}

// Method to Check whether the Person is Part of the Tree by Consanguinity or Affinity
bool MatrPerson::getConsanguinity()
{
  return this->consanguinity;
}

// Method to Get Gender
matriarchy::genders MatrPerson::getGender()
{
  return this->gender;
}

// Method to Get the Partner Information (It's a Matriarchy Tree...)
MatrPerson *MatrPerson::getPartner()
{
  return this->partner;
}

// Setters

// Method to Set the Node's Partner
void MatrPerson::setPartner(MatrPerson *partner)
{
  this->partner = partner;
}

// MATRIARCHY NODE CLASS

// Constructors
MatrNode::MatrNode()
{
  return;
}

MatrNode::MatrNode(MatrPerson *data)
{
  this->data = data;
}

MatrNode::MatrNode(MatrPerson *data, MatrNode *mother)
{
  this->data = data;
  this->mother = mother;
}

// Method to Add Root Node Header to a Given Stringstream
void MatrNode::addRootHeaderToStream(ostringstream *msg)
{
  // Root Header
  Col cols[4] = {
      Col("Level", terminal::nLevel),
      Col("Root Mother", terminal::nMotherId),
      Col("Name", terminal::nName),
      Col("Partner", terminal::nName)};

  // Create Title Linked List
  ColLinkedList *titleList = new ColLinkedList(cols, 4, Col());

  *msg << terminal::sgrBg << terminal::sgrFg << titleList->getText() << terminal::reset << '\n'
       << left;

  // Deallocate Memory
  delete titleList;
}

// Method to Add Root Node Data to a Given Stringstream
void MatrNode::addRootDataToStream(ostringstream *msg, int level, MatrPerson *root)
{
  // Get Root Node Partner
  MatrPerson *partner = root->getPartner();

  // Add Root Node Data
  *msg << setw(terminal::nLevel) << setfill(' ') << level
       << setw(terminal::nMotherId) << setfill(' ') << root->getNodeId()
       << setw(terminal::nName) << setfill(' ') << root->getName();

  if (partner != NULL)
  {
    string partnerName = partner->getName();
    *msg << setw(terminal::nName) << setfill(' ') << partnerName;
  }
  *msg << '\n';
}

// Method to Add Child Nodes Header to a Given Stringstream
void MatrNode::addChildHeaderToStream(ostringstream *msg)
{
  // Node Header
  Col cols[8] = {
      Col("Level", terminal::nLevel),
      Col("Mother Node", terminal::nMotherId),
      Col("Node", terminal::nNodeId),
      Col("Gender", terminal::nGender),
      Col("Name", terminal::nName),
      Col("Status", terminal::nStatus),
      Col("Consanguinity", terminal::nConsanguinity),
      Col("Partner", terminal::nName)};

  // Create Title Linked List
  ColLinkedList *titleList = new ColLinkedList(cols, 8, Col());

  // Add Node Header
  *msg << terminal::sgrBg << terminal::sgrFg << titleList->getText() << terminal::reset << '\n'
       << left;

  // Deallocate Memory
  delete titleList;
}

// Method to Add Child Node Data to a Given Stringstream
void MatrNode::addChildDataToStream(ostringstream *msg, int motherId, int level, MatrPerson *person)
{
  char status, consanguinity, gender;
  string partnerName;

  // Get Genders
  gender = person->getGender();

  // Get Status
  if (gender == matriarchy::man)
  {
    gender = matriarchy::manAbbr;
    status = (person->getPartner() != NULL) ? matriarchy::marriedAbbr : matriarchy::singleAbbr;
    consanguinity = matriarchy::consanguinityAbbr;
    partnerName = "";
  }

  else
  {
    gender = matriarchy::womanAbbr;

    MatrPerson *partner = person->getPartner();
    status = (partner != NULL) ? matriarchy::marriedAbbr : matriarchy::singleAbbr;
    consanguinity = (person->getConsanguinity()) ? matriarchy::consanguinityAbbr : matriarchy::affinityAbbr;
    partnerName = (partner != NULL) ? partner->getName() : "";
  }

  // Add Child Node Data
  *msg << setw(terminal::nLevel) << setfill(' ') << level
       << setw(terminal::nMotherId) << setfill(' ') << motherId
       << setw(terminal::nNodeId) << setfill(' ') << person->getNodeId()
       << setw(terminal::nGender) << setfill(' ') << gender
       << setw(terminal::nName) << setfill(' ') << person->getName()
       << setw(terminal::nStatus) << setfill(' ') << status
       << setw(terminal::nConsanguinity) << setfill(' ') << consanguinity
       << setw(terminal::nName) << setfill(' ') << partnerName << '\n';
}

// Method to Make the Node Orphan
void MatrNode::makeOrphan()
{
  MatrNodePtr children[3];
  int orphanNodeId = this->data->getNodeId();

  // Get Node's Mother
  MatrNodePtr mother = this->mother;

  // Remove the Mother-Child Realtionship
  if (mother->lChild->data->getNodeId() == orphanNodeId)
    mother->lChild = NULL;

  else if (mother->mChild->data->getNodeId() == orphanNodeId)
    mother->mChild = NULL;

  else if (mother->rChild->data->getNodeId() == orphanNodeId)
    mother->rChild = NULL;
}

// Method to Print the Nodes through Different Types of Level Order Traversal
void MatrNode::levelOrder(MatrNodePtr n, matriarchy::traversals traversal)
{
  bool printMsg;
  int level;
  string name, partnerName;
  MatrNodePtr searchNode, child, children[2], motherBrothers[2], cousins[6];
  MatrPerson *t;
  ostringstream msg;

  QueueLinkedList<MatrNodePtr> *nodes = new QueueLinkedList<MatrNodePtr>(NULL);

  // Push Node to Queue
  nodes->push(n);
  level = 0;

  // Add Root Header to Stream
  msg << terminal::clear;
  this->addRootHeaderToStream(&msg);

  // Add Root Node Data to Stream
  this->addRootDataToStream(&msg, level, n->data);
  msg << '\n';

  // Add Nodes Child Header to Stream
  this->addChildHeaderToStream(&msg);

  // Traverse the Matriarchy Tree
  switch (traversal)
  {
  case matriarchy::parents:
    printMsg = true;
    this->levelOrderParents(level, nodes, &msg);
    break;

  case matriarchy::women:
    printMsg = true;
    this->levelOrderWomen(level, nodes, &msg);
    break;

  case matriarchy::men:
    printMsg = true;
    this->levelOrderMen(level, nodes, &msg);
    break;

  case matriarchy::single:
    printMsg = true;
    this->levelOrderSingle(level, nodes, &msg);
    break;

  case matriarchy::noKids:
    printMsg = true;
    this->levelOrderNoKids(level, nodes, &msg);
    break;

  case matriarchy::cousins:
    printMsg = false;

    // Get Node Name to be Searched
    cout << "\nName to Search: ";
    getline(cin, name);

    // Search for the Given Node Name
    searchNode = this->searchNode(&level, nodes, name);

    // Check if the Node was Found
    if (searchNode == NULL)
      pressEnterToCont("\nNode not Found", true);

    // Check if the Node can have Aunts/Uncles
    else if (searchNode->mother == NULL)
      pressEnterToCont("\nNode doesn't have Aunts/Uncles", true);

    // Check if the Node can have Cousins
    else if (searchNode->mother->mother == NULL)
      pressEnterToCont("\nNode doesn't have Cousins", true);

    else
    {
      printMsg = true;

      // Get Child's Mother
      n = searchNode->mother;

      // Get Child's Grandmother
      n = n->mother;

      // Get Child's Aunts/Uncles
      if (n != NULL)
      {
        motherBrothers[0] = (n->lChild->data != searchNode->mother->data) ? n->lChild : n->rChild;
        motherBrothers[1] = (n->mChild->data != searchNode->mother->data) ? n->mChild : n->rChild;

        // Get Child's Cousins
        for (int i = 0; i < 2; i++)
        {
          cousins[i * 3] = motherBrothers[i]->lChild;
          cousins[i * 3 + 1] = motherBrothers[i]->mChild;
          cousins[i * 3 + 2] = motherBrothers[i]->rChild;
        }

        for (int i = 0; i < 6; i++)
          // Add Child's Cousin Data to the Given Stream
          if (cousins[i] != NULL)
            this->addChildDataToStream(&msg, searchNode->data->getNodeId(), level, cousins[i]->data);
      }
    }
    break;

  case matriarchy::divorce:
    printMsg = false;

    // Get Node Name to be Searched
    cout << "\nName to Search: ";
    getline(cin, name);

    // Search for the Given Node Name
    searchNode = this->searchNode(&level, nodes, name);

    if (searchNode == NULL)
      pressEnterToCont("\nNode not Found", true);

    else if (searchNode->data->getPartner() == NULL)
      pressEnterToCont("\nPartner doesn't have a Partner", true);

    else
    {
      name = searchNode->data->getName();
      partnerName = searchNode->data->getPartner()->getName();

      // Check if the Bond can be Broken. Just an Easter Egg
      if (getLower(name).find("ivana") != string::npos && getLower(partnerName).find("ramon") != string::npos)
      {
        pressEnterToCont("\nThe Bond can't be Broken", true);
        break;
      }

      // Get the Old Partner Data, and Divorce the Nodes
      t = searchNode->data->getPartner();
      searchNode->data->setPartner(NULL);

      // Deallocate Memory Occupied by the Old Partner
      delete t;
    }

    break;
  }

  // Print Level Order Traversal
  if (printMsg)
    cout << msg.str();

  // Deallocate Memory
  delete nodes;
}

// Method to Add the Parent-Child Relationship to a Given Stringstream
void MatrNode::levelOrderParents(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Check if the Child Exists
      if (children[i] == NULL)
        continue;

      // Get Child Data
      child = children[i]->data;

      // Add Child Data to Stream
      this->addChildDataToStream(msg, nId, level, child);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

// Method to Print Only Women through Level Order Traversal
void MatrNode::levelOrderWomen(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Check if the Child Exists
      if (children[i] == NULL)
        continue;

      // Get Child Data
      child = children[i]->data;

      // Check if It's a Woman
      if (child->getGender() == matriarchy::woman)
        // Add Child Data to Stream
        this->addChildDataToStream(msg, nId, level, child);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

// Method to Print Only Men through Level Order Traversal
void MatrNode::levelOrderMen(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child, *partner;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Check if the Child Exists
      if (children[i] == NULL)
        continue;

      // Get Child Data
      child = children[i]->data;
      partner = child->getPartner();

      // Check if It's a Man
      if (child->getGender() == matriarchy::man)
        // Add Child Data to Stream
        this->addChildDataToStream(msg, nId, level, child);

      // Check if It's a Woman and if She's Married
      else if (child->getGender() == matriarchy::woman && partner != NULL)
        // Add Woman's Partner Data to Stream
        this->addChildDataToStream(msg, nId, level, partner);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

// Method to Print Only Single Nodes through Level Order Traversal
void MatrNode::levelOrderSingle(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child, *partner;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Check if the Child Exists
      if (children[i] == NULL)
        continue;

      // Get Child Data
      child = children[i]->data;

      // Check if It's Single
      if (child->getPartner() == NULL)
        // Add Child Data to Stream
        this->addChildDataToStream(msg, nId, level, child);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

// Method to Print Only the Couples that have No Kids through Level Order Traversal
void MatrNode::levelOrderNoKids(int level, QueueLinkedList<MatrNodePtr> *nodes, ostringstream *msg)
{
  int nextNodesLevel, currNodesLevel, nId;
  MatrNodePtr n, children[3];
  MatrPerson *child, *partner;

  nextNodesLevel = 1;
  level = currNodesLevel = 0;

  while (!nodes->isEmpty())
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      level++;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3; i++)
    {
      // Check if the Child Exists
      if (children[i] == NULL)
        continue;

      // Get Child Data
      child = children[i]->data;

      // Check if It's a Woman and have no kids
      if (child->getGender() == matriarchy::woman)
        if (children[i]->lChild == NULL && children[i]->mChild == NULL && children[i]->rChild == NULL)
          this->addChildDataToStream(msg, nId, level, child);

      // Push n's Child
      nodes->enqueue(children[i]);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }
}

// Method to Search for a Given Node
MatrNodePtr MatrNode::searchNode(int *level, QueueLinkedList<MatrNodePtr> *nodes, string name)
{
  bool found = false;
  int nextNodesLevel, currNodesLevel, nId;
  MatrPerson *partner;
  MatrNodePtr n, child, children[2], motherBrothers[2], cousins[6];

  nextNodesLevel = 1;
  *level = currNodesLevel = 0;

  // Check if the Root Node is the One that's being Searched
  child = nodes->first();
  partner = child->data->getPartner();

  // Check if It's the Root Mother
  found = child->data->getName() == name;
  if (found)
    return nodes->dequeue();

  // Check if It's the Root Mother Partner
  if (partner != NULL)
  {
    found = partner->getName() == name;
    if (found)
      return nodes->dequeue();
  }

  while (!nodes->isEmpty() && !found)
  {
    // Get the Number of Nodes in the Current Tree Level. Increase the Level Counter
    if (currNodesLevel == 0)
    {
      currNodesLevel = nextNodesLevel;
      nextNodesLevel = 0;
      *level += 1;
    }

    // Get First Node
    n = nodes->dequeue();
    nId = n->data->getNodeId();

    // Get n's Children
    children[0] = n->lChild;
    children[1] = n->mChild;
    children[2] = n->rChild;

    for (int i = 0; i < 3 && !found; i++)
    {
      // Check if the Child Exists
      if (children[i] == NULL)
        continue;

      // Get Child
      child = children[i];
      partner = child->data->getPartner();

      // Check if It's the Node that's being Searched
      found = child->data->getName() == name;
      if (found)
        return child;

      // Check if It's the Partner of the Node that's being Searched
      if (partner != NULL)
      {
        found = partner->getName() == name;
        if (found)
          return child;
      }

      // Push n's Child
      nodes->enqueue(child);

      // Increase the Next Level Nodes Counter
      nextNodesLevel++;
    }

    // Decrease the Number of Nodes on the Current Level
    currNodesLevel--;
  }

  return NULL;
}

#endif