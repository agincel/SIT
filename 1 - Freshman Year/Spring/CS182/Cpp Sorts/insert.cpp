#include "sorting.hh"

template void Sortings<int, intintCompare>::insert(int*, unsigned int, unsigned int);
template void Sortings<char*, strstrCompare>::insert(char**, unsigned int, unsigned int);

template <class Elem, class Comp>
void Sortings<Elem, Comp>::insert(Elem *arr, unsigned int incr, unsigned int n)
{

}

template void Sortings<int, intintCompare>::insert(int*, unsigned int);
template void Sortings<char*, strstrCompare>::insert(char**, unsigned int);

template <class Elem, class Comp>
void Sortings<Elem, Comp>::insert(Elem *arr, unsigned int n)
{

}
