#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "Practical.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>

static const int MAXPENDING = 5;

void HandleTCPClient(int clntSocket)
{
    char buffer[BUFSIZE];

    ssize_t numBytesRcvd = read(clntSocket, buffer, BUFSIZE);

    if (numBytesRcvd < 0)
    {
        DieWithSystemMessage("recv() failed");
    }

    ssize_t numBytesSent = send(clntSocket, "HTTP/1.1 200 OK \r\n\r\nHello, World!\r\n", numBytesRcvd, 0);

    if (numBytesSent < 0)
    {
        DieWithSystemMessage("send() failed");
    }
    else if (numBytesSent != numBytesRcvd)
    {
        DieWithUserMessage("send()", "sent unexpected number of bytes\n");
    }

    close(clntSocket);
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        DieWithUserMessage("Parameter(s)", "<Server Port>");
    }

    in_port_t servPort = atoi(argv[1]);

    int servSock;

    if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        DieWithSystemMessage("socket() failed");
    }

    struct sockaddr_in servAddr;

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(servPort);

    if (bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        DieWithSystemMessage("bind() failed");
    }

    if (listen(servSock, MAXPENDING) < 0)
    {
        DieWithSystemMessage("listen() failed");
    }

    struct sockaddr_in clntAddr;
    socklen_t clntAddrLen = sizeof(clntAddr);

    int clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntAddrLen);

    if (clntSock < 0)
    {
        DieWithSystemMessage("accept() failed");
    }

    char clntName[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
    {
        printf("Handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
    }
    else
    {
        puts("Unable to get client address");
    }

    HandleTCPClient(clntSock);

    return 0;
}