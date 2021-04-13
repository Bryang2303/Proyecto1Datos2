#include "widget.h"
#include <QApplication>
#include "client.h"
#include "iostream"
#include "mserver.h"
using namespace std;

int main(int argc, char *argv[])
{
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
        mserver *server = new mserver();
    }

}
