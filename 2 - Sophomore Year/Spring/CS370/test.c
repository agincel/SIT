#include <stdio.h>
#include <stdlib.h>
int main()
{
	int *fp;
	char line[128];
	size_t len = 0;
	ssize_t read;

	int n = -1; /* number of input items */
	int k = -1; /* divisor */

	int currentNum = 0;
	int total = 0; /* total divided */

	int i = 0;


	/*
	fp = fopen("input.txt", "r");
	if (fp == NULL)
		exit(1);

	read = getline(&line, &len, fp);
	*/


	if (read != -1) /* get n and k */
	{
		/* read = "7 2" */
		scanf("%d %d", &n, &k);
	}
	else
	{
		exit(1);
	}

	while(i < n)
	{
		i++;
		scanf("%d", &currentNum);
		if (currentNum % k == 0)
			total++;
	}

	printf("%d", total);

	return 0;
}