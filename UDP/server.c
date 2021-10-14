#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>
#include <netinet/in.h>
#include <netdb.h> 

#define SIZE 1024

void write_file(int sockfd, struct sockaddr_in addr){
    char* filename = "server.txt";
    int n;
    char buffer[SIZE];
    socklen_t addr_size;
    FILE* fp = fp = fopen(filename, "w");
    while (1)
    {
        addr_size = sizeof(addr);
        n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, &addr_size);

        if (strcmp(buffer, "END") == 0){
            break;
        }
        printf("[RECEVING] Data: %s", buffer);
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    fclose(fp);
}

int main(int argc,char *argv[]){
    struct hostent *server;
    server = gethostbyname(argv[1]);
    const int port = atoi(argv[2]);
    int server_sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[SIZE];
    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sockfd < 0){
        perror("[ERROR] socket error");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr,server->h_length);
    if (bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("[ERROR] bind error");
        exit(1);
    }
    write_file(server_sockfd, client_addr);
    close(server_sockfd);
    return 0;
}
