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
    char buf[1024];
    int bytes_read = 0;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
    {
        perror("socket creating error");
        close(sock);
        return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3426);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("binding error");
        close(sock);
        return 2;
    }

    do
    {
        bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);
        sendto(sock, buf, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
    }
    while (bytes_read == 0);
    
    close(sock);

    for(int i = 0; i < bytes_read; i++) {
        printf("%c", buf[i]);
    }

    return 0;
}