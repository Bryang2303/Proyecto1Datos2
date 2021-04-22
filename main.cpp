#include "widget.h"
#include <QApplication>
#include "client.h"
#include "iostream"
#include "mserver.h"
using namespace std;

mserver *server;

void * serverRun(void *)
{
    try{
        server->run();
    }catch(string ex)
    {
        cout << ex;
    }

   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    char origen [] = "abcdefghi";
    cout << origen << endl;

    int mode = 2;
    if (mode==2){
        QApplication a(argc, argv);
        Widget w;
        w.show();


        cout << "SIUU" << endl;

        a.exec();
        //Client *s = new Client();
        return 0;
    } else {
        server = new mserver;
        pthread_t hiloServer;
        pthread_create(&hiloServer,0,serverRun,NULL);
        pthread_detach(hiloServer);

        while (1) {
            string mensaje;
            cin >> mensaje;
            server->setMensaje(mensaje.c_str());
        }

        delete server;
        return 0;
    }

}
