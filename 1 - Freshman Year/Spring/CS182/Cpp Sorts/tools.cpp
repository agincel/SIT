#include "sorting.hh"

template void Sortings<int, intintCompare>::swap(int*, unsigned int, unsigned int);
template void Sortings<char*, strstrCompare>::swap(char**, unsigned int, unsigned int);

template <class Elem, class Comp>
void Sortings<Elem, Comp>::swap(Elem* arr, unsigned int x, unsigned int y)
{
	Elem temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}
