#include <iostream>
using namespace std;
int main()
{
	int num = -1;
	while(num != 42)
	{
		cin >> num;
		if (num != 42)
			cout << num << endl;
	}

	return 0;
}