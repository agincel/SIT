#include "sorting.hh"

template void Sortings<int, intintCompare>::merge(int*, unsigned int);
template void Sortings<int, intintCompare>::mergeRecurse(int*, int[], unsigned int, unsigned int);
template void Sortings<char*, strstrCompare>::merge(char**, unsigned int);
template void Sortings<char*, strstrCompare>::mergeRecurse(char**, char*[], unsigned int, unsigned int);

template <class Elem, class Comp>
void Sortings<Elem, Comp>::merge(Elem *arr, unsigned int n)
{
}

template <class Elem, class Comp>
void Sortings<Elem, Comp>::mergeRecurse(Elem *arr, Elem tmp[], unsigned int l, unsigned int r)
{

}

