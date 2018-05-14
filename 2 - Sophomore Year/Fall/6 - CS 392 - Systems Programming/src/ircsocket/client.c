#include "my.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/time.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void my_bzero(char *toZero, int count)
{
    while(count > 0)
    {
        count--;
        *toZero++ = 0;
    }
}

void my_bcopy(char *src, char *dest, int len)
{
    char *lasts, *lastd;
    if(dest < src)
        while ((len--) > 0)
            *dest++ = *src++;
    else
    {
        lasts = src + (len - 1);
        lastd = dest + (len - 1);
        while((len--) > 0)
            *(char *)lastd-- = *(char *)lasts--;
    }
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

int main(int argc, char *argv[])
{
    int sockfd, portno, n, bytesRead, running;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    fd_set master, readfd;

    char *buffer, *nickname;

    buffer = (char *)malloc(sizeof(char) * 256);
    running = 1;
    if (argc < 3) 
    {
       my_str("Usage: /client host port\n");
       exit(1);
    }

    portno = my_atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) 
    {
        my_str("No host with that name found!\n");
        exit(1);
    }

    my_bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    my_bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(portno);

    my_bzero(buffer, 256);
    my_str("Please enter your nickname: ");
    bytesRead = read(0, buffer, 255);
    buffer = inputClean(buffer);
    my_str("\n> ");

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    if (write(sockfd, buffer, my_strlen(buffer)) < 0) /* write username */
        error("write() error!\n");

    FD_ZERO(&master);
    FD_ZERO(&readfd);

    FD_SET(sockfd, &master);
    FD_SET(0, &master);
    
    while(running == 1)
    {
        readfd = master;
        if(select(sockfd + 1, &readfd, NULL, NULL, NULL) < 0)
            error("Select() failed\n");

        if(FD_ISSET(0, &readfd)) /* reading from console */
        {
            my_bzero(buffer, 256);
            my_str("> ");
            bytesRead = read(0, buffer, 255);

            if (bytesRead < 0)
                error("read() error!\n");
            buffer = inputClean(buffer);
            buffer[bytesRead] = '\0';

            if (my_strcmp(buffer, "/exit") == 0)
            {
                my_str("Disconnecting from server.\n");
                close(sockfd);
                exit(0);
            }
            else if (write(sockfd, buffer, my_strlen(buffer)) < 0)
                error("write() error!\n");
        }
        else if(FD_ISSET(sockfd, &readfd)) /* reading from server */
        {
            my_bzero(buffer, 256);
            bytesRead = read(sockfd, buffer, 255);

            if (bytesRead < 0)
                error("read() from server error!\n");
            else if (bytesRead == 0)
            {
                my_str("Connection to server interrupted!\n");
                close(sockfd);
                exit(0);
            }
            else
            {
                my_char('\n');
                buffer[bytesRead] = '\0';
                my_str(buffer);
                my_char('\n');
                my_str("> ");
            }
        }
    }
    return 0;
}
