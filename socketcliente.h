#ifndef SOCKETCLIENTE_H
#define SOCKETCLIENTE_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <QObject>
#include <arpa/inet.h>

using namespace std;

class SocketCliente: public QObject
{
    Q_OBJECT
public:
    SocketCliente();
    bool connectar();
    void setMensaje(const char *msn);
private:
    int descriptor;
    sockaddr_in info;
    static void * controlador(void *obj);
signals:
    void NewMensaje(QString msn);
};

#endif // SOCKETCLIENTE_H
