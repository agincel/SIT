#include "MySBBST.hh"
#include <cstdlib>
using namespace std;


int main(int argc, char **argv)
{
  int i;
  student *sarr[5];

  if (argc < 2)
    {
      student nope;
      MySBBST<student, unsigned int, studentStudentComp, uintStudentComp> tree(nope);
      sarr[0] = new student("bob", "marley", 1);
      sarr[1] = new student("sid", "vicious", 2);
      sarr[2] = new student("kurt", "cobain", 6);
      sarr[3] = new student("Darth", "Bewchy", 4);
      sarr[4] = new student("Foo", "Fighter", 5);

	  for (i = 0; i < 5; i++)
	  {
		  tree.add(*sarr[i]);
		  tree.add(*sarr[4 - i]);
		  tree.printout();
	  }
		

	  
	  tree.add(*sarr[2]);
	  tree.printout();
	  cout << tree.search(2) << endl;
	  cout << tree.remove(2) << endl;
	  tree.printout();

	  cout << endl << endl;

	  cout << "Testing sending zero values:";

	  cout << "search for 0: " << tree.search(0) << endl;
	  cout << "remove 0: " << tree.remove(0) << endl;

	  cout << "adding nope then printing the tree: " << endl;
	  tree.add(nope);
	  tree.printout();

	  cout << "adding 500 Darth Bewchy students: " << endl << endl;

	  for (int i = 0; i < 500; i++)
	  {
		  tree.add(*sarr[3]);
	  }

	  tree.printout();

	  if (tree.isValidTree())
		  cout << "Tree is valid! :D" << endl << endl;
	  else
		  cout << "Tree is invalid. :(" << endl << endl;
    }
  else
    {
	  MySBBST<int, int, intintCompare, intintCompare> tree(-2147483647);

    for (i = 1; i < argc; i++)
	{
	  tree.add(atoi(argv[i]));
	  tree.printout();
	  cout << endl << "=============" << endl;
	}

	tree.printout();
	cout << endl;
	if (tree.isValidTree())
		cout << "Tree is valid!";
	else
		cout << "Tree is invalid. :(";

	cout << endl << "---------------" << endl;

	cout << tree.search(43) << " " << tree.search(-1) << endl;
	cout << tree.remove(43) << endl;
	cout << tree.search(43);

	cout << endl << endl;

	cout << "Testing sending zero values:";

	cout << "search for zero: " << tree.search(-2147483647) << endl;
	cout << "remove zero: " << tree.remove(-2147483647) << endl;

	cout << "adding zero value then printing the tree: " << endl;
	tree.add(-2147483647);
	tree.printout();

	cout << "adding the number 42 500 times: " << endl << endl;

	for (i = 0; i < 500; i++)
	{
		tree.add(42);
	}

	tree.printout();

	if (tree.isValidTree())
		cout << "Tree is valid!" << endl << endl;
	else
		cout << "Tree is invalid. :(" << endl << endl;

    }

  return 0;
}
