#include "sorting.hh"

template void Sortings<int, intintCompare>::quick(int*, unsigned int);
template void Sortings<int, intintCompare>::quickRecurse(int*, unsigned int, unsigned int);
template unsigned int Sortings<int, intintCompare>::findPivot(int*, unsigned int, unsigned int);
template unsigned int Sortings<int, intintCompare>::partition(int*, unsigned int, unsigned int);


template void Sortings<char*, strstrCompare>::quick(char**, unsigned int);
template void Sortings<char*, strstrCompare>::quickRecurse(char**, unsigned int, unsigned int);
template unsigned int Sortings<char*, strstrCompare>::findPivot(char**, unsigned int, unsigned int);
template unsigned int Sortings<char*, strstrCompare>::partition(char**, unsigned int, unsigned int);

using namespace std;

template <class Elem, class Comp>
void Sortings<Elem, Comp>::quick(Elem *arr, unsigned int n)
{
	//general call for quicksort; does error checking then begins the recursive quicksort
	if (arr != NULL && n > 1)
	{
		cout << "Quick sort: " << endl;
		quickRecurse(arr, 0, n - 1);

	}
}

template <class Elem, class Comp>
void Sortings<Elem, Comp>::quickRecurse(Elem *arr, unsigned int l, unsigned int r)
{
	//recursive part of quicksort; partitions the array using a pivot, then checks if the left and right sides still need to be recursively called.

	partition(arr, l, r);

	//cout << "Recursive call L: " << l << " R: " << r << endl; //debugging

	

	
	
}

template <class Elem, class Comp>
unsigned int Sortings<Elem, Comp>::findPivot(Elem *arr, unsigned int l, unsigned int r)
{
	//choosing pivot as the midpoint of the array because this was causing me a million problems
	int pivot = (l + (r - l) / 2);

	//cout << "Pivot: " << pivot << endl; //debug
	return pivot;

	
	

	

}

template <class Elem, class Comp>
unsigned int Sortings<Elem, Comp>::partition(Elem *arr, unsigned int l, unsigned int r)
{
	//partitions the array; all elements less than pivot go left, all greater than go right
	
	int i = l;
	int j = r;

	Elem pivot = arr[findPivot(arr, l, r)];

	while (i <= j)
	{
		while (Comp::lt(arr[i], pivot)) //if elements on left are already where they should be, skip them
			i++;
		while (Comp::gt(arr[j], pivot)) //if elements on right are already where they should be, skip them
			j--;
		
		if (i <= j)
		{
			swap(arr, i, j);
			i++;
			j--;
		}
	}



	//cout << "Successfully partitioned. j: " << j << endl; //debug

	if (l < j)
		quickRecurse(arr, l, j); //if there is still a left partition to sort

	if (r > i)
		quickRecurse(arr, i, r);

	return i; //choosing to return i, the index after the left partition
	
}
