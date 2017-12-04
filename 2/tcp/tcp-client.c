#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int sock;
    struct sockaddr_in addr;
    char message[] = "TCP MESSAGE\n";
    char buf[sizeof(message)];
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        perror("Socket creation error");
        return 1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); 
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("Connection error");
        return 2;
    }
    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message), 0);

    for(int i = 0; i < sizeof(message); i++) {
        printf("%c", buf[i]);
    }

    close(sock);
    return 0;
}