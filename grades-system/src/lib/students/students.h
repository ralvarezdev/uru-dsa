#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <limits.h>
#include <iomanip>
#include <fstream>

#include "../../../../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/base.h"
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
using namespace students;

#ifndef STUDENTS_LINKED_LISTS
#define STUDENTS_LINKED_LISTS

// STUDENT CLASS

class Student
{
private:
  int id = -1;
  string firstName = "";
  string lastName = "";
  string email = "";
  string gender = "";
  students::genders genderAbb = students::genders::genderNull;
  int grades[students::nCourses] = {-1};
  float prom = -1;

public:
  // Constructors
  Student();
  Student(int, string, string, string, string, int *);

  // Public Methods
  int getId();
  string getFirstName();
  string getLastName();
  string getEmail();
  string getGender();
  students::genders getGenderAbb();
  int getGrade(int);
  float getProm();
  void setGenderAbb();
  void generateFile();
};

// STUDENT LINKED LIST CLASS

class StudentLinkedList : public SingleLinkedList<Student>
{
public:
  // Inherit Constructors
  using SingleLinkedList<Student>::SingleLinkedList;

  // Constructors
  StudentLinkedList() : SingleLinkedList<Student>(Student()){};

  // Public Methods
  void insertionSort(Student);
  void print(int);
  void readFile();
  int linearSearch(int);
  int linearSearch(SingleNodePtr<Student>, int);
  void generateStudentFile(int);
  void overwriteCSV();
};

// STUDENT CLASS

// Student Class Constructors
Student::Student()
{
  return;
}

Student::Student(int id, string firstName, string lastName, string email, string gender, int *grades)
{
  // Assign Data
  this->id = id;
  this->firstName = firstName;
  this->lastName = lastName;
  this->email = email;
  this->gender = gender;

  // Assign Gender Abbreviation
  this->setGenderAbb();

  // Assign Grades
  float sum;
  for (int i = 0; i < students::nCourses; i++)
  {
    this->grades[i] = grades[i];
    sum += grades[i];
  }

  this->prom = sum / students::nCourses;
}

// Getters

// Method to Get ID
int Student::getId()
{
  return this->id;
}

// Method to Get First name
string Student::getFirstName()
{
  return this->firstName;
}

// Method to Get Last Name
string Student::getLastName()
{
  return this->lastName;
}

// Method to Get Email
string Student::getEmail()
{
  return this->email;
}

// Method to Get Gender
string Student::getGender()
{
  return this->gender;
}

// Method to Get Gender Abbreviation
students::genders Student::getGenderAbb()
{
  return this->genderAbb;
}

// Method to Get Grade at Given Index
int Student::getGrade(int index)
{
  return this->grades[index];
}

// Method to Get Prom
float Student::getProm()
{
  return this->prom;
}

// Method to Set Gender Abbreviation
void Student::setGenderAbb()
{
  string genderLower = getLower(this->gender);

  // Check Gender
  if (genderLower == "female")
    this->genderAbb = students::genders::female;
  else if (genderLower == "male")
    this->genderAbb = students::genders::male;
  else
    this->genderAbb = students::genders::nonBinary;
};

// Method to Generate Student File
void Student::generateFile()
{
  ostringstream content, filename;

  // Get Filename
  filename << this->getId() << '-' << this->getFirstName() << '-' << this->getLastName() << ".txt";
  ofstream studentFile(filename.str());

  // Add Student Data
  content << "ID: " << this->getId() << '\n'
          << "First Name: " << this->getFirstName() << '\n'
          << "Last Name: " << this->getLastName() << '\n'
          << "Email: " << this->getEmail() << '\n'
          << "Gender: " << this->getGender() << '\n'
          << "Prom: " << this->getProm() << '\n'
          << "OOP: " << this->getGrade(0) << '\n'
          << "DSA: " << this->getGrade(1) << '\n'
          << "Databases: " << this->getGrade(2) << '\n'
          << "Math: " << this->getGrade(3) << '\n'
          << "Statistics: " << this->getGrade(4);

  studentFile << content.str(); // Write Content to Student File
  studentFile.close();          // STUDENT LINKED LIST CLASS
}

// STUDENT LINKED LIST CLASS

// Method to Insert in a Sorted Student Linked List
void StudentLinkedList::insertionSort(Student student)
{
  SingleNodePtr<Student> p, q, n;
  float pProm, studentProm;
  int compareFirstName, compareLastName;

  p = this->head;
  q = NULL;

  while (true)
  {
    q = p;
    p = p->next;

    // Reached Tail Node
    if (p == NULL)
      break;

    pProm = p->data.getProm();
    studentProm = student.getProm();

    // pProm is Less
    if (pProm < studentProm)
      break;
    // pProm is Equal is Equal to studentProm
    else if (pProm == studentProm)
    {
      compareFirstName = student.getLastName().compare(p->data.getLastName()) < 0;

      // Student whose Last Name is being Compared Must Go First
      if (compareFirstName < 0)
        break;
      // Student whose First Name is being Compared Must Go First
      else if (compareFirstName > 0)
      {
        compareLastName = student.getLastName().compare(p->data.getLastName());

        if (compareLastName < 0)
          break;
      }
    }
  }

  // Create new Node, and Insert between q and p Node
  n = new SingleNode(student);
  q->next = n;
  n->next = p;
}

// Method to Print Students
void StudentLinkedList::print(int max = INT_MAX)
{
  // Read students.csv
  if (this->length == 0)
    this->readFile();

  SingleNodePtr<Student> p = this->head->next;
  ostringstream message;

  Student student;
  students::genders genderAbb;
  int n = 0;

  message << left;

  // Prints from Head to Tail or max Students
  while (p != NULL && n < max)
  {
    student = p->data;

    // Add Student Data
    message << setw(nId) << setfill(' ') << student.getId()
            << setw(nFirstName) << setfill(' ') << student.getFirstName()
            << setw(nLastName) << setfill(' ') << student.getLastName();

    // Add Gender Abbreviation
    genderAbb = student.getGenderAbb();
    if (genderAbb == students::genders::female)
      message << setw(nGender) << setfill(' ') << "Female";
    else if (genderAbb == students::genders::male)
      message << setw(nGender) << setfill(' ') << "Male";
    else
      message << setw(nGender) << setfill(' ') << "Other";

    // Add Course Grades
    message << setw(nProm) << setfill(' ') << student.getProm();
    for (int i = 0; i < students::nCourses; i++)
      message << setw(nCourse) << setfill(' ') << student.getGrade(i);

    // Add New Line
    message << '\n';

    p = p->next;
    n++; // Increase Counter
  }

  cout << message.str();
}

// Method to Read students.csv File
void StudentLinkedList::readFile()
{
  string firstName, lastName, email, gender;
  int id, grades[students::nCourses];

  string line, word;
  int count, i;

  ifstream studentCSV(students::studentsFilename);

  if (!studentCSV.is_open()) // Couldn't Access to studentCSV
  {
    studentCSV.close();
    pressEnterToCont("Error: File Not Found. Press ENTER to go Back to Main Menu", true);
    return; // End this Function
  }

  // Remove Header
  getline(studentCSV, line);

  while (getline(studentCSV, line)) // Get Students
    try
    {
      if (line.length() == 0)
        continue;

      fill(grades, grades + students::nCourses, 0);

      stringstream file(line);

      i = count = 0;
      while (getline(file, word, sep))
      {
        if (word.length() != 0)
          switch (count)
          {
          case 0:
            id = stoi(word);
            break;
          case 1:
            firstName = word;
            break;
          case 2:
            lastName = word;
            break;
          case 3:
            email = word;
            break;
          case 4:
            gender = word;
            break;

          default:
            grades[i++] = stoi(word);
            break;
          }

        count++;
      }

      // Save Grades
      Student *newStudent = new Student(id, firstName, lastName, email, gender, grades);

      // Insert Student
      this->insertionSort(*newStudent);

      // Increment Counter
      this->increaseLength();
    }
    catch (...)
    {
      // It will Ignore the Line that was Read from movies.csv
    }

  studentCSV.close();
}

// Method that Checks if the Given ID is Inside Linked List
int StudentLinkedList::linearSearch(SingleNodePtr<Student> p, int id)
{
  int pos = 0;
  Student student;

  while (p != NULL)
  {
    if (id == p->data.getId())
    {
      cout << '\n';
      printTitle("Student Found");

      // Get Student
      student = p->data;

      cout << "ID: " << id << '\n'
           << "First Name: " << student.getFirstName() << '\n'
           << "Second Name: " << student.getLastName() << '\n'
           << "Email: " << student.getEmail();

      return pos;
    }
    p = p->next;
    pos++;
  }

  return -1;
}

// Method Overload
int StudentLinkedList::linearSearch(int id)
{
  return this->linearSearch(this->head->next, id); // Set Head Node as p Node
}

// Method to Generate Student File
void StudentLinkedList::generateStudentFile(int pos)
{
  SingleNodePtr<Student> p;

  // Move pos Nodes
  p = this->move(this->head->next, pos);

  // Generate Student File
  p->data.generateFile();
}

// Method to Overwite students.csv
void StudentLinkedList::overwriteCSV()
{
  SingleNodePtr<Student> p;
  Student student;

  ostringstream content;
  ofstream studentsCSV(students::studentsFilename);

  // Get Initial Nodes
  p = this->head->next;

  content << "id,first_name,last_name,email,gender,oop,dsa,databases,math,statistics\n"; // Overwrite Header
  while (p != NULL)
  {
    student = p->data; // Get Student

    // Add Student Data
    content << student.getId() << sep
            << student.getFirstName() << sep
            << student.getLastName() << sep
            << student.getEmail() << sep
            << student.getGender();

    for (int i = 0; i < students::nCourses; i++)
      content << sep << student.getGrade(i);

    content << '\n';

    // Move to Next Node
    p = p->next;
  }

  studentsCSV << content.str(); // Write Content to students.csv
  studentsCSV.close();
}

#endif