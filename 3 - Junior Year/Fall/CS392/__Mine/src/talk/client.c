#include "my.h"
#include <signal.h>

int acknowledgementReceived = 0;

void alarmHandler()
{
  my_str("Connection failed. Exiting.\n");
  exit(1);
}

void acknowledge()
{
  usleep(2000);
  acknowledgementReceived = 1;
}

int main(int argc, char *argv[])
{
  int divisor = 32768, i = 0, j = 0;
  pid_t serverPID = 0;
  pid_t myPID = 0;
  char x = 0;
  char *sendingString;

  signal(SIGALRM, alarmHandler);
  signal(SIGUSR1, acknowledge);

  if(argc < 3)
  {
    my_str("Usage: ./client serverPID stringtoprint\n");
    exit(1);
  }

  serverPID = my_atoi(argv[1]);
  sendingString = my_vect2str(&argv[2]);

  my_str("Sending my pID: ");
  my_int(getpid());
  my_str("\n");

  myPID = getpid();

  for(j = 0; j < sizeof(int)*8; j++) /* on linux lab, 32 */
  {
    if((myPID & 1) == 0)
      kill(serverPID, SIGUSR1);
    else
      kill(serverPID, SIGUSR2);

    myPID >>= 1;
    usleep(100);
  }

  alarm(5);
  pause();

  if(acknowledgementReceived == 1)
  {
    alarm(0);

    my_str("Sending string: ");
    my_str(sendingString);
    my_str("\n\n");

    while(sendingString[i] != '\0')
    {

      x = sendingString[i];
      for(j = 0; j < sizeof(char)*8; j++) /* on linux lab, 8 */
      {
        if((x & 1) == 0)
          kill(serverPID, SIGUSR1);
        else
          kill(serverPID, SIGUSR2);

        x >>= 1;
        usleep(100);
      }

      j = 0;
      i++;
    }

    for(j = 0; j < sizeof(char)*8; j++)
    {
      kill(serverPID, SIGUSR1);
      usleep(100);
    }

    return 0;
  }
  else
    my_str("You got a signal that wasn\'t SIGUSR1...?\n");

  return 1;
}
