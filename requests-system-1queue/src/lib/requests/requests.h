#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "../../../../submodules/udemy-dsa-cpp/data-structures/queue/base.h"
#include "../terminal/input.h"
#include "../terminal/ansiEsc.h"
#include "../namespaces.h"

using std::cout;
using std::fill;
using std::ifstream;
using std::left;
using std::ofstream;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;
using std::stringstream;

using namespace files;
using namespace terminal;
using namespace requests;

#ifndef REQUEST_QUEUE_LINKED_LIST
#define REQUEST_QUEUE_LINKED_LIST

// REQUEST CLASS

class Request
{
private:
  string firstName = "";
  string lastName = "";
  string title = "";
  string description = "";
  requests::priority priority = requests::priorityNull;

public:
  // Constructors
  Request();
  Request(string, string, string, string, requests::priority);

  // Public Methods
  string getFirstName();
  string getLastName();
  string getTitle();
  string getDescription();
  requests::priority getPriority();
  string getPriorityStr();
};

// REQUEST QUEUE LINKED LIST CLASS

class RequestQueueLinkedList : public QueueLinkedList<Request>
{
public:
  // Inherit Constructors
  using QueueLinkedList<Request>::QueueLinkedList;

  // Constructors
  RequestQueueLinkedList() : QueueLinkedList<Request>(Request()){};

  // Public Methods
  void moveBack();
  void insertByPriority(Request);
  void readFile();
  void print();
  void overwriteCSV();
};

// REQUESTS CLASS

// Request Class Constructors
Request::Request()
{
  return;
}

Request::Request(string firstName, string lastName, string title, string description, requests::priority priority)
{
  // Assign Data
  this->firstName = firstName;
  this->lastName = lastName;
  this->title = title;
  this->description = description;
  this->priority = priority;
}

// Getters

// Method to Get First Name
string Request::getFirstName()
{
  return this->firstName;
}

// Method to Get Last Name
string Request::getLastName()
{
  return this->lastName;
}

// Method to Get Description
string Request::getDescription()
{
  return this->description;
}

// Method to Get Title
string Request::getTitle()
{
  return this->title;
}

// Method to Get Priority
requests::priority Request::getPriority()
{
  return this->priority;
}

// Method to Get Priority as String
string Request::getPriorityStr()
{
  requests::priority priority = this->getPriority();

  switch (priority)
  {
  case requests::priority::directory:
    return "Directory";

  case requests::priority::subdirectory:
    return "Subdirectory";

  case requests::priority::professor:
    return "Professor";

  case requests::priority::associateProfessor:
    return "Assoc. Professor";

  case requests::priority::administration:
    return "Administration";

  case requests::priority::alumni:
    return "Alumni";

  default:
    return "NULL";
  }
}

// REQUEST QUEUE LINKED LIST CLASS

// Method to Pop First Node and Push it Back
void RequestQueueLinkedList::moveBack()
{
  // Temp Request
  Request temp;

  // Pop First Request
  temp = this->pop();

  // Push First Request to the End
  this->push(temp);
}

// Method to Push Node by Priority
void RequestQueueLinkedList::insertByPriority(Request request)
{
  // Request Priority
  requests::priority priority = request.getPriority();

  // Old Queue Length
  int oldLen = this->getLength();

  // Insert at the End
  if (priority == requests::priority::alumni || oldLen == 0)
  {
    this->push(request);
    return;
  }

  // Temp Requests
  Request prevRequest, nextRequest;

  // Temp Priorities
  requests::priority prevPriority, nextPriority;

  // First Iteration
  prevPriority = requests::priority::priorityNull;
  nextRequest = this->pop();
  nextPriority = nextRequest.getPriority();
  oldLen--;

  // Just One Request was in Queue
  if (oldLen == 0)
  {
    if (nextPriority >= priority)
    {
      this->push(nextRequest);
      this->push(request);
      return;
    }

    this->push(request);
    this->push(nextRequest);
    return;
  }

  // Move Nodes to auxQueue, until New Request can be Pushed at the Right Order and Priority Position
  for (; oldLen > 0 && nextPriority >= priority; oldLen--)
  {
    // Push Previous Request
    if (prevPriority != requests::priority::priorityNull)
      this->push(prevRequest);

    // Save Next Request and Priority as the Previous One
    prevRequest = nextRequest;
    prevPriority = nextPriority;

    // Get Top Request
    nextRequest = this->pop();
    nextPriority = nextRequest.getPriority();
  }

  // Push Previous Request
  if (prevPriority != requests::priority::priorityNull)
    this->push(prevRequest);

  // Push New Request
  this->push(request);

  // Push Next Request
  this->push(nextRequest);

  // Push Nodes Left to the End
  for (; oldLen > 0; oldLen--)
    // Move Node to the End
    this->moveBack();
}

// Method to Read requests.csv File
void RequestQueueLinkedList::readFile()
{
  string firstName, lastName, title, description;
  requests::priority priority;

  string line, word;
  int count;

  ifstream requestsCSV(requests::requestsFilename);

  if (!requestsCSV.is_open()) // Couldn't Access to requestsCSV
  {
    requestsCSV.close();
    pressEnterToCont("Error: File Not Found. Press ENTER to go Back to Main Menu", true);
    return; // End this Function
  }

  // Remove Header
  getline(requestsCSV, line);

  while (getline(requestsCSV, line)) // Get Requests
    try
    {
      if (line.length() == 0)
        continue;

      stringstream file(line);

      count = 0;
      while (getline(file, word, sep))
      {
        if (word.length() == 0)
          continue;

        switch (count)
        {
        case 0:
          firstName = word;
          break;

        case 1:
          lastName = word;
          break;

        case 2:
          title = word;
          break;

        case 3:
          if (word.at(0) == '"')
          {
            // Add Comma
            word += ',';

            // Get Missing Part from Description
            string temp;
            getline(file, temp, '"');

            // Add Double Quotes at the End
            temp += '"';

            // Append it
            word.append(temp);
          }

          description = word;
          break;

        case 4:
          priority = requests::priority(stoi(word));
          break;

        default:
          break;
        }

        count++;
      }

      // Save Request
      Request *newRequest = new Request(firstName, lastName, title, description, priority);

      // Insert Request
      this->insertByPriority(*newRequest);
    }
    catch (...)
    {
      // It will Ignore the Line that was Read from requests.csv
    }

  requestsCSV.close();
}

// Method to Overwite requests.csv
void RequestQueueLinkedList::overwriteCSV()
{
  SingleNodePtr<Request> p;
  Request request;

  // Old Queue Length
  int oldLen = this->getLength();

  ostringstream content;
  ofstream requestsCSV(requests::requestsFilename);

  content << "first_name,last_name,title,description,priority\n"; // Overwrite Header

  // Get All Nodes Data
  for (; oldLen > 0; oldLen--)
  {
    // Pop First Request
    request = this->pop();

    // Add Request Data
    content << request.getFirstName() << sep
            << request.getLastName() << sep
            << request.getTitle() << sep
            << request.getDescription() << sep
            << request.getPriority() << '\n';

    // Push First Request to the End
    this->push(request);
  }

  requestsCSV << content.str(); // Write Content to requests.csv
  requestsCSV.close();
}

// Method to Print All Requests
void RequestQueueLinkedList::print()
{
  Request request;
  string title, description;

  // Old Queue Length
  int oldLen = this->getLength();

  ostringstream content;

  // Set Text Alignment to the Left
  content << left;

  // Print All Nodes
  for (; oldLen > 0; oldLen--)
  {
    // Pop First Request from RequestQueueLinkedList
    request = this->pop();

    // Add Request Data
    content << setw(terminal::nFirstName) << setfill(' ') << request.getFirstName()
            << setw(terminal::nLastName) << setfill(' ') << request.getLastName();

    title = request.getTitle();
    if (title.length() < terminal::nTitle)
      content << setw(terminal::nTitle) << setfill(' ') << title;
    else
      content << title.substr(0, terminal::nTitle - 4) << "... ";

    description = request.getDescription();
    // Check if Description Contains Some Commas
    if (description.find(',') != string::npos)
      // Remove Double Quotes
      description = description.substr(1, description.length() - 2);

    if (description.length() < terminal::nDescription)
      content << setw(terminal::nDescription) << setfill(' ') << description;
    else
      content << description.substr(0, terminal::nDescription - 4) << "... ";

    content << setw(terminal::nPriority) << setfill(' ') << request.getPriorityStr()
            << '\n';

    // Push First Request to auxQueue
    this->push(request);
  }

  // Print Content
  cout << content.str();
}

#endif