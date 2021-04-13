//
// Created by bryang2303 on 12/4/21.
//
#include "mserver.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "iostream"
using namespace std;

void mserver::error(const char *msg)
{
    perror(msg);
    exit(0);
}
void mserver::flow() {
    while(1)
    {
        bzero(this->buffer,256);
        this->n = read(this->newsockfd,this->buffer,255);
        if (this->n < 0) error("ERROR reading from socket");
        printf("Client: %s\n",this->buffer);
        bzero(this->buffer,256);
        fgets(this->buffer,255,stdin);
        this->n = write(this->newsockfd,this->buffer,strlen(this->buffer));
        if (this->n < 0) error("ERROR writing to socket");
        int i=strncmp("Bye" , this->buffer, 3);
        if(i == 0)
            break;
    }
}
mserver::mserver() {
    int portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 8080;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(this->sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(this->sockfd,5);
    clilen = sizeof(cli_addr);
    this->newsockfd = accept(this->sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (this->newsockfd < 0)
        error("ERROR on accept");
    flow();
    close(this->newsockfd);
    close(this->sockfd);

}
