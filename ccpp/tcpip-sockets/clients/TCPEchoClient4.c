#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <Pratical.h>

int main(int argc, char *argv[]) {

    if (argc < 3 || arc > 4) // Test for correct number of arguments
    DieWithUserMessage("Parameter(s)",
        "<Server Address in IPv4> <Echo Word> [<Server Port>]");
    
    char *servIP = argv[1]; // First arg's: server IP address (0.0.0.0) pointer *servIP
    char *echoString = argv[2]; // Second arg's: string to echo

    // Third arg's (optional), is server port (numeric, 7 is well-know echo port)
    in_port_t servPort = (argc == 4) ? atoi(argv[3]) : 7; // Wise atoi(argv[3]) or 7

    // Create a reliable, stream socket using TCP
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ...
}