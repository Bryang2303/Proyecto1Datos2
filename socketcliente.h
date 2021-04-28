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
/**
 * @brief The SocketCliente class La clase que permite la creacion del Socket Cliente, asi como su conexion con el servidor y todo el flujo de datos con este
 */
class SocketCliente: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief SocketCliente EL constructor del socket cliente
     */
    SocketCliente();
    /**
     * @brief connectar Permite activar y reconocer la conexion con  el servidor
     * @return Si la conexion fue exitosa o no
     */
    bool connectar();
    /**
     * @brief setMensaje Se establece un mensaje para ser enviado al servidor
     * @param msn El contenido del mensaje
     */
    void setMensaje(const char *msn);
private:
    int descriptor;
    /**
     * @brief info La direccion del socket de entrada
     */
    sockaddr_in info;
    /**
     * @brief controlador Permite el control de mensajes recibidos
     * @param obj Asignacion del servidor que envia el mensaje
     * @return
     */
    static void * controlador(void *obj);
signals:
    /**
     * @brief NewMensaje Creacion de un mensaje nuevo mensaje
     * @param msn El contenido del mensaje
     */
    void NewMensaje(QString msn);
};

#endif // SOCKETCLIENTE_H
