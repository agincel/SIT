#include "sorting.hh"

template void Sortings<int, intuival>::radix(int*, unsigned int);

using namespace std;

template <class Elem, class Comp>
void Sortings<Elem, Comp>::radix(Elem *arr, unsigned int n)
{	
	//sorts elements of arr from 0 to n using radix sort; only works on integers
	
	if (arr != NULL && n > 1)
	{
		cout << "Radix sort: " << endl;

		int *count = new int[RADIX];
		int *b = new int[RADIX];
		int exp = 0;
		int max = 0;
		int i = 0;

		for (i = 1, max = arr[0]; i < n; i++)
			if (Comp::uintVal(arr[i]) > Comp::uintVal(max))
				max = arr[i];

		for (exp = 1; (max / exp) >= RADIX; exp *= RADIX)
			;
		max = exp;



		for (exp = 1; exp <= max && exp > 0; exp *= RADIX)
		{
			for (i = 0; i < RADIX; i++)
				count[i] = 0; //fill array with 0s

			for (i = 0; i < n; i++)
				count[(Comp::uintVal(arr[i]) / exp) % RADIX]++; //increment number of instances of that value

			for (i = 1; i < RADIX; i++)
				count[i] += count[i - 1]; //shift

			for (i = n - 1; i >= 0; i--)
				b[--count[(Comp::uintVal(arr[i]) / exp) % RADIX]] = arr[i];

			for (i = 0; i < n; i++)
				arr[i] = b[i];
		}





	}



}
