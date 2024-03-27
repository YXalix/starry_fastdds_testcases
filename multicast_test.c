#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MCAST_GRP "239.255.0.1"
#define MCAST_PORT 50000

void send_multicast_message() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        fprintf(stderr, "Opening datagram socket error\n");
        exit(1);
    }

    // ttl = 1
    int ttl = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
        fprintf(stderr, "Setting TTL error\n");
        exit(1);
    }

    struct sockaddr_in addr;
    memset((char *)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(MCAST_GRP);
    addr.sin_port = htons(MCAST_PORT);

    char* msg = "Hello, World!";
    if (sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "Sending datagram message error\n");
        exit(1);
    }
    printf("Sent message: %s\n", msg);

    close(sock);
}

void receive_multicast_message() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        fprintf(stderr, "Opening datagram socket error\n");
        exit(1);
    }

    struct sockaddr_in addr;
    memset((char *)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(MCAST_PORT);

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "Binding datagram socket error\n");
        exit(1);
    }

        // IP_MULTICAST_LOOP = 1
    int loop = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0) {
        fprintf(stderr, "Setting loopback error\n");
        exit(1);
    }

    // IP_MULTICAST_IF
    struct in_addr localInterface;
    localInterface.s_addr = inet_addr("127.0.0.1");
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &localInterface, sizeof(localInterface)) < 0) {
        fprintf(stderr, "Setting local interface error\n");
        exit(1);
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(MCAST_GRP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        fprintf(stderr, "Adding multicast group error\n");
        exit(1);
    }

    char buf[1024];
    int n = recvfrom(sock, buf, sizeof(buf), 0, NULL, 0);
    if (n < 0) {
        fprintf(stderr, "Receiving datagram message error\n");
        exit(1);
    }
    buf[n] = '\0';
    printf("Received message: %s\n", buf);

    close(sock);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    if (pid > 0) { // parent process
        receive_multicast_message();
    } else { // child process
        send_multicast_message();
    }

    return 0;
}
