#include "sorting.hh"
#include <cstdlib>
using namespace std;


/*
	Adam Gincel
	CS182 Programming Assignment 2
	C++ Sorts: Selection, Radix, and Quick Sort.

	I pledge my honor that I have abided by the Stevens Honor System.
*/


int main(int argc, char **argv)
{
  int i = 0;
  if (argc > 3)
    {
      switch (argv[1][0])
	{
	case 'i':
	  int iarr[argc - 2];
	  for (i = 2; i < argc; i++)
	    iarr[i - 2] = atoi(argv[i]);
	  
	  //Sortings<int, intintCompare>::select(iarr, argc - 2); // selection sort
	  Sortings<int, intuival>::radix(iarr, argc - 2); //radix sort
	  //Sortings<int, intintCompare>::quick(iarr, argc - 2); //quick sort

	  //Sortings<int, intintCompare>::quick(NULL, argc - 2); //quick sort

	  for (i = 0; i < argc - 2; i++)
	    {
	      cout << iarr[i] << " ";
	    }

	  cout << endl;
	  break;
	case 's':
	  char *sarr[argc - 2];
	  for (i = 2; i < argc; i++)
	    sarr[i - 2] = argv[i];
	  //Sortings<char*, strstrCompare>::select(sarr, argc - 2); // selection sort
	  Sortings<char*, strstrCompare>::quick(sarr, argc - 2); //quick sort
	  for (i = 0; i < argc - 2; i++)
	    {
	      cout << sarr[i] << " ";
	    }

	  cout << endl;
	  break;

	default:
	  i = -1;
	  cout << "Cannot sort that" << endl;
	}
    }
  else
    {
      cout << "Use: ./mysorts {i | s} item1 [item2] [item3] ..." << endl;
    }
  return 0;
}
