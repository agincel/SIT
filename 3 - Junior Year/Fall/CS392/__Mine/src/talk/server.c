#include "my.h"
#include <signal.h>

char result = 0;
int clientPID = 0;
int waitingForString = 1;

int counter = 0;

void characterAssemble(int bit)
{
  result += bit << counter;
  counter++;
  if(counter == sizeof(char)*8)
  {
    if(result == 0) //result was null terminator, print \n
    {
       my_char('\n');
       waitingForString = 0;
    }
    else
      my_char(result);

    result = 0;
    counter = 0;
  }
}

void signal_one()
{
  characterAssemble(0);
}

void signal_two()
{
  characterAssemble(1);
}

void pidAssemble(int bit)
{
  clientPID += bit << counter;
  counter++;

  if(counter == sizeof(int)*8) /* on linux lab, 32 */
    counter = 0;
}

void signal_one_client()
{

  pidAssemble(0);
}

void signal_two_client()
{
  pidAssemble(1);
}



void signal_kill()
{
  my_str("\nServer exiting.\n");
  exit(0);
}

void break_loop()
{
  my_str("\nNever received string from client.\n");
  waitingForString = 0;
}



int main(int argc, char *argv[])
{
  int i;
  signal(SIGINT, signal_kill);
  signal(SIGALRM, break_loop);

  my_str("Server pID: ");
  my_int(getpid());
  my_char('\n');
  my_char('\n');

  while(1)
  {
      /* get client pID */
      clientPID = 0;
      signal(SIGUSR1, signal_one_client);
      signal(SIGUSR2, signal_two_client);
      my_str("\nWaiting for client PID...");
      for(i = 0; i < sizeof(int)*8; i++) /* wait for all bits of int */
        pause();

      my_str("Received Client PID: ");
      my_int(clientPID);
      my_str("\nReceived string from client: ");
      kill(clientPID, SIGUSR1);
      usleep(200);

      signal(SIGUSR1, signal_one);
      signal(SIGUSR2, signal_two);

      alarm(5);
      while(waitingForString)
        pause();

      alarm(0);
      waitingForString = 1;
  }
}
