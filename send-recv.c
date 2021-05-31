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
    struct sockaddr_in senderinfo;
    socklen_t addrlen;
    char buf[2048];
    char* msg = "HELLO\n";
    char ipaddrstr[INET_ADDRSTRLEN];
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

    // receive
    memset(buf, 0, sizeof(buf));
    addrlen = sizeof(senderinfo);

    n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&senderinfo, &addrlen);

    // show sender info
    inet_ntop(AF_INET, &senderinfo.sin_addr, ipaddrstr, sizeof(ipaddrstr));
    printf("UDP packet from : %s, port=%d\n", ipaddrstr, ntohs(senderinfo.sin_port));

    // show content
    write(fileno(stdout), buf, n);

    close(sock);

    return 0;
}