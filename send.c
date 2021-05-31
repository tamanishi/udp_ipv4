#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
// #include <arpa/inet.h>

int main(void) {
    int sock;
    struct sockaddr_in addr;
    char* msg = "HELLO\n";
    int n;

    // create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(54321);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    // send
    n = sendto(sock, msg, strlen(msg), 0, (struct sockaddr *)&addr, sizeof(addr));
    if(n < 1) {
        perror("sendto");
        return 1;
    }

    close(sock);

    return 0;
}