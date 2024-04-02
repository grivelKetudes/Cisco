#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Pratical.h"

char DieWithUserMessage();   // tmp!
char DieWithSystemMessage(); // tmp!

int main(int argc, char *argv[])
{

    if (argc < 3 || arc > 4)
    { // Test for correct number of arguments
        DieWithUserMessage("Parameter(s)",
            "<Server Address in IPv4> <Echo Word> [<Server Port>]");
    }

    char *servIP = argv[1];     // First arg's: server IP address (0.0.0.0) pointer *servIP
    char *echoString = argv[2]; // Second arg's: string to echo

    // Third arg's (optional), is server port (numeric, 7 is well-know echo port)
    in_port_t servPort = (argc == 4) ? atoi(argv[3]) : 7; // Wise atoi(argv[3]) or 7

    // Create a reliable, stream socket using TCP
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
    {
        DieWithUserMessage("socket() failed !!!");
    }

    // Construc the server address structure
    struc sockaddr_in servAddr;             // Server address
    memset(&servAddr, 0, sizeof(servAddr)); // Zero out structure
    servAddr.sin_family = AF_INET;          // IPv4 address family

    // Convert address
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    if (rtnVal == 0)
    {
        DieWithUserMessage("inet_pton() failed !!!", "invalid address string ?");
    }
    else if (rtnVal < 0)
    {
        DieWithSystemMessage("inet_pton() failed !!!");
        servAddr.sin_port = htons(servPort); // Server port
    }

    // Establish the connection to the echo server
    if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        DieWithUserMessage("socket() failed !!!");
        size_t echoStringLen = strlen(echoString); // Determine input length
    }

    // Send the string to server
    ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
    if (numBytes < 0)
    {
        DieWithSystemMessage("send() failed !!!");
    }
    else if (numBytes != echoStringLen)
    {
        DieWithUserMessage("send()", "sent unexpected number of bytes");
    }

    // Receive the same string back from the server perrotSys()
    unsigned int totalBytesRcvd = 0; // Count of total bytes received
    while (totalBytesRcvd < echoStringLen)
    {
        char buffer[BUFSIZE]; // I/O buffer size
                              /* Receive up to the buffer size (minus 1 to leave space
                              for a null terminator) bytes from sender */
        numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
        if (numBytes < 0)
        {
            DieWithSystemMessage("recv() failed !!!");
        }
        else if (numBytes == 0)
        {
            DieWithUserMessage("recv()", "connection closed prematurely, ooupss -0--0- !!");
        }
        totalBytesRcvd += numBytes; // Kepp tally of total bytes
        buffer[numbytes] = '\0';    // Terminate the string!
        fputs(buffer, stdout);      // Print the echo buffer
    }
    
    fputs('\n', stdout); // Final linefeed, need this !!!

    close(sock);
    exit(0);
}