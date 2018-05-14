/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

#include "my.h"
#include "mylist.h"
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/time.h>

struct user
{
	int fd;
	char *nick;
};

void my_bzero(char *toZero, int count)
{
    while(count > 0)
    {
        count--;
        *toZero++ = 0;
    }
}

void* my_memset(void *s, char c, int len) 
{
    char *dst = s;
    while (len > 0) {
        *dst = c;
        dst++;
        len--;
    }
    return s;
}

char *getUserNick(struct s_node *head, int userfd)
{
	struct user *currentUser = NULL;
	while (head != NULL)
	{
		currentUser = (struct user *)head->elem;
		if (currentUser->fd == userfd)
			return currentUser->nick;
		else
			head = head->next;
	}
	return "Anonymous";
}

void changeUserNick(struct s_node **head, int userfd, char *newNick)
{
	struct user *currentUser = NULL;
	while (*head != NULL)
	{
		currentUser = (struct user *)(*head)->elem;
		if (currentUser->fd == userfd)
			currentUser->nick = my_strconcat(newNick, "");
		else
			*head = (*head)->next;
	}
}

void removeUser(struct s_node **head, int userfd)
{
	struct user *currentUser = NULL;
	struct s_node *currentNode = *head;
	int i = 0;
	while (currentNode != NULL)
	{
		currentUser = (struct user *)currentNode->elem;
		if (currentUser->fd == userfd)
		{
			remove_node_at(head, i);
			currentNode = NULL;
		}
		else
		{
			i++;
			currentNode = currentNode->next;
		}
	}

}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int listener, newsockfd, portno, i, j, bytesRead;
    fd_set master, readfd;
    struct s_node *userList = NULL;
    struct user *newUser = NULL;

    socklen_t clilen;

    char buffer[256];
    char *messageSending;

    struct sockaddr_in serv_addr, cli_addr;
    int n, maxFileDescriptors = 0;

    char **parsedInput;

    if (argc < 2) 
    {
        my_str("Usage: /server [port]\n");
        exit(1);
    }

    listener = socket(AF_INET, SOCK_STREAM, 0);

    if (listener < 0) 
    {
       my_str("ERROR opening socket");
       exit(1);
    }

    my_bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = my_atoi(argv[1]);

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    my_memset(&(serv_addr.sin_zero), '\0', 8);

    if (bind(listener, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    {
        my_str("Binding failed.\n");
        exit(1);
    }

    listen(listener,5);

    FD_ZERO(&master);
    FD_ZERO(&readfd);

    FD_SET(listener, &master);
    maxFileDescriptors = listener;
    my_str("Server is now online!\n\n");
    while(1)
    {
        readfd = master;

        if (select(maxFileDescriptors + 1, &readfd, NULL, NULL, NULL) < 0)
            error("select() failed!\n");

        for(i = 3; i <= maxFileDescriptors; i++)
        {
            if(FD_ISSET(i, &readfd))
            {
                if(i == listener) /* we got a new connection */
                {
                	my_str("Got a new connection!\n");
                    clilen = sizeof(cli_addr);
                    newsockfd = accept(listener, 
                                (struct sockaddr *) &cli_addr, 
                                &clilen);

                    if (newsockfd < 0) 
                        error("ERROR on accept");

                    /* read in username */
                    my_bzero(buffer, 256);
                    bytesRead = read(newsockfd, buffer, 255);
                    if (bytesRead > 0) /* was valid username */
                    {
                    	newUser = (struct user *)malloc(sizeof(struct user));
                    	newUser->fd = newsockfd;
                    	newUser->nick = my_strconcat(buffer, ""); /* hacky lmao */
                    	add_node(new_node(newUser, NULL, NULL), &userList);
                    	my_str("New user entry: ");
                    	my_str(buffer);
                    	my_char('\n');
                        messageSending = my_strconcat(buffer, " has connected.");
                        for(j = 3; j <= maxFileDescriptors; j++)
                        {
                            if(FD_ISSET(j, &master))
                            {
                                if(j != listener && j != i)
                                {
                                    if (write(j, messageSending, my_strlen(messageSending)) < 0)
                                        error("write() error!\n");
                                }
                            }
                        }
                    }
                    else
                    	my_str("no nickname received...\n");

                    FD_SET(newsockfd, &master);
                    if (newsockfd > maxFileDescriptors)
                        maxFileDescriptors = newsockfd;
                }
                else /* we got text */
                {
                    bytesRead = read(i, buffer, 255);
                    messageSending = "";
                    if (bytesRead > 1) /* got a message, not just a newline */
                    {
                    	buffer[bytesRead] = '\0';
                    	if (buffer[0] == '/') /* special command */
                    	{
                    		parsedInput = my_str2vect(buffer);

                    		if (my_strcmp(parsedInput[0], "/nick") == 0)
                    		{
                    			if (parsedInput[1] != NULL)
                    			{
                    				messageSending = my_strconcat(getUserNick(userList, i), " changed their nick to ");
                    				removeUser(&userList, i);
                    				newUser = (struct user *)malloc(sizeof(struct user));
                    				newUser->fd = i;
                    				newUser->nick = parsedInput[1];
                    				add_node(new_node(newUser, NULL, NULL), &userList);
                    				messageSending = my_strconcat(messageSending, getUserNick(userList, i));
                    			}
                    		}
                    		else if (my_strcmp(parsedInput[0], "/me") == 0)
                    		{
                    			messageSending = my_strconcat(getUserNick(userList, i), " ");
                  				messageSending = my_strconcat(messageSending, my_vect2str(&parsedInput[1]));
                    		}else if (my_strcmp(parsedInput[0], "/exit") == 0)
                            {
                                messageSending = "";
                            }else /* invalid command */
                            {
                                if (write(i, "Invalid command.", my_strlen("Invalid command.")) < 0)
                                    error("wrote() error!\n");
                            }
                    	}
                    	else /* normal message */
                    	{
	                        messageSending = my_strconcat(getUserNick(userList, i), ": ");
	                        messageSending = my_strconcat(messageSending, buffer);

                    	}

                    	if (my_strcmp(messageSending, "") != 0) /* if wrote message to send, send it */
                    	{
	                        my_str(messageSending);
	                        my_char('\n');
                    		for(j = 3; j <= maxFileDescriptors; j++)
	                        {
	                            if(FD_ISSET(j, &master))
	                            {
	                                if(j != listener && j != i)
	                                {
	                                    if (write(j, messageSending, my_strlen(messageSending)) < 0)
	                                        error("write() error!\n");
	                                }
	                            }
	                        }
	                    }
                    }
                    else if (bytesRead == 0) /* we closed the file descriptor on client */
                    {
                        messageSending = my_strconcat("SERVER: ", getUserNick(userList, i));
                        messageSending = my_strconcat(messageSending, " disconnected.\n");
                        my_str(messageSending);
                        removeUser(&userList, i);

                        for(j = 3; j <= maxFileDescriptors; j++)
                        {
                            if(FD_ISSET(j, &master))
                            {
                                if(j != listener && j != i)
                                {
                                    /* change to "SERVER: /nick disconnected" */
                                    if (write(j, messageSending, my_strlen(messageSending)) < 0)
                                        error("write() error!\n");
                                }
                            }
                        }

                        close(i);
                        FD_CLR(i, &master);
                        continue;
                    }
                    else if (bytesRead < 0)
                        error("Read error...\n");
                }
            }




        }
    }
    return 0; 
}
