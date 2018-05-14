#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include <string>
using namespace std;
/*
Adam Gincel
MySBBST.cpp
This file contains the implementations for the AVL Tree.

I pledge my honor that I have abided by the Stevens Honor System.
*/

class student
{
private:
  string name;
  string surname;
  unsigned int cwid;
public:
  student(string n, string s, unsigned int c)
  { name = n; surname = s; cwid = c; }
  student()
  { name = ""; surname = ""; cwid = 0;}

  friend ostream &operator<<(ostream &os, const student &s)
  { 
    return os << s.name << " " << s.surname << " " << s.cwid;
  }
  string getName() { return name; };
  string getSurname() { return surname; };
  unsigned int getCwid() { return cwid; };
};

class studentStudentComp
{
public:
  static bool lt(student s1, student s2)
  {
    return s1.getCwid() < s2.getCwid();
  }
  static bool gt(student s1, student s2)
  {
    return s1.getCwid() > s2.getCwid();
  }
  static bool eq(student s1, student s2)
  {
    return s1.getCwid() == s2.getCwid();
  }
};

class uintStudentComp
{
public:
  static bool lt(unsigned int s1, student s2)
  {
    return s1 < s2.getCwid();
  }
  static bool gt(unsigned int s1, student s2)
  {
    return s1 > s2.getCwid();
  }
  static bool eq(unsigned int s1, student s2)
  {
    return s1 == s2.getCwid();
  }
};

#endif
