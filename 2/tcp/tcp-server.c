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
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read = 0;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener == -1)
    {
        perror("socket listen mode error");
        return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind error");
        return 2;
    }

    listen(listener, 1);
    
    do
    {
        sock = accept(listener, NULL, NULL);
        if(sock == -1)
        {
            perror("accept error");
            continue;
        }

        do
        {
            bytes_read = recv(sock, buf, 1024, 0);
            send(sock, buf, bytes_read, 0);
        }
        while(bytes_read == 0);
    
        
    }
    while(bytes_read == 0);

    close(sock);

    for(int i = 0; i < bytes_read; i++) {
        printf("%c", buf[i]);
    }
    
    return 0;
}