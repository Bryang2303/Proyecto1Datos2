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
    //char origen = "abc";
    //cout << origen+=origen2 << endl;
    float ff = 2.5;
    double aw = 2.3525;
    int s = 2;
    long q = 300000;
    double h = 5;
    QString sw = QString::number(h+aw);
    string sw2 = sw.toUtf8().constData();
    qDebug() << sw << endl;

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
