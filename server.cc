#include <iostream>
#include <fstream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define MAX 1024

int main(int argc, char *argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in svraddr;
    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(1234);
    svraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(fd, (struct sockaddr*)&svraddr, sizeof(svraddr));
    listen(fd, 20);

    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int cli = accept(fd, (struct sockaddr*)&svraddr, &len);

    // get file path
    char filename[MAX];
    bzero(filename, MAX);
    recv(cli, filename, MAX, 0);
    char rootpath[MAX];
    rootpath[0] = '\0';
    strcat(strcat(rootpath, argv[1]), filename);

    // send file
    char buf[MAX];
    bzero(buf, MAX);
    std::ifstream istrm(rootpath, std::ios::binary);
    istrm.read(buf, MAX);
    int l = istrm.gcount();
    send(cli, buf, l, 0);

    istrm.close();
    close(cli);
    close(fd);
    return 0;
}
