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
    int sock, n;
    struct sockaddr_in addr;
    char msg[] = "UDP MESSAGE\n";
    char buf[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
    {
        perror("socket creating error");
        close(sock);
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3426);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    socklen_t sock_len = sizeof (addr);
    sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *)&addr, sizeof(addr));
    n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&addr, &sock_len);

    for(int i = 0; i < n; i++) {
        printf("%c", buf[i]);
    }

    close(sock);

    return 0;
}