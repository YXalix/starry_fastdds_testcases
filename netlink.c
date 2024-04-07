#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/types.h>
#include <arpa/inet.h>

#define MAX_PAYLOAD 4096

void parse_rtattr(struct rtattr *tb[], int max, struct rtattr *rta, int len) {
    for (; RTA_OK(rta, len); rta = RTA_NEXT(rta, len)) {
        if (rta->rta_type <= max)
            tb[rta->rta_type] = rta;
    }
}

void print_netlink_info(unsigned char *buffer, ssize_t recv_len) {
    struct ifinfomsg *ifinfo;
    struct ifaddrmsg *ifaddr;
    struct rtattr *tb[IFLA_MAX + 1] = { NULL };
    int len;

    for (struct nlmsghdr *nlh = (struct nlmsghdr *)buffer; NLMSG_OK(nlh, recv_len); nlh = NLMSG_NEXT(nlh, recv_len)) {
        if (nlh->nlmsg_type == NLMSG_DONE) {
            break;
        } else if (nlh->nlmsg_type == RTM_NEWLINK) {
            ifinfo = (struct ifinfomsg *) NLMSG_DATA(nlh);
            len = nlh->nlmsg_len - NLMSG_SPACE(sizeof(*ifinfo));

            parse_rtattr(tb, IFLA_MAX, IFLA_RTA(ifinfo), len);

            printf("RTM_NEWLINK(%d) message:\n", nlh->nlmsg_type);
            if (tb[IFLA_IFNAME])
                printf("\tInterface: %s\n", (char *) RTA_DATA(tb[IFLA_IFNAME]));
            if (tb[IFLA_MTU])
                printf("\tMTU: %d\n", *(int *) RTA_DATA(tb[IFLA_MTU]));
            if (tb[IFLA_ADDRESS]) {
                unsigned char *mac = RTA_DATA(tb[IFLA_ADDRESS]);
                printf("\tMAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                        mac[0],
                        mac[1],
                        mac[2],
                        mac[3],
                        mac[4],
                        mac[5]);
            }
        } else if (nlh->nlmsg_type == RTM_NEWADDR) {
            printf("RTM_NEWADDR(%d) message:\n", nlh->nlmsg_type);
            ifaddr = (struct ifaddrmsg *) NLMSG_DATA(nlh);
            len = nlh->nlmsg_len - NLMSG_SPACE(sizeof(*ifaddr));

            parse_rtattr(tb, IFA_MAX, IFA_RTA(ifaddr), len);

            if (tb[IFA_LOCAL])
                printf("\tLocal Address: %s\n", inet_ntoa(*(struct in_addr *) RTA_DATA(tb[IFA_LOCAL])));
            if (tb[IFA_ADDRESS])
                printf("\tAddress: %s\n", inet_ntoa(*(struct in_addr *) RTA_DATA(tb[IFA_ADDRESS])));
            if (tb[IFA_LABEL])
                printf("\tInterface: %s\n", (char *) RTA_DATA(tb[IFA_LABEL]));
        } else {
            printf("other type(%d) message: \n", nlh->nlmsg_type);
        }

    }
}

int main() {
    int sock_fd;
    struct sockaddr_nl src_addr, dest_addr;
    struct nlmsghdr *nlh;
    char buffer[MAX_PAYLOAD];

    // 创建一个套接字
    sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();
    src_addr.nl_groups = 0;

    if (bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr)) < 0) {
        perror("bind");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // 初始化目标地址
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;  // 对内核发送消息

    // 初始化消息头
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    nlh->nlmsg_len = 20;
    nlh->nlmsg_type = RTM_GETLINK;
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    nlh->nlmsg_seq = 1;

    // 发送消息
    if (sendto(sock_fd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("sendto");
        close(sock_fd);
        free(nlh);
        exit(EXIT_FAILURE);
    }

    // 接收消息，直到接收到长度为20的消息作为结束标志
    printf("Received GETLINK packets in u8 format:\n");
    int len = 0;
    while (1) {
        ssize_t recv_len = recvfrom(sock_fd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (recv_len < 0) {
            perror("recvfrom");
            close(sock_fd);
            free(nlh);
            exit(EXIT_FAILURE);
        }

        // 打印接收到的包
        len += recv_len;
        for (ssize_t i = 0; i < recv_len; ++i) {
            printf("%02x ", (unsigned char)buffer[i]);
            if ((i + 1) % 16 == 0)
                printf("\n");
        }
        printf("\n");
        print_netlink_info(buffer, recv_len);
        printf("\n\n");

        // 检查是否接收到长度为20的消息
        if (recv_len == 20)
            break;
    }

    printf("\nReceived GETADDR len %d\n", len);


    nlh->nlmsg_type = RTM_GETADDR;
    // 发送消息
    if (sendto(sock_fd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("sendto");
        close(sock_fd);
        free(nlh);
        exit(EXIT_FAILURE);
    }


    // 接收消息，直到接收到长度为20的消息作为结束标志
    printf("Received GETADDR packets in u8 format:\n");
    len = 0;
    while (1) {
        ssize_t recv_len = recvfrom(sock_fd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (recv_len < 0) {
            perror("recvfrom");
            close(sock_fd);
            free(nlh);
            exit(EXIT_FAILURE);
        }

        // 打印接收到的包
        len += recv_len;
        for (ssize_t i = 0; i < recv_len; ++i) {
            printf("%02x ", (unsigned char)buffer[i]);
            if ((i + 1) % 16 == 0)
                printf("\n");
        }
        printf("\n");
        print_netlink_info(buffer, recv_len);
        printf("\n\n");

        // 检查是否接收到长度为20的消息
        if (recv_len == 20)
            break;
    }

    printf("\nReceived GETADDR len %d\n", len);


    // 释放资源
    close(sock_fd);
    free(nlh);

    return 0;
}
