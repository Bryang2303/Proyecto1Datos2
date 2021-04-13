//
// Created by bryang2303 on 8/4/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "client.h"
#include "client.h"
#include "iostream"
using namespace std;
void Client::error(const char *msg)
{
    perror(msg);
    exit(0);
}
void Client::flow() {
    while(1)
    {

        bzero(this->buffer,256);
        fgets(this->buffer,255,stdin);
        this->n = write(this->sockfd,"holi",strlen(this->buffer));
        if (this->n < 0)
            error("ERROR writing to socket");
        bzero(this->buffer,256);
        this->n = read(this->sockfd,this->buffer,255);
        if (this->n < 0)
            error("ERROR reading from socket");
        printf("Server : %s\n",this->buffer);
        int i = strncmp("Bye" , this->buffer , 3);
        if(i == 0)
            break;
    }
}
Client::Client() {
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;


    portno = 8080;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("127.0.0.1");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(this->sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    printf("Client: ");
    flow();
    close(this->sockfd);

}

