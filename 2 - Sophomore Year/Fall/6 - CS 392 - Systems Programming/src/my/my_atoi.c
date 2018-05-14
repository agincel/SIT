/*
*	Adam Gincel
*	my_atoi.c
*	Pulls an integer out of a string.	
*
*	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include "my.h"

int my_atoi(char *str)
{
	int result = 0, i = 0, neg = 1, end = 0, numReached = 0;

	if(str == NULL)
		return 0;

	while(str[i] != '\0' && end == 0)
	{
		if((str[i] >= '0' && str[i] <= '9') || str[i] == '-') /* given character is valid digit or a - */
		{
			if(str[i] == '-')
			{
				if(numReached == 0)
					neg *= -1;
				else
					end = 1; /* if reaching hyphen after number, not valid. */
			}
			else
			{
				result *= 10;
				result += (int)(str[i] - '0');
				numReached = 1;
			}
		}else /* given character is not a digit or a - */
		{
			if(numReached != 0)
				end = 1;
		}

		i++;
	}

	if(numReached == 1)
	{
		result *= neg;
		return result;
	}else
		return 0;
}