#include "mserver.h"

mserver::mserver()
{
}


bool mserver::crear_Socket()
{
    descriptor = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(descriptor < 0)
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY;
    info.sin_port = htons(4050);
    memset(&info.sin_zero,0,sizeof(info.sin_zero));
    return true;
}

bool mserver::ligar_kernel()
{
    if((bind(descriptor,(sockaddr *)&info,(socklen_t)sizeof(info))) < 0)
        return false;

    listen(descriptor,5);
    return true;
}


void mserver::run()
{
    if(!crear_Socket())
        throw string("Error al crear el socket");
    if(!ligar_kernel())
        throw string("Error al  ligar kernel");

    while (true) {
        cout << "Esperando nuevo cliente"<<endl;
        dataSocket data;
        socklen_t tam = sizeof(data.info);
        data.descriptor = accept(descriptor,(sockaddr*)&data.info,&tam);
        if(data.descriptor < 0)
            cout << "Error al acceptar al cliente"<<endl;
        else
        {
            clientes.push_back(data.descriptor);
            pthread_t hilo;
            pthread_create(&hilo,0,mserver::controladorCliente,(void *)&data);
            pthread_detach(hilo);
        }
    }
    close(descriptor);
}



void * mserver::controladorCliente(void *obj)
{
    dataSocket *data = (dataSocket*)obj;
    while (true) {
        string mensaje;
        while (1) {
            char buffer[100] = {0};
            int bytes = recv(data->descriptor,buffer,100,0);
            mensaje.append(buffer,bytes);
            if(bytes < 100)
                break;
        }
        cout << mensaje << endl;
    }

    close(data->descriptor);
    pthread_exit(NULL);
}


void mserver::setMensaje(const char *msn)
{
    for(unsigned int i = 0 ; i < clientes.size() ; i++)
        cout << "bytes enviados "<< send(clientes[i],msn,strlen(msn),0);
}
