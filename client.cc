#include <fstream>
#include <iostream>

#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAX 1024

int main(int argc, char *argv[])
{
    char buf[MAX];
    bzero(buf, MAX);
    int f = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in svraddr;
    bzero(&svraddr, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(1234);
    svraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(f, (struct sockaddr*)&svraddr, sizeof(svraddr));

    // send file name
    const char *filename = argv[1];
    send(f, filename, strlen(filename) + 1, 0);

    // recieve file
    int n = recv(f, buf, MAX, 0);
    const char *recieve_n = basename((char *)filename);
    std::ofstream ostrm(recieve_n, std::ios::binary);
    ostrm.write(buf, n);
    ostrm.close();
 
    close(f);
    return 0;
}
