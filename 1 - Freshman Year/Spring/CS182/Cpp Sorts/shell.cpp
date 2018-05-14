#include "sorting.hh"

template void Sortings<int, intintCompare>::shell(int*, unsigned int);
template void Sortings<char*, strstrCompare>::shell(char**, unsigned int);

template <class Elem, class Comp>
void Sortings<Elem, Comp>::shell(Elem *arr, unsigned int n)
{
}
