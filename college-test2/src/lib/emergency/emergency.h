#include <iostream>
#include <fstream>
#include <sstream>

#include "../../../../submodules/udemy-dsa-cpp/data-structures/queue/base.h"

using namespace std;

#ifndef EMERGENCY_QUEUE
#define EMERGENCY_QUEUE

// Person Enum
enum person
{
  girl,
  boy,
  woman,
  man
};

class Emergency
{
public:
  int type;
  int person;

  // Constructors
  Emergency(){};
  Emergency(int, int);
};

// Emergency Constructors
Emergency::Emergency(int type, int person)
{
  this->type = type;
  this->person = person;
}

// EMERGENCY QUEUE LINKED LIST CLASS
// FIFO
// First-in, First-out

class EmergencyQueue : public QueueLinkedList<Emergency>
{
public:
  // Inherit Constructors
  using QueueLinkedList<Emergency>::QueueLinkedList;

  // Public Methods
  void insertionSort(Emergency); // Method that Overwrites the push Method Inherited by its Base Class
  void readFile();
  void pushBack();
  void print();
};

// Method to Push Emergencies
void EmergencyQueue::insertionSort(Emergency e)
{
  int iter = 0, length = this->getLength();

  // If it's Empty
  if (this->isEmpty())
  {
    this->enqueue(e);
    return;
  }

  // First Emergency
  Emergency first = this->first();

  // Compare Emergency to Push with the First One
  while (first.type < e.type && iter < length)
  {
    this->pushBack();
    first = this->first();

    iter++;
  }

  while (first.type == e.type && first.person <= e.person && iter < length)
  {
    this->pushBack();
    first = this->first();

    iter++;
  }

  // Push Emergency to Queue
  this->enqueue(e);

  // Get Queue Length
  length = this->getLength();

  // Push Left Emergencies at the Original Order with the One that was Inserted
  for (int i = 0; i < length - iter - 1; i++)
    this->pushBack();
}

// Method to Pop First Node and Pushed it Back
void EmergencyQueue::pushBack()
{
  Emergency t = this->dequeue();
  this->enqueue(t);
}

// Method to Insert Emergencies while Reading unknown.txt while
void EmergencyQueue::readFile()
{
  string line, word;
  int type, person, c;

  ifstream emergencies("unknown.txt");

  if (!emergencies.is_open())
  {
    cout << "File couldn't be Opened";
    return;
  }

  while (getline(emergencies, line))
  {
    stringstream file(line);

    // Get Emergency Type
    getline(file, word, ' ');
    type = word[0];

    while (getline(file, word, ' '))
    {
      // Get Person
      c = word[0];

      switch (c)
      {
      case 'm':
        person = person::boy;
        break;
      case 'f':
        person = person::girl;
        break;
      case 'M':
        person = person::man;
        break;
      case 'F':
        person = person::woman;
        break;
      }

      // Pushed Emergency to Queue
      this->insertionSort(Emergency(type, person));
    }
  }
}

// Method to Print Emergencies from Queue
void EmergencyQueue::print()
{
  Emergency e;
  int iter = 0;

  ostringstream output;

  output << "Emergencies:\n";

  while (iter != this->getLength())
  {
    // Get First Emergency
    e = this->dequeue();

    // Add Emergency to output
    output << '[' << char(e.type) << "] ";

    switch (e.person)
    {
    case person::girl:
      output << "Girl";
      break;
    case person::boy:
      output << "Boy";
      break;
    case person::woman:
      output << "Woman";
      break;
    case person::man:
      output << "Man";
      break;
    }

    // Push Back Emergency
    this->push(e);

    output << '\n';

    iter++;
  }

  cout << output.str();
}

#endif