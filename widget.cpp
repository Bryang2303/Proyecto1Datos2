#include "widget.h"
#include "ui_widget.h"
#include "iostream"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <typeinfo>
#include <algorithm>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    //Client *s = new Client();
    //connect(ui->pushButton, &QPushButton::clicked, this, &Widget::cerrarApp);
    conexion = new SocketCliente;
    if(!conexion->connectar())
        QMessageBox::critical(this,"Error","Error al conectar con el servidor",QMessageBox::Ok);

    connect(conexion,SIGNAL(NewMensaje(QString)),SLOT(printMensaje(QString)));
    connect(ui->pushButton_8,SIGNAL(clicked()),SLOT(sendMensaje()));
}

Widget::~Widget()
{
    delete ui;
    //string s1 = "int arise = 12;";
    //string s2 = "int";
    //string s3 = ";";

    //if(strstr(s1.c_str(),s2.c_str()))
    //{
    //    if(strstr(s1.c_str(),"=")){

    //        cout << " S1 Contains an equalizer";
}

void Widget::Recon(QStringList codelines){
    int i;
    for (i=0;i<codelines.size();i++){
        string line = codelines[i].toUtf8().constData();
        //cout << line << "\n"; // Toda la linea
        vector<string> lineDivided;
        boost::split(lineDivided, line, boost::is_any_of(" "));

        string last = lineDivided[lineDivided.size()-1];
        if (lineDivided.size()<2){
            cout << "Error en linea " << i << endl;

        } else if (lineDivided[0]=="int"){
            string tipo = "int";
            string nombre = lineDivided[1];
            string espacio = "4";

            if (lineDivided.size()>3 && lineDivided[2]=="="){
                try {
                    if(atoi(lineDivided[3].c_str()))
                    {
                        string valor = lineDivided[3];
                        cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;

                    } else {
                        throw "Error en la asignacion de valor a una variable en linea ";
                    }

                } catch(const char* msg) {
                    cout << msg << i << endl;
                }
            } else {
                cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
            }

        } else if (lineDivided[0]=="double"){
            string tipo = "double";
            string nombre = lineDivided[1];
            string espacio = "8";

            if (lineDivided.size()>3 && lineDivided[2]=="="){
                try {
                    double d;
                    //string S;
                    //S = "4.53634";
                    //istringstream(S) >> d;
                    //cout << d << endl;
                    if(istringstream(lineDivided[3]) >> d)
                    {
                        string valor = lineDivided[3];
                        cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;

                    } else {
                        throw "Error en la asignacion de valor a una variable en linea ";
                    }

                } catch(const char* msg) {
                    cout << msg << i << endl;
                }
            } else {
                cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
            }

        } else if (lineDivided[0]=="float"){
            string tipo = "float";
            string nombre = lineDivided[1];
            string espacio = "4";

            if (lineDivided.size()>3 && lineDivided[2]=="=" && last[last.size()-1]=='f'){
                try {
                    float f;
                    if(istringstream(last.substr (0,last.length()-1)) >> f)
                    {
                        string valor = last.substr (0,last.length()-1);
                        cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;

                    } else {
                        throw "Error en la asignacion de valor a una variable en linea ";
                    }

                } catch(const char* msg) {
                    cout << msg << i << endl;
                }
            } else {
                cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
            }

        } else if (lineDivided[0]=="long"){
            string tipo = "long";
            string nombre = lineDivided[1];
            string espacio = "8";

            if (lineDivided.size()>3 && lineDivided[2]=="=" && last[last.size()-1]=='f'){
                try {
                    float f;
                    if(istringstream(last.substr (0,last.length()-1)) >> f)
                    {
                        string valor = last.substr (0,last.length()-1);
                        cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;

                    } else {
                        throw "Error en la asignacion de valor a una variable en linea ";
                    }

                } catch(const char* msg) {
                    cout << msg << i << endl;
                }
            } else {
                cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
            }

        }

    }
}


void Widget::on_pushButton_3_clicked()
{
    Client *clientGUI = new Client();
}



void Widget::on_pushButton_6_clicked()
{
    QString plainTextEditContents = ui->plainTextEdit->toPlainText();
    QStringList lines = plainTextEditContents.split("\n");
    //cout << lines[0].toUtf8().constData() << endl;
    Recon(lines);


}

void Widget::sendMensaje()
{
    conexion->setMensaje(ui->lineEdit_16->text().toStdString().c_str());

}

void Widget::printMensaje(QString msn)
{
    ui->plainTextEdit->setPlainText(msn);
}
