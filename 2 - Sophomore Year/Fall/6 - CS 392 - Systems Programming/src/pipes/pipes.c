#include "my.h"

int main(int argc, char *argv[])
{
	int pipefds1[2], pipefds2[2];
	char *input = my_vect2str(&argv[1]);
	char *readIn = (char *)malloc(sizeof(char) * 1024);
	pid_t pID1, pID2;

  if(argc <= 1)
  {
    my_str("No command line arguments given. Usage: ./pipes string to print...\n");
    return 0;
  }

	if(pipe(pipefds1) < 0)
	{
		my_str("First pipe failed to be created.\n");
		exit(1);
	}

	pID1 = fork();
	if(pID1 > 0) /* this is the parent */
	{
		close(pipefds1[0]); /* parent cannot read */
		my_str("Parent (pID ");
		my_int(getpid());
		my_str("): ");
		my_str(input);
		my_char('\n');
		write(pipefds1[1], input, 1024);
		wait();
	}
	else if(pID1 < 0)
	{
		my_str("First fork failed.\n");
		free(readIn);
		exit(1);
	}
	else /* this is the child */
	{
		close(pipefds1[1]); /* child cannot write */
		read(pipefds1[0], readIn, 1024);
    if(pipe(pipefds2) < 0)
		{
			my_str("Second pipe failed to be created.\n");
			free(readIn);
			exit(1);
		}
		pID2 = fork();
		if(pID2 > 0) /* first child */
		{
      close(pipefds2[0]); /* c1 can't read */
			my_str("Child (pID ");
			my_int(getpid());
			my_str("): ");
			my_str(readIn);
			my_char('\n');

			write(pipefds2[1], readIn, 1024);
      wait();
			free(readIn);
      return 0;
		}
		else if(pID2 < 0)
		{
			my_str("Second fork failed.\n");
			free(readIn);
			exit(1);
		}
    else /* second child */
    {
      close(pipefds2[1]); /* c2 can't write */
      free(readIn);
      readIn = (char *)malloc(sizeof(char) * 1024);
      read(pipefds2[0], readIn, 1024);

			my_str("Grandchild (pID ");
			my_int(getpid());
			my_str("): ");
			my_str(readIn);
      my_str("\n\n");
			free(readIn);
      return 0;
    }
	}
	free(readIn);
  return 0;
}
