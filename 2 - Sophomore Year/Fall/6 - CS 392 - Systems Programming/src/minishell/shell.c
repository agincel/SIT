#include "my.h"
#include <dirent.h>

void startup()
{
	my_str("  __  __       _ _           _     _____ _          _ _ \n");
	my_str(" |  \\/  |     | | |         | |   / ____| |        | | |\n");
	my_str(" | \\  / | ___ | | |_   _ ___| | _| (___ | |__   ___| | |\n");
	my_str(" | |\\/| |/ _ \\| | | | | / __| |/ /\\___ \\| '_ \\ / _ \\ | |\n");
	my_str(" | |  | | (_) | | | |_| \\__ \\   < ____) | | | |  __/ | |\n");
	my_str(" |_|  |_|\\___/|_|_|\\__,_|___/_|\\_\\_____/|_| |_|\\___|_|_|\n\n\n\n");
}

char *inputClean(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return str;
}


int main()
{
	char *inputString;
	char **inputVector;
	char cwd[1024];
	int running = 1;
	startup();
	int error;
	pid_t pID;

	while(running == 1)
	{
		inputString = (char *)malloc(sizeof(char) * 1024);
		getcwd(cwd, sizeof(cwd));
		my_str(cwd);
		my_str("/> ");
		read(0, inputString, 1024);
		inputString = inputClean(inputString);
		inputVector = my_str2vect(inputString);

		if(my_strcmp(inputVector[0], "exit") == 0)
		{
			my_str("Bye!");
			running = 0;
		}
		else if(my_strcmp(inputVector[0], "pfeffer") == 0)
			my_str("The ride never ends...");
		else if(my_strcmp(inputVector[0], "cd") == 0)
		{
			if(inputVector[1] != NULL)
			{
				error = chdir(my_vect2str(inputVector + 1));
				if(error < 0)
				{
					my_str("-MolluskShell: cd: ");
					my_str(inputVector[1]);
					my_str(": Folder not found.");
				}

			}
			else
				my_str("-MolluskShell: cd: Specify a folder.");
		}
		else /* is exec-ing or wrong */
		{
			if(inputVector[0] != NULL)
			{
				pID = fork();
				if(pID == 0) /* this is the child process */
				{
					error = execvp(inputVector[0], inputVector);
					if(error < 0)
					{
						my_str("-MolluskShell: ");
						my_str(inputVector[0]);
						my_str(": Command not found.");
					}
					exit(0);
				}
				else if(pID < 0) /* fork failed? */
				{
					my_str("Fork failed?");
					exit(1); /* exit with error */
				}
				else	/* parent process, waiting for fork() to end */
				{
					wait(pID);
				}
			}
		}

		my_char('\n');
		free(inputString);
	}
}
