//
// Created by bryang2303 on 12/4/21.
//

#ifndef MS2_MSERVER_H
#define MS2_MSERVER_H


#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>


using namespace std;

struct dataSocket{
    int descriptor;
    sockaddr_in info;
};

class mserver
{
public:
    mserver();
    void run();
    void setMensaje(const char *msn);
private:
    int descriptor;
    sockaddr_in info;
    bool crear_Socket();
    bool ligar_kernel();
    static void * controladorCliente(void *obj);
    vector<int> clientes;
};


#endif //MS2_MSERVER_H
