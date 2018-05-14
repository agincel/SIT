#include "sorting.hh"

template void Sortings<int, intintCompare>::select(int*, unsigned int);
template void Sortings<char*, strstrCompare>::select(char**, unsigned int);

/*
	@author Adam Gincel
	@param arr - Array to be sorted
	@param n - number of items in arr to sort.

*/

using namespace std;

template <class Elem, class Comp>
void Sortings<Elem, Comp>::select(Elem *arr, unsigned int n)
{
	//sorts array from 0 to n using selection sort
	int i, j;
	int indexOfMinimum;

	//error checking
	if (arr != NULL && n > 1) //array not null, more than 1 element to sort
	{
		cout << "Selection sort: " << endl;
		for (i = 0; i < n; i++)
		{
			indexOfMinimum = i;
			for (j = i; j < n; j++)
				if (Comp::lt(arr[j], arr[indexOfMinimum]))
					indexOfMinimum = j;

			if (indexOfMinimum != i)
			{
				swap(arr, i, indexOfMinimum);
				//cout << "swapped " << i << " " << indexOfMinimum << endl;
			}
				
		}
	}

}
