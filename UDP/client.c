#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>
#include <netinet/in.h>
#include <netdb.h> 

#define SIZE 1024

void send_file_data(FILE* fp, int sockfd, struct sockaddr_in addr){
    int n;
    char buffer[SIZE];

    while (fgets(buffer, SIZE, fp) != NULL){
        printf("[SENDING] Data: %s", buffer);

        n = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
        if (n == -1){
            perror("[ERROR] sending data to the server.");
            exit(1);
        }
        bzero(buffer, SIZE);
    }
    strcpy(buffer, "END");
    sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
    fclose(fp);
}

int main(int argc,char *argv[]){
    struct hostent *server;
    server = gethostbyname(argv[1]);
    const int port = atoi(argv[2]);
    int server_sockfd;
    struct sockaddr_in server_addr;
    char *filename = argv[3];
    FILE *fp = fopen(filename, "r");
    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sockfd < 0){
        perror("[ERROR] socket error");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr,server->h_length);
    if (fp == NULL){
        perror("[ERROR] reading the file");
        exit(1);
    }
    send_file_data(fp, server_sockfd, server_addr);
    close(server_sockfd);
    return 0;
}
