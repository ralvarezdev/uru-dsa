#include <string>
#include <sstream>
#include <iomanip>

#include "../../../../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/base.h"
#include "ansiEsc.h"

using std::left;
using std::ostringstream;
using std::setfill;
using std::setw;

#ifndef COLS_LINKED_LISTS
#define COLS_LINKED_LISTS

// COL CLASS

class Col
{
private:
  string name = "";
  int width = -1;

public:
  // Constructors
  Col();
  Col(string, int);

  // Public Methods
  string getName();
  int getWidth();
};

// COL LINKED LIST CLASS

class ColLinkedList : public SingleLinkedList<Col>
{
public:
  // Inherit Constructors
  using SingleLinkedList<Col>::SingleLinkedList;

  // Constructors
  ColLinkedList() : SingleLinkedList<Col>(Col()){};

  // Public Methods
  void print();
};

// COL CLASS

// Col Class Constructors
Col::Col()
{
  return;
}

Col::Col(string name, int width)
{
  this->name = name;
  this->width = width;
}

// Getters
string Col::getName()
{
  return this->name;
}

int Col::getWidth()
{
  return this->width;
}

// COL LINKED LISTS CLASS

// Method to Print Columns Title, with Customed Width for each Field and Customed Colors
void ColLinkedList::print()
{
  SingleNodePtr<Col> p = this->head->next;
  ostringstream message;

  int width;
  string name;

  message << left;

  // Prints from Head to Tail
  while (p != NULL)
  {
    width = p->data.getWidth();
    name = p->data.getName();

    message << setw(width) << setfill(' ') << name;
    p = p->next;
  }

  // Print Title
  printTitle(message.str());
}

#endif