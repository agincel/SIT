#ifndef _SORTING_H_
#define _SORTING_H_

#include <iostream>
#include <cstring>
using namespace std;

template <class Elem, class Comp>
class Sortings
{
 public:
  static void merge(Elem *arr, unsigned int n); //not this
  static void quick(Elem *arr, unsigned int n); // do merge or this one
  static void select(Elem *arr, unsigned int n);
  static void insert(Elem *arr, unsigned int n); // do select or this one --not this
  static void shell(Elem *arr, unsigned int n); //not this
  static void radix(Elem *arr, unsigned int n); // do shell or this one
// when using radix, Comp should be a class
  // with a static method "uintVal(...)" that gives an unsigned int representation of the items
 private:
  // These are all optional, add or remove as functions as you need
  static const unsigned int THRESHOLD = 3; // used by shell (I also use it in merge & quick)
  static const unsigned int RADIX = 16; // used by radix
  static void insert(Elem *arr, unsigned int incr, unsigned int n); // used by shell
  static void swap(Elem *arr, unsigned int, unsigned int);
  static void mergeRecurse(Elem *arr, Elem tmp[], unsigned int l, unsigned int r); // used by merge
  static void quickRecurse(Elem *arr, unsigned int l, unsigned int r); // used by quick
  static unsigned int partition(Elem *arr, unsigned int l, unsigned int r); // used by quickRecurse
  static unsigned int findPivot(Elem *arr, unsigned int l, unsigned int r); // used by quickRecurse
};

class intuival
{
public:
  static unsigned int uintVal(int n);
};

class intintCompare
{
 public:
  static bool lt(int, int);
  static bool gt(int, int);
  static bool eq(int, int);
};

class strstrCompare
{
 public:
  static bool lt(char*, char*);
  static bool gt(char*, char*);
  static bool eq(char*, char*);  
};

#endif
