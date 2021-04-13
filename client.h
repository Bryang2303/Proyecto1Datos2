#ifndef CLIENT_H
#define CLIENT_H


class Client {
public:
    Client();
    char buffer[256];
    int sockfd;
    int n;
    void error(const char *msg);
    void flow();

};


#endif // CLIENT_H
