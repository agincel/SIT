#include "sorting.hh"

bool intintCompare::lt(int x, int y)
{
  return x < y;
}

bool intintCompare::gt(int x, int y)
{
	return x > y;
}

bool intintCompare::eq(int x, int y)
{
	return x == y;
}

bool strstrCompare::lt(char* s1, char* s2)
{
	return (strcmp(s1, s2) < 0);
}

bool strstrCompare::gt(char* s1, char* s2)
{
  return (strcmp(s1, s2) > 0);
}

bool strstrCompare::eq(char* s1, char* s2)
{
	return (strcmp(s1, s2) == 0);
}

unsigned int intuival::uintVal(int n)
{
  // hint: return the absolute value of n :-)
	if (n > 0)
		return n;
	else
		return n * -1;
}
