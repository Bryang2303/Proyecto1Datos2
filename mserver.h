//
// Created by bryang2303 on 12/4/21.
//

#ifndef MS2_MSERVER_H
#define MS2_MSERVER_H


class mserver {
public:
    mserver();
    char buffer[256];
    int newsockfd;
    int sockfd;
    int n;
    void error(const char *msg);
    void flow();

};


#endif //MS2_MSERVER_H
