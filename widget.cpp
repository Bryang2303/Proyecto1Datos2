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


QString Widget::Solve(int first, int second, int action){
    if (action==1){
        QString s = QString::number(first+second);
        return s;
    } else if (action==2){
        QString s = QString::number(first-second);
        return s;
    } else if (action==3){
        QString s = QString::number(first*second);
        return s;
    } else if (action==4){
        QString s = QString::number(first/second);
        return s;
    }
}
void Widget::IsOrNot(QString n, QString t){
    for (int j = 0;j<this->variables.size();j++){
        QStringList variables2 = this->variables[j].split("|");
        if (variables2[0] == n && variables2[1] == t){
            this->alreadyIs = 1;
            break;
        }
    }
}
QString Widget::searchInScope(QString n, QString t, QString scp){
    for (int j = 0;j<this->variables.size();j++){
        QStringList variables2 = this->variables[j].split("|");
        //qDebug() << n << t << scp << endl;
        qDebug() << variables2[0] << variables2[1] << "\n";
        if (variables2[0] == n && variables2[1] == t){
            //cout << "paciente ceroooo 0" << endl;
            if (variables2[3] == scp || variables2[3] == "0"){
                //cout << "PASO 1" << endl;
                return variables2[2];
            }
        }
    }
    return "no";
}



void Widget::Recon(QStringList codelines){
    int i;
    const char CaracteresIndeseados[] = { '[', ']', ';', '.' };
    //this->variables.clear();
    //bool alreadyIs = 0;
    for (i=0;i<codelines.size();i++){
        //bool scope = false;

        string line = codelines[i].toUtf8().constData();
        //cout << line << "\n"; // Toda la linea
        vector<string> lineDivided;
        boost::split(lineDivided, line, boost::is_any_of(" "));

        string last = lineDivided[lineDivided.size()-1];

        if(lineDivided[0]=="{") {
            this->scope = true;
            this->scopes.append(this->scopes[this->scopes.size()-1]+1);
            qDebug() << this->scopes;
            this->contScope = this->scopes[this->scopes.size()-1];

        } else if(lineDivided[0]=="}") {
            this->scope = false;
            this->contScope = 0;

        } else if (lineDivided[0]=="int"){
            string tipo = "int";
            string nombre = lineDivided[1];
            ////////
            QString type = QString::fromStdString(lineDivided[0]);
            QString name = QString::fromStdString(nombre);
            QString scopeNum = QString::number(this->contScope);

            ////////
            string espacio = "4";
            if (lineDivided.size()>3 && lineDivided[2]=="="){
                try {
                    if(atoi(lineDivided[3].c_str()) && lineDivided.size()<=4)////
                    {
                        string valor = lineDivided[3];
                        ////////
                        QString value = QString::fromStdString(valor);
                        IsOrNot(name,type);

                        if (this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + value + "|" + scopeNum);
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;
                        } else {
                            alreadyIs = 1;
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                        qDebug() << this->variables << endl;
                        ////////

                    } else if (atoi(lineDivided[3].c_str()) && atoi(lineDivided[5].c_str())){
                        IsOrNot(name,type);
                        if (lineDivided[4]=="+" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),1) + "|" + scopeNum);
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),1).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),2) + "|" + scopeNum);
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),2).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),3) + "|" + scopeNum);
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),3).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),4) + "|" + scopeNum);
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),4).toUtf8().constData() << endl;

                        } else {
                            alreadyIs = 1;
                            throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                        }
                        qDebug() << this->variables << endl;
                        ////////
                    } else if (atoi(lineDivided[5].c_str())){
                        IsOrNot(name,type);
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;
                            if (searchInScope(name2,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),1) + "|" + scopeNum);
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),2) + "|" + scopeNum);
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),3) + "|" + scopeNum);
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),4) + "|" + scopeNum);
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }
                    } else if (atoi(lineDivided[3].c_str())) {
                        IsOrNot(name,type);
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[5];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;
                            if (searchInScope(name2,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),1) + "|" + scopeNum);
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),2) + "|" + scopeNum);
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),3) + "|" + scopeNum);
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),4) + "|" + scopeNum);
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else {
                        throw "Error en la asignacion de valor a una variable en linea ";
                    }

                } catch(const char* msg) {
                    cout << msg << i << endl;
                }
            } else {
                ////////
                for (int z = 0;z<this->variables.size();z++){
                    QStringList variables2 = this->variables[z].split("|");
                    if (variables2[0] == name && variables2[1] == type){
                        alreadyIs = 1;
                    }
                }
                if (alreadyIs==0){
                    this->variables.append(name + "|" + type + "|" + "0" + "|" + scopeNum);
                    cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
                } else {
                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                }
                qDebug() << this->variables << endl;
                ////////

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

            if (lineDivided.size()>3 && lineDivided[2]=="="){
                try {
                    string::size_type sz;   // alias of size_t
                    long l = stol (lineDivided[3],&sz);
                    if(stol (lineDivided[3],&sz) == l)
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

        } else if (lineDivided[0]=="char" && lineDivided[2][0] == '[' && lineDivided[2][lineDivided[2].size()-1] == ']'){
            string tipo = "char";
            string nombre = lineDivided[1];

            if (lineDivided.size()>4 && lineDivided[3]=="="){
                try {

                    if(atoi(lineDivided[2].substr (1,lineDivided[2].size()-1).c_str()))
                    {
                        string espacio = lineDivided[2].substr (0,lineDivided[2].length()-1);
                        string espacio2 = espacio.substr (1,espacio.length()-1);
                        cout << espacio2 << endl;
                        int sp;

                        if (istringstream(espacio2) >> sp){

                            if (sp>=lineDivided[4].size()){
                                string valor = espacio.substr (1,espacio.length()-1);
                                cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;
                            } else {
                                throw "Error en la asignacion de valor a una variable en linea ";
                            }

                        } else {
                            throw "Error en la asignacion de valor a una variable en linea ";
                        }

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


    qDebug() << this->variables << "\n";

    //Client *clientGUI = new Client();
    /*
    QString plainTextEditContents = ui->plainTextEdit->toPlainText();
    QStringList lines = plainTextEditContents.split("\n");
    QStringList licta;
    //cout << line << "\n"; // Toda la linea

    for (int i = 0;i<lines.size();i++){
        //qDebug() << lines[i] << "\n";
        string line = lines[i].toUtf8().constData();
        vector<string> lineDivided;
        boost::split(lineDivided, line, boost::is_any_of(" "));

        cout << lineDivided[0] << "\n";
        QString t = QString::fromStdString(lineDivided[0]);
        QString n = QString::fromStdString(lineDivided[1]);
        QString v = QString::fromStdString(lineDivided[2]);

        licta.append(t + "|" + n + "|" + v);
        qDebug() << licta[i] << "\n";
    }
    for (int j = 0;j<licta.size();j++){
        QStringList licta2 = licta[j].split("|");
        qDebug() << " t: " << licta2[0] << " n: " << licta2[1] << " v: "<< licta2[2] << "\n";

    }
    */

    //QStringList lines2 = plainTextEditContents.split("|");
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
