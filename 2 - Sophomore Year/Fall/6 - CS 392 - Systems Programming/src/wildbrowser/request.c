#include "wild.h"

char *pageNotFound()
{
	return "<html><title>PAGE NOT FOUND</title><body> <p> </p> <p>WildBrowser is afraid to inform you that it was unable to reach the site you gave. Press Enter to go type an address.</p> </body></html>";
}

char *openingPage()
{
	return "<html> <title>Welcome to WildBrowser!</title><body> <p> </p> <p>Welcome to WildBrowser, a rudimentary text-based web browser! Press Enter to go type an address.</p> </body> </html>";
}




char *getHostName(char *request)
{
	int i = 0;

	char *hostName = (char *)malloc(sizeof(char) * strlen(request));

	if(my_modified_strcmp(request, "http://"))
		request = &request[7];

	while(request[i] != '/' && request[i] != '\0') /* if you reach the query or the end */
	{
		hostName[i] = request[i];
		i++;
	}

	return hostName;
}

char *getQuery(char *request)
{
	int i = 0;
	if(my_modified_strcmp(request, "http://"))
		request = &request[7];

	while(request[i] != '/' && request[i] != '\0') /* if you reach the query or the end */
		i++;

	if(request[i] == '\0')
		return "/";
	else
		return &request[i];
}

char *webRequest(char *request)
{
    int sockfd, portno, n, bytesRead, running, pageMalloc, i;
    struct sockaddr_in serv_addr;
    struct hostent *receivedServer;
    struct hostent server;
    char *readingPage;
    char *readPage;
    char *tempPage;
    char *httpCall;

    portno = 80;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");


    receivedServer = gethostbyname(getHostName(request));

    if(receivedServer == (void *)0) /* received server is null */
    	return pageNotFound(); 
    else
    	server = *receivedServer;

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server.h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server.h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    httpCall = (char *)malloc(sizeof(char) * 1024);
    strcpy(httpCall, "GET ");
    strcat(httpCall, getQuery(request));
    strcat(httpCall, " HTTP/1.1\r\nHost: ");
    strcat(httpCall, getHostName(request));
    strcat(httpCall, "\r\n\r\n");
    my_str(httpCall);

    if (write(sockfd, httpCall, 1024) < 0) /* request page */
        error("write() error!\n");

	pageMalloc = 65536; /* get entire page, then parse */
    readingPage = (char *)malloc(sizeof(char) * pageMalloc);
    readPage = (char *)malloc(sizeof(char) * pageMalloc);
    while(read(sockfd, readingPage, 65536) > 0)
	{
		tempPage = (char *)malloc(sizeof(char) * pageMalloc); /* tempPage holds existing readPage */
		strcpy(tempPage, readPage);

		pageMalloc += 65536;
		readPage = (char *)malloc(sizeof(char) * pageMalloc);
		strcpy(readPage, tempPage);
		strcat(readPage, readingPage);

		bzero(readingPage, 65536);
		bzero(tempPage, pageMalloc - 65536);
	}

	for (i = 0; i < strlen(readPage); i++)
	{
		if (readPage[i] == '<')
			break;
	}

	return &readPage[i];
}