#include "widget.h"
#include "ui_widget.h"
#include "iostream"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
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
#include <json.h>


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
    //pLabel->setStyleSheet( "Qlabel { background-color : red; color : blue; }");
    //ui->label_3->setStyleSheet("Qlabel { background-color : red; color : blue;  }");
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

void Widget::RamView(){
    ui->plainTextEdit_2->clear();
    QStringList RV = malloc.getV_asignada();
    for (int r = 0; r< RV.size();r++){
        QString dato = RV[r];
        qDebug()<< dato << endl;
        ui->plainTextEdit_2->appendPlainText(dato);
    }
}
void Widget::log(QString T, QString msgL){
    date();
    string str{this->fecha};
    string fecha2 = str.substr (0,str.length()-1);
    cout << fecha2 << endl;
    QString _date = QString::fromStdString(fecha2);
    //qDebug() << _date << endl;
    ui->plainTextEdit_3->appendPlainText(_date+" "+T+": "+msgL);
}
void Widget::date(){
    this->current_time=time(NULL);
    ctime(&this->current_time);
    strcpy(this->fecha, ctime(&this->current_time));
    cout << this->fecha << endl;

}

void Widget::Counting(QString n){
    for (int k = 0; k<this->variables3.size();k++){
        QStringList variables2 = this->variables3[k].split("|");
        //qDebug() << this->codeLines2 << endl
        if (variables2[0]==n && variables2[1]!="0"){
            this->counters[k]+=1;

            cout << "Ahora k es : " << this->counters[k] << endl;
            if (variables2[1].toInt() == this->counters[k]){
                //cout << "Proceso terminado " << variables2[0].toUtf8().constData() << endl;
                ui->plainTextEdit_5->appendPlainText(variables2[0]);
                log("[WARN]","Garbage Collector ha recolectado la variable : " + variables2[0]);

            }
        }
        else if (variables2[0]==n && variables2[1]=="0"){
            ui->plainTextEdit_5->appendPlainText(variables2[0]);
            log("[WARN]","Garbage Collector ha recolectado la variable : " + variables2[0]);
        }

    }
    //cout << this->counters;
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
auto Widget::Solve2(auto first, auto second, auto action){
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
// a , b , c
void Widget::IsOrNot(QString n, QString t){
    for (int j = 0;j<this->variables.size();j++){
        QStringList variables2 = this->variables[j].split("|");
        if (variables2[0] == n){
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
        if (variables2[0] == n){
            //cout << "paciente ceroooo 0" << endl;
            if (variables2[3] == scp || variables2[3] == "0"){
                //cout << "PASO 1" << endl;
                return variables2[2];
            }
        }
    }
    return "no";
}
QString Widget::searchInScope2(QString n,QString scp){
    for (int j = 0;j<this->variables.size();j++){
        QStringList variables2 = this->variables[j].split("|");
        //qDebug() << n << t << scp << endl;
        qDebug() << variables2[0] << variables2[1] << "\n";
        if (variables2[0] == n){
            //cout << "paciente ceroooo 0" << endl;
            if (variables2[3] == scp || variables2[3] == "0"){
                //cout << "PASO 1" << endl;
                return variables2[1];
            }
        }
    }
    return "no";
}
void Widget::setValue(QString n,auto v, QString t, QString scp){
    //cout << v << " ahora si" << endl;
    for (int j = 0;j<this->variables.size();j++){
        QStringList variables2 = this->variables[j].split("|");
        //qDebug() << n << " " << v << endl;
        //qDebug() << variables2[0] << variables2[1] << "\n";
        if (variables2[0] == n){
            QString vv = QString::number(v);
            variables.removeAt(j);
            this->variables.append(n + "|" + t + "|" + vv + "|" + scp);
        }

    }
}

void Widget::sendMsg(QString n, QString Jaction){
    for (int j = 0;j<this->variables.size();j++){
        QStringList variables2 = this->variables[j].split("|");
        //qDebug() << n << " " << v << endl;
        //qDebug() << variables2[0] << variables2[1] << "\n";
        if (variables2[0] == n){
            QString CMsg = Jaction + "|" + variables2[1] + "|" + variables2[2] + "|" + n;
            qDebug() << CMsg << endl;
            conexion->setMensaje(CMsg.toUtf8().constData());
        }
    }
}


void Widget::Recon(QStringList codelines, int runKind){
    int i=0;
    int limit;
    if (runKind==0){
        limit = codelines.size();

    } else {
        limit = this->pos;
        i = limit-1;
    }


    //this->variables.clear();
    //bool alreadyIs = 0;
    for (i;i<limit;i++){
        //bool scope = false;
        if (limit>codelines.size()){
            cout << "Se paso del limite" << endl;
            log("[ERROR]","Fuera del limite de las lineas de codigo");
            break;
        }
        this->alreadyIs=0;

        string line = codelines[i].toUtf8().constData();
        //cout << line << "\n"; // Toda la linea
        vector<string> lineDivided;
        boost::split(lineDivided, line, boost::is_any_of(" "));



        cout << lineDivided[0] << endl;
        string last = lineDivided[lineDivided.size()-1];
        if(lineDivided[0]=="{") {
            this->scope = true;
            this->scopes.append(this->scopes[this->scopes.size()-1]+1);
            qDebug() << this->scopes;
            this->contScope = this->scopes[this->scopes.size()-1];
            cout << contScope << endl;
        } else if(lineDivided[0]=="}") {
            //this->scope = false;
            this->contScope = 0;
        } else if (lineDivided[0]=="struct" && lineDivided.size()>2 && lineDivided[2]=="{"){
            string tipo = "struct";
            ////////
            QString type = QString::fromStdString(lineDivided[0]);
            this->scope = true;
            this->scopes.append(this->scopes[this->scopes.size()-1]+1);
            qDebug() << this->scopes;
            this->contScope = this->scopes[this->scopes.size()-1];
            string nombre = lineDivided[1];
            QString name = QString::fromStdString(nombre);

            QString scopeNum = QString::number(this->contScope);
            IsOrNot(name,name);
            if (this->alreadyIs==0){
                this->variables.append(name + "|" + type + "|" + Solve(0,0,1) + "|" + scopeNum);
            } else{
                log("[ERROR]","Estructura ya declarada anteriormente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
            }
        } else if (lineDivided[1]==".getAddr()"){
            cout << "Direccion de memoria" << endl;

        } else if (lineDivided[0]=="reference" && lineDivided.size()>=4){
            if (lineDivided[1]=="<" && lineDivided[3]==">"){
                string tipo = "reference";
                ////////
                QString type = QString::fromStdString(lineDivided[0]);

                string tipo2 = lineDivided[2];
                ////////
                QString type2 = QString::fromStdString(tipo2);

                string nombre = lineDivided[4];
                QString name = QString::fromStdString(nombre);

                QString scopeNum = QString::number(this->contScope);
                IsOrNot(name,name);
                if (this->alreadyIs==0){
                    //this->variables.append(name + "|" + type + "<" + type2 + ">" + "|" + Solve(0,0,1) + "|" + scopeNum);
                    this->variables.append(name + "|" + type + "|" + Solve(0,0,1) + "|" + scopeNum);
                } else{
                    log("[ERROR]","Referencia ya declarada anteriormente. Error en la linea "+QString::number(i));
                }

            } else {
                log("[ERROR]","Error en la declaracion de un objeto de tipo Reference en linea "+QString::number(i));
            }
            qDebug() << this->variables << endl;

        } else if (lineDivided[0]=="cout" && lineDivided[1]=="<<" && lineDivided[3]=="<<"){
            if ( lineDivided[4]=="\n;" || lineDivided[4]=="endl;" ){
                string nombre = lineDivided[2];
                QString name = QString::fromStdString(nombre);
                QString scopeNum = QString::number(this->contScope);
                IsOrNot(name,name);
                if (this->alreadyIs==1){
                    QString a = searchInScope(name,name,scopeNum);
                    ui->plainTextEdit_4->appendPlainText(" > "+a);
                } else{
                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                }
            } else {
                log("[ERROR]","Error en la asignacion de valor a una variable en linea "+QString::number(i));
            }
        } else if (lineDivided[0]=="print" && lineDivided[1]=="(" && lineDivided[3]==")"){
            string nombre = lineDivided[2];
            QString name = QString::fromStdString(nombre);
            QString scopeNum = QString::number(this->contScope);
            IsOrNot(name,name);
            if (this->alreadyIs==1){
                QString a = searchInScope(name,name,scopeNum);
                ui->plainTextEdit_4->appendPlainText(" > "+a);
            } else{
                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
            }


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
                int in;
                try {

                    if(lineDivided.size()<=4)////
                    {
                        if (atoi(lineDivided[3].c_str())){
                            in = atoi(lineDivided[3].c_str());
                            auto s = std::to_string(in);
                            string valor = s;
                            ////////
                            QString value = QString::fromStdString(valor);
                            this->alreadyIs=0;
                            IsOrNot(name,type);

                            if (this->alreadyIs==0){
                                if (runKind==1){
                                    Counting(name);
                                }
                                this->variables.append(name + "|" + type + "|" + value + "|" + scopeNum);
                                cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;
                                log("[INFO]","Variable " +name+ " de tipo " + type + " asignada con un valor de " + value);

                                sendMsg(name,this->J.ParseJson(0));
                                J.Write("1",name,type,value);
                                J.CreateJsonFile();
                                malloc.Principal();

                                RamView();
                            } else {
                                alreadyIs = 1;
                                log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                            }

                            qDebug() << this->variables << endl;
                            ////////

                        } else {
                            //cout << "AHORA?" << endl;
                            IsOrNot(name,type);
                            if (this->alreadyIs==0){
                                string nombre2 = lineDivided[3];
                                QString name2 = QString::fromStdString(nombre2);

                                if (runKind==1){
                                    Counting(name);
                                    Counting(name2);
                                }

                                QString no = QString::fromStdString("no");
                                if (searchInScope(name2,type,scopeNum)!=no){
                                    string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();

                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),0,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");

                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),0,1).toUtf8().constData() << endl;
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),0,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                                }
                                qDebug() << this->variables << endl;

                            }
                        }


                    } else if (atoi(lineDivided[3].c_str()) && atoi(lineDivided[5].c_str())){
                        this->alreadyIs=0;
                        IsOrNot(name,type);
                        if (runKind==1 && this->alreadyIs==0){
                            Counting(name);
                        }
                        if (lineDivided[4]=="+" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),1) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),1).toUtf8().constData() << endl;
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),1));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                        } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),2) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),2).toUtf8().constData() << endl;
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),2));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                        } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),3) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),3).toUtf8().constData() << endl;
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),3));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                        } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),4) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),4).toUtf8().constData() << endl;
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve(atoi(lineDivided[3].c_str()),atoi(lineDivided[5].c_str()),4));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                        } else {
                            alreadyIs = 1;
                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                        }
                        qDebug() << this->variables << endl;
                        ////////
                    } else if (atoi(lineDivided[5].c_str())){
                        this->alreadyIs=0;
                        IsOrNot(name,type);
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;

                            if (searchInScope(name2,type,scopeNum)!=no){

                                if (runKind==1){
                                    Counting(name);
                                    Counting(name2);
                                }
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(lineDivided[5].c_str()),4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
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
                                if (runKind==1){
                                    Counting(name);
                                    Counting(name2);
                                }
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),4) + "|" + scopeNum);
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(lineDivided[3].c_str()),atoi(value2.c_str()),4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else if (1){

                        IsOrNot(name,type);
                        if (this->alreadyIs==0){

                            cout << lineDivided.size() << endl;
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            string nombre3 = lineDivided[5];
                            QString name3 = QString::fromStdString(nombre3);
                            QString no = QString::fromStdString("no");
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                                Counting(name3);
                            }
                            if (searchInScope(name2,type,scopeNum)!=no || searchInScope(name3,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                string value3 = searchInScope(name3,type,scopeNum).toUtf8().constData();
                                cout << value2 << " " << value3 << endl;
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(value3.c_str()),1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),atoi(value3.c_str()),1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(value3.c_str()),1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(value3.c_str()),2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),atoi(value3.c_str()),2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(value3.c_str()),2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(value3.c_str()),3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),atoi(value3.c_str()),3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(value3.c_str()),3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atoi(value2.c_str()),atoi(value3.c_str()),4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atoi(value2.c_str()),atoi(value3.c_str()),4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),atoi(value3.c_str()),4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else {
                        log("[ERROR]","Error en la asignacion de valor a una variable en linea. Error en la asignacion de valor a una variable en linea "+QString::number(i));
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
                if (this->alreadyIs==0){
                    if (runKind==1){
                        Counting(name);
                    }
                    this->variables.append(name + "|" + type + "|" + "0" + "|" + scopeNum);
                    log("[INFO]","Variable " +name+ " de tipo " + type + " definida sin valor");
                    cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
                    sendMsg(name,this->J.ParseJson(0));
                    J.Write("1",name,type,"0");
                    J.CreateJsonFile();
                    malloc.Principal();

                    RamView();
                } else {
                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                }
                qDebug() << this->variables << endl;
                ////////

            }

        } else if (lineDivided[0]=="double"){
            string tipo = "double";
            string nombre = lineDivided[1];
            ////////
            QString type = QString::fromStdString(lineDivided[0]);
            QString name = QString::fromStdString(nombre);
            QString scopeNum = QString::number(this->contScope);
            ///////
            string espacio = "8";

            if (lineDivided.size()>3 && lineDivided[2]=="="){
                double d;
                double d2;
                try {

                    if(lineDivided.size()<=4)////
                    {
                        cout << "CASO 1" << endl;
                        if (istringstream(lineDivided[3]) >> d){
                            string valor = lineDivided[3];
                            ////////
                            QString value = QString::fromStdString(valor);
                            IsOrNot(name,type);

                            if (this->alreadyIs==0){
                                if (runKind==1){
                                    Counting(name);
                                }
                                this->variables.append(name + "|" + type + "|" + value + "|" + scopeNum);
                                log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                sendMsg(name,this->J.ParseJson(0));
                                J.Write("1",name,type,value);
                                J.CreateJsonFile();
                                malloc.Principal();

                                RamView();
                                cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;
                            } else {
                                alreadyIs = 1;
                                log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                            }

                            qDebug() << this->variables << endl;
                            ////////

                        } else {
                            //cout << "AHORA?" << endl;
                            IsOrNot(name,type);
                            if (this->alreadyIs==0){
                                string nombre2 = lineDivided[3];
                                QString name2 = QString::fromStdString(nombre2);
                                if (runKind==1){
                                    Counting(name);
                                    Counting(name2);
                                }
                                QString no = QString::fromStdString("no");
                                if (searchInScope(name2,type,scopeNum)!=no){
                                    string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                    istringstream(value2) >> d;
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,0,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,0,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,0,1).toUtf8().constData() << endl;
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                                }
                                qDebug() << this->variables << endl;

                            }
                        }
                    } else if (istringstream(lineDivided[3]) >> d && istringstream(lineDivided[5]) >> d2){
                        cout << "CASO 2" << endl;
                        IsOrNot(name,type);
                        istringstream(lineDivided[3]) >> d;
                        istringstream(lineDivided[5]) >> d2;
                        if (runKind==1 && this->alreadyIs==0){
                            Counting(name);
                        }
                        if (lineDivided[4]=="+" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve2(d,d2,1) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,1).toUtf8().constData() << endl;
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve2(d,d2,1));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                        } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve2(d,d2,2) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,2).toUtf8().constData() << endl;
                            J.Write("1",name,type,Solve2(d,d2,2));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                        } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve2(d,d2,3) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve2(d,d2,3));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,3).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve2(d,d2,4) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve2(d,d2,4));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,4).toUtf8().constData() << endl;

                        } else {
                            alreadyIs = 1;
                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                        }
                        qDebug() << this->variables << endl;
                        ////////
                    } else if (istringstream(lineDivided[5]) >> d){
                        cout << "CASO 3" << endl;
                        IsOrNot(name,type);
                        istringstream(lineDivided[5]) >> d;
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                            }
                            if (searchInScope(name2,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                istringstream(value2) >> d2;
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d2,d,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d2,d,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d2,d,1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d2,d,2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d2,d,2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d2,d,2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d2,d,3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d2,d,3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d2,d,3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d2,d,4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d2,d,4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d2,d,4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }
                    } else if (istringstream(lineDivided[3]) >> d) {
                        cout << "CASO 4" << endl;
                        IsOrNot(name,type);
                        istringstream(lineDivided[3]) >> d;
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[5];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                            }
                            if (searchInScope(name2,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                istringstream(value2) >> d2;
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,d2,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,d2,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,d2,2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,d2,2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,d2,3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,d2,3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,d2,4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,d2,4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else if (1){
                        cout << "CASO 5" << endl;
                        IsOrNot(name,type);

                        if (this->alreadyIs==0){
                            cout << lineDivided.size() << endl;
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            string nombre3 = lineDivided[5];
                            QString name3 = QString::fromStdString(nombre3);
                            QString no = QString::fromStdString("no");
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                                Counting(name3);
                            }

                            if (searchInScope(name2,type,scopeNum)!=no || searchInScope(name3,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                string value3 = searchInScope(name3,type,scopeNum).toUtf8().constData();
                                istringstream(value2) >> d;
                                istringstream(value3) >> d2;
                                cout << value2 << " " << value3 << endl;
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,d2,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,d2,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,d2,2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,d2,2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,d2,3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,d2,3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(d,d2,4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(d,d2,4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(d,d2,4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }
                    } else {
                        log("[ERROR]","Error en la asignacion de valor a una variable en linea. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                        throw "Error en la asignacion de valor a una variable en linea ";
                    }

                } catch(const char* msg) {
                    cout << msg << i << endl;
                }
            } else {
                ////////
                IsOrNot(name,type);
                if (this->alreadyIs==0){
                    if (runKind==1){
                        Counting(name);
                    }
                    this->variables.append(name + "|" + type + "|" + "0" + "|" + scopeNum);
                    log("[INFO]","Variable " +name+ " de tipo " + type + " definida sin valor");
                    sendMsg(name,this->J.ParseJson(0));
                    J.Write("1",name,type,"0");
                    J.CreateJsonFile();
                    malloc.Principal();

                    RamView();

                    cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
                } else {
                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                }
                qDebug() << this->variables << endl;
                ////////

            }

        } else if (lineDivided[0]=="float"){
            string tipo = "float";
            string nombre = lineDivided[1];
            ////////
            QString type = QString::fromStdString(lineDivided[0]);
            QString name = QString::fromStdString(nombre);
            QString scopeNum = QString::number(this->contScope);
            ///////
            string espacio = "4";
            if (lineDivided.size()>3 && lineDivided[2]=="="){
                float f;
                float f2;
                try {

                    if(lineDivided.size()<=4)////
                    {
                        cout << "CASO 1" << endl;
                        if (istringstream(lineDivided[3].substr (0,lineDivided[3].length()-1)) >> f && lineDivided[3][lineDivided[3].size()-1]=='f'){

                            string valor = last.substr (0,last.length()-1);
                            ////////
                            QString value = QString::fromStdString(valor);
                            IsOrNot(name,type);

                            if (this->alreadyIs==0){
                                if (runKind==1){
                                    Counting(name);

                                }
                                this->variables.append(name + "|" + type + "|" + value + "|" + scopeNum);
                                log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                sendMsg(name,this->J.ParseJson(0));
                                J.Write("1",name,type,value);
                                J.CreateJsonFile();
                                malloc.Principal();

                                RamView();
                                cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;
                            } else {
                                alreadyIs = 1;
                                log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                            }

                            qDebug() << this->variables << endl;
                            ////////

                        } else {
                            //cout << "AHORA?" << endl;
                            IsOrNot(name,type);
                            if (this->alreadyIs==0){
                                string nombre2 = lineDivided[3];
                                QString name2 = QString::fromStdString(nombre2);
                                if (runKind==1){
                                    Counting(name);
                                    Counting(name2);
                                }
                                QString no = QString::fromStdString("no");
                                if (searchInScope(name2,type,scopeNum)!=no){
                                    string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                    istringstream(value2) >> f;
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,0,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,0,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,0,1).toUtf8().constData() << endl;
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                                }
                                qDebug() << this->variables << endl;
                            }
                        }
                    } else if (istringstream(lineDivided[3].substr (0,lineDivided[3].length()-1)) >> f && istringstream(lineDivided[5].substr (0,lineDivided[5].length()-1)) >> f2 && lineDivided[3][lineDivided[3].size()-1]=='f' && lineDivided[5][lineDivided[5].size()-1]=='f'){
                        cout << "CASO 2" << endl;
                        IsOrNot(name,type);
                        istringstream(lineDivided[3].substr (0,lineDivided[3].length()-1)) >> f;
                        istringstream(lineDivided[5].substr (0,lineDivided[5].length()-1)) >> f2;
                        if (runKind==1 && this->alreadyIs==0){
                            Counting(name);
                        }
                        if (lineDivided[4]=="+" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve2(f,f2,1) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve2(f,f2,1));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,1).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve2(f,f2,2) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve2(f,f2,2));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,2).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve2(f,f2,3) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve2(f,f2,3));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,3).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve2(f,f2,4) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve2(f,f2,4));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,4).toUtf8().constData() << endl;

                        } else {
                            alreadyIs = 1;
                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                        }
                        qDebug() << this->variables << endl;
                        ////////*/

                    } else if (istringstream(lineDivided[5].substr (0,lineDivided[5].length()-1)) >> f && lineDivided[5][lineDivided[5].size()-1]=='f'){
                        cout << "CASO 3" << endl;
                        IsOrNot(name,type);
                        istringstream(lineDivided[5].substr (0,lineDivided[5].length()-1)) >> f;
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                            }
                            if (searchInScope(name2,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                istringstream(value2) >> f2;
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f2,f,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f2,f,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f2,f,1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f2,f,2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f2,f,2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f2,f,2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f2,f,3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f2,f,3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f2,f,3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f2,f,4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f2,f,4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f2,f,4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }


                    } else if (istringstream(lineDivided[3].substr (0,lineDivided[3].length()-1)) >> f && lineDivided[3][lineDivided[3].size()-1]=='f') {
                        cout << "CASO 4" << endl;
                        IsOrNot(name,type);
                        istringstream(lineDivided[3].substr (0,lineDivided[3].length()-1)) >> f;
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[5];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                            }
                            if (searchInScope(name2,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                istringstream(value2) >> f2;
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,f2,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,f2,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,f2,2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,f2,2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,f2,3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,f2,3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,f2,4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,f2,4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else if (1){
                        cout << "CASO 5" << endl;
                        IsOrNot(name,type);

                        if (this->alreadyIs==0){
                            cout << lineDivided.size() << endl;
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            string nombre3 = lineDivided[5];
                            QString name3 = QString::fromStdString(nombre3);
                            QString no = QString::fromStdString("no");
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                                Counting(name3);
                            }

                            if (searchInScope(name2,type,scopeNum)!=no || searchInScope(name3,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                string value3 = searchInScope(name3,type,scopeNum).toUtf8().constData();
                                istringstream(value2) >> f;
                                istringstream(value3) >> f2;
                                cout << value2 << " " << value3 << endl;
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,f2,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,f2,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,f2,2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,f2,2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,f2,3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,f2,3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve2(f,f2,4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve2(f,f2,4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve2(f,f2,4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else {
                        log("[ERROR]","Error en la asignacion de valor a una variable en linea. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                        throw "Error en la asignacion de valor a una variable en linea ";
                    }

                } catch(const char* msg) {
                    cout << msg << i << endl;
                }
            } else {
                ////////
                IsOrNot(name,type);
                if (this->alreadyIs==0){
                    this->variables.append(name + "|" + type + "|" + "0" + "|" + scopeNum);
                    log("[INFO]","Variable " +name+ " de tipo " + type + " definida sin valor asignado");
                    sendMsg(name,this->J.ParseJson(0));
                    J.Write("1",name,type,"0");
                    J.CreateJsonFile();
                    malloc.Principal();

                    RamView();
                    cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
                    if (runKind==1){
                        Counting(name);

                    }
                } else {
                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                }
                qDebug() << this->variables << endl;
                ////////
            }

        } else if (lineDivided[0]=="long"){
            string tipo = "long";
            string nombre = lineDivided[1];
            string espacio = "8";
            QString type = QString::fromStdString(lineDivided[0]);
            QString name = QString::fromStdString(nombre);
            QString scopeNum = QString::number(this->contScope);

            ////////
            if (lineDivided.size()>3 && lineDivided[2]=="="){
                long l;
                long l2;
                try {
                    string::size_type sz;   // alias of size_t

                    if(lineDivided.size()<=4)////
                    {
                        cout << "CASO 1" << endl;
                        if (atol(lineDivided[3].c_str())){
                            //istringstream(lineDivided[3]) >> l;
                            l = atol(lineDivided[3].c_str());
                            auto s = std::to_string(l);
                            string valor = s;
                            //string valor = lineDivided[3];
                            ////////
                            QString value = QString::fromStdString(valor);
                            IsOrNot(name,type);

                            if (this->alreadyIs==0){
                                this->variables.append(name + "|" + type + "|" + value + "|" + scopeNum);
                                log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                sendMsg(name,this->J.ParseJson(0));
                                J.Write("1",name,type,value);
                                J.CreateJsonFile();
                                malloc.Principal();

                                RamView();
                                cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;
                                if (runKind==1){
                                    Counting(name);

                                }
                            } else {
                                alreadyIs = 1;
                                log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                            }

                            qDebug() << this->variables << endl;
                            ////////

                        } else {
                            //cout << "AHORA?" << endl;
                            //cout << "AHORA?" << endl;
                            IsOrNot(name,type);
                            if (this->alreadyIs==0){
                                string nombre2 = lineDivided[3];
                                QString name2 = QString::fromStdString(nombre2);
                                if (runKind==1){
                                    Counting(name);
                                    Counting(name2);
                                }
                                QString no = QString::fromStdString("no");
                                if (searchInScope(name2,type,scopeNum)!=no){
                                    string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();

                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),0,1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),0,1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atoi(value2.c_str()),0,1).toUtf8().constData() << endl;
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                                }
                                qDebug() << this->variables << endl;

                            }
                        }

                    } else if (atol(lineDivided[3].c_str()) && atol(lineDivided[5].c_str())){
                        if (runKind==1){
                            Counting(name);
                        }
                        IsOrNot(name,type);
                        if (lineDivided[4]=="+" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),1) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),1));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),1).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),2) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),2));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),2).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),3) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),3));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),3).toUtf8().constData() << endl;

                        } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                            this->variables.append(name + "|" + type + "|" + Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),4) + "|" + scopeNum);
                            log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                            sendMsg(name,this->J.ParseJson(0));
                            J.Write("1",name,type,Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),4));
                            J.CreateJsonFile();
                            malloc.Principal();

                            RamView();
                            cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(lineDivided[3].c_str()),atol(lineDivided[5].c_str()),4).toUtf8().constData() << endl;

                        } else {
                            alreadyIs = 1;
                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                        }
                        qDebug() << this->variables << endl;
                        ////////
                    } else if (atol(lineDivided[5].c_str())){
                        IsOrNot(name,type);
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                            }
                            if (searchInScope(name2,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(value2.c_str()),atol(lineDivided[5].c_str()),4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else if (atol(lineDivided[3].c_str())) {
                        IsOrNot(name,type);
                        if (this->alreadyIs==0){
                            string nombre2 = lineDivided[5];
                            QString name2 = QString::fromStdString(nombre2);
                            QString no = QString::fromStdString("no");
                            //qDebug() << searchInScope(name2,type,scopeNum) << endl;
                            //qDebug() << this->variables << endl;
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                            }
                            if (searchInScope(name2,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(lineDivided[3].c_str()),atol(value2.c_str()),4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else if (1){

                        IsOrNot(name,type);
                        if (this->alreadyIs==0){
                            cout << lineDivided.size() << endl;
                            string nombre2 = lineDivided[3];
                            QString name2 = QString::fromStdString(nombre2);
                            string nombre3 = lineDivided[5];
                            QString name3 = QString::fromStdString(nombre3);
                            QString no = QString::fromStdString("no");
                            if (runKind==1){
                                Counting(name);
                                Counting(name2);
                                Counting(name3);
                            }
                            if (searchInScope(name2,type,scopeNum)!=no || searchInScope(name3,type,scopeNum)!=no){
                                string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                string value3 = searchInScope(name3,type,scopeNum).toUtf8().constData();
                                cout << value2 << " " << value3 << endl;
                                if (lineDivided[4]=="+" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),atol(value3.c_str()),1) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),atol(value3.c_str()),1));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(value2.c_str()),atol(value3.c_str()),1).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="-" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),atol(value3.c_str()),2) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),atol(value3.c_str()),2));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(value2.c_str()),atol(value3.c_str()),2).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="*" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),atol(value3.c_str()),3) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),atol(value3.c_str()),3));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(value2.c_str()),atol(value3.c_str()),3).toUtf8().constData() << endl;
                                } else if (lineDivided[4]=="/" && this->alreadyIs==0){
                                    this->variables.append(name + "|" + type + "|" + Solve(atol(value2.c_str()),atol(value3.c_str()),4) + "|" + scopeNum);
                                    log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                    sendMsg(name,this->J.ParseJson(0));
                                    J.Write("1",name,type,Solve(atol(value2.c_str()),atol(value3.c_str()),4));
                                    J.CreateJsonFile();
                                    malloc.Principal();

                                    RamView();
                                    cout << "Variable de tipo " << tipo << " asignada con un valor de " << Solve(atol(value2.c_str()),atol(value3.c_str()),4).toUtf8().constData() << endl;
                                } else {
                                    alreadyIs = 1;
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea. Operador desconocido ";
                                }
                            } else {
                                log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                            }
                            qDebug() << this->variables << endl;

                        } else {
                            log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                            throw "Variable ya existente. Error en la asignacion de valor a una variable en linea ";
                        }

                    } else {
                        log("[ERROR]","Error en la asignacion de valor a una variable en linea. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                        throw "Error en la asignacion de valor a una variable en linea ";
                    }

                } catch(const char* msg) {
                    cout << msg << i << endl;
                }
            } else {
                ////////

                IsOrNot(name,type);
                if (this->alreadyIs==0){
                    this->variables.append(name + "|" + type + "|" + "0" + "|" + scopeNum);
                    log("[INFO]","Variable " +name+ " de tipo " + type + " definida sin valor asignado");
                    sendMsg(name,this->J.ParseJson(0));
                    J.Write("1",name,type,"0");
                    J.CreateJsonFile();
                    malloc.Principal();

                    RamView();
                    cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
                    if (runKind==1){
                        Counting(name);
                    }
                } else {
                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                }
                qDebug() << this->variables << endl;
                ////////

            }

        } else if (lineDivided[0]=="char"){
            if (lineDivided[2][0] == '[' && lineDivided[2][lineDivided[2].size()-1] == ']'){
                string tipo = "char";
                string nombre = lineDivided[1];
                QString type = QString::fromStdString(lineDivided[0]);
                QString name = QString::fromStdString(nombre);
                QString scopeNum = QString::number(this->contScope);

                if (lineDivided.size()>4 && lineDivided[3]=="="){
                    try {
                        //cout << "uno" << endl;

                        if(atoi(lineDivided[2].substr (1,lineDivided[2].size()-1).c_str()))
                        {
                            //cout << "dos" << endl;
                            string espacio = lineDivided[2].substr (0,lineDivided[2].length()-1);
                            string espacio2 = espacio.substr (1,espacio.length()-1);
                            cout << espacio2 << endl;
                            int sp;
                            if (lineDivided[4][lineDivided[4].size()-1]=='"' && lineDivided[4][0]=='"' ){
                                if (runKind==1){
                                    Counting(name);

                                }

                                if (istringstream(espacio2) >> sp){
                                    //cout << "tres" << endl;
                                    IsOrNot(name,type);

                                    if (sp>=lineDivided[4].size()-2 && alreadyIs==0){
                                        string valor = lineDivided[4].substr (1,lineDivided[4].length()-2);
                                        QString value = QString::fromStdString(valor);
                                        this->variables.append(name + "|" + type + "|" + value + "|" + scopeNum);
                                        log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                        sendMsg(name,this->J.ParseJson(0));
                                        J.Write("1",name,type,value);
                                        J.CreateJsonFile();
                                        malloc.Principal();

                                        RamView();
                                        cout << "Variable de tipo " << tipo << " asignada con un valor de " << valor << endl;
                                    } else {
                                        log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                                    }
                                    qDebug() << this->variables << endl;
                                    ////////
                                 } else {
                                    log("[ERROR]","Error en la asignacion de valor a una variable en linea. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    throw "Error en la asignacion de valor a una variable en linea ";
                                 }
                            } else if(atoi(lineDivided[2].substr (1,lineDivided[2].size()-1).c_str()) && istringstream(espacio2) >> sp){
                                    IsOrNot(name,type);
                                    if (this->alreadyIs==0){
                                        string nombre2 = lineDivided[4];
                                        QString name2 = QString::fromStdString(nombre2);
                                        if (runKind==1){
                                            Counting(name);
                                            Counting(name2);
                                        }
                                        QString no = QString::fromStdString("no");
                                        if (searchInScope(name2,type,scopeNum)!=no){
                                            string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                            QString value3 = QString::fromStdString(value2);
                                            cout << value2.size() << " tayaaa " << endl;
                                            cout << sp << " tadaaa " << endl;
                                            if (value2.size()<=sp){
                                                this->variables.append(name + "|" + type + "|" + value3 + "|" + scopeNum);
                                                log("[INFO]","Variable " +name+ " de tipo " + type + " asignada");
                                                sendMsg(name,this->J.ParseJson(0));
                                                J.Write("1",name,type,value3);
                                                J.CreateJsonFile();
                                                malloc.Principal();

                                                RamView();
                                                cout << "Variable de tipo " << tipo << " asignada con un valor de " << value3.toUtf8().constData() << endl;
                                            } else {
                                                log("[ERROR]","Dimension de la variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                                throw "Dimension de la variable incompatible. Error en la asignacion de valor a una variable en linea ";
                                            }
                                        } else {
                                            log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                                        }
                                        qDebug() << this->variables << endl;

                                    } else {
                                        log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        throw "Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea ";
                                    }

                            } else {
                                log("[ERROR]","Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                throw "Error en la asignacion de valor a una variable en linea ";
                            }

                        }
                    } catch(const char* msg) {
                        cout << msg << i << endl;
                    }
                } else {
                    //cout << "Seraaaa" << endl;
                    ////////
                    IsOrNot(name,type);
                    if (alreadyIs==0){
                        this->variables.append(name + "|" + type + "|" + "0" + "|" + scopeNum);
                        log("[INFO]","Variable " +name+ " de tipo " + type + " definida sin valor asignado");
                        sendMsg(name,this->J.ParseJson(0));
                        J.Write("1",name,type,"0");
                        J.CreateJsonFile();
                        malloc.Principal();

                        RamView();
                        cout << "Variable " << nombre << " de tipo " << tipo << " definida sin valor asignado " << endl;
                    } else {
                        log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                        cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                    }
                    qDebug() << this->variables << endl;
                    ////////
                }
            } else {
                log("[ERROR]","Error en la asignacion de valor a una variable en linea "+QString::number(i));
            }
        } else {
            if (lineDivided.size()>=3 && lineDivided[1]=="="){
                string nombre = lineDivided[0];
                QString name = QString::fromStdString(nombre);
                QString scopeNum = QString::number(this->contScope);

                IsOrNot(name,name);

                cout << this->alreadyIs << endl;
                if (this->alreadyIs==1){
                    string tipo = searchInScope2(name,scopeNum).toUtf8().constData();
                    QString type = QString::fromStdString(tipo);
                    QString type1 = "int";
                    QString type2 = "float";
                    QString type3 = "double";
                    QString type4 = "long";
                    if (lineDivided.size()==3){
                        cout << "caso 11111" << endl;
                        if (type == type1){
                            if (atoi(lineDivided[2].c_str())){
                                cout << "a ver " << atoi(lineDivided[2].c_str()) << endl;
                                setValue(name,atoi(lineDivided[2].c_str()),type1,scopeNum);
                                sendMsg(name,this->J.ParseJson(1));
                                QString lue = QString::number(atoi(lineDivided[2].c_str()));
                                J.Write("2",name,type,lue);
                                J.CreateJsonFile();

                                if (runKind==1){
                                    Counting(name);
                                }
                            } else {
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        string value2 = searchInScope(name2,type1,scopeNum).toUtf8().constData();
                                        log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                        setValue(name,atoi(value2.c_str()),type1,scopeNum);
                                        sendMsg(name,this->J.ParseJson(1));
                                        QString lue = QString::number(atoi(lineDivided[2].c_str()));
                                        J.Write("2",name,type,lue);
                                        J.CreateJsonFile();
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }

                                } else {
                                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                                }
                            }
                        } else if (type == type4){
                            if (atol(lineDivided[2].c_str())){
                                cout << "a ver " << atoi(lineDivided[2].c_str()) << endl;
                                setValue(name,atol(lineDivided[2].c_str()),type4,scopeNum);
                                QString lue = QString::number(atol(lineDivided[2].c_str()));
                                J.Write("2",name,type,lue);
                                J.CreateJsonFile();
                                sendMsg(name,this->J.ParseJson(1));
                                if (runKind==1){
                                    Counting(name);
                                }
                            } else {
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        string value2 = searchInScope(name2,type4,scopeNum).toUtf8().constData();
                                        log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                        setValue(name,atol(value2.c_str()),type4,scopeNum);
                                        QString lue = QString::number(atol(value2.c_str()));
                                        J.Write("2",name,type,lue);
                                        J.CreateJsonFile();
                                        sendMsg(name,this->J.ParseJson(1));
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }

                                } else {
                                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                                }
                            }

                        } else if(type == type2 || type == type3){
                            double d;
                            double d2;
                            if (istringstream(lineDivided[2]) >> d){
                                cout << "a ver " << d << endl;
                                setValue(name,d,type4,scopeNum);
                                QString lue = QString::number(d);
                                J.Write("2",name,type,lue);
                                J.CreateJsonFile();
                                sendMsg(name,this->J.ParseJson(1));
                                if (runKind==1){
                                    Counting(name);
                                }
                            } else {
                                //QString value = QString::fromStdString(valor)
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        string value2 = searchInScope(name2,type,scopeNum).toUtf8().constData();
                                        istringstream(value2) >> d2;
                                        log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                        setValue(name,d2,type,scopeNum);
                                        QString lue = QString::number(d2);
                                        J.Write("2",name,type,lue);
                                        J.CreateJsonFile();
                                        sendMsg(name,this->J.ParseJson(1));
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }

                                } else {
                                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                                }
                            }
                        }

                    } else if (lineDivided.size()==5){
                        cout << "caso 22222" << endl;
                        if (type == type1){
                            if (atoi(lineDivided[2].c_str()) && atoi(lineDivided[4].c_str())){
                                //cout << "a ver " << atoi(lineDivided[2].c_str()) << endl;
                                if (runKind==1){
                                    Counting(name);
                                }
                                if (lineDivided[3]=="+"){
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),1).toUtf8().constData()),type1,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    //QString lue = QString::number(Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),1));
                                    J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),1));
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="-"){
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),2).toUtf8().constData()),type1,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    //QString lue = QString::number(Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),2));
                                    J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),2));
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="*"){
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),3).toUtf8().constData()),type1,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    //QString lue = QString::number(Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),3));
                                    J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),3));
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="/"){
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),4).toUtf8().constData()),type1,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    //QString lue = QString::number(Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),4));
                                    J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atoi(lineDivided[4].c_str()),4));
                                    J.CreateJsonFile();
                                } else {
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de variable" << endl;
                                }
                            } else if (atoi(lineDivided[4].c_str())){
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        cout << value3 << endl;
                                        cout << lineDivided[4] << endl;
                                        if (lineDivided[3]=="+"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),1).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),1));
                                            J.Write("2",name,type,Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),1));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="-"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),2).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),2));
                                            J.Write("2",name,type,Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),2));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="*"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),3).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),3));
                                            J.Write("2",name,type,Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),3));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="/"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),4).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),4));
                                            J.Write("2",name,type,Solve2(atoi(value3.c_str()),atoi(lineDivided[4].c_str()),4));
                                            J.CreateJsonFile();
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    cout << "Error en la asignacion de la variable " << endl;
                                }
                            } else if(atoi(lineDivided[2].c_str())){
                                string nombre2 = lineDivided[4];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        //cout << value3 << endl;
                                        if (lineDivided[3]=="+"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),1).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),1));
                                            J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),1));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="-"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),2).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),2));
                                            J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),2));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="*"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),3).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),3));
                                            J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),3));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="/"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),4).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),4));
                                            J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atoi(value3.c_str()),4));
                                            J.CreateJsonFile();
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    cout << "Error en la asignacion de la variable " << endl;
                                }
                            } else if(1){
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                string nombre3 = lineDivided[4];
                                QString name3 = QString::fromStdString(nombre3);
                                IsOrNot(name2,name);
                                IsOrNot(name3,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                        Counting(name3);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    string tipo3 = searchInScope2(name3,scopeNum).toUtf8().constData();
                                    QString type3 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        QString value4 = searchInScope(name3, type3, scopeNum);
                                        string value5 = value4.toUtf8().constData();
                                        //cout << value3 << " yyyy " << value5 << endl;
                                        if (lineDivided[3]=="+"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),1).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),1));
                                            J.Write("2",name,type,Solve2(atoi(value3.c_str()),atoi(value5.c_str()),1));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="-"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),2).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),2));
                                            J.Write("2",name,type,Solve2(atoi(value3.c_str()),atoi(value5.c_str()),2));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="*"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),3).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),3));
                                            J.Write("2",name,type,Solve2(atoi(value3.c_str()),atoi(value5.c_str()),3));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="/"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),4).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),4));
                                            J.Write("2",name,type,Solve2(atoi(value3.c_str()),atoi(value5.c_str()),4));
                                            J.CreateJsonFile();
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de la variable " << endl;
                                }////////
                            } else {
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        string value2 = searchInScope(name2,type1,scopeNum).toUtf8().constData();
                                        log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                        setValue(name,1,type1,scopeNum);
                                        sendMsg(name,this->J.ParseJson(1));
                                        //QString lue = QString::number(atoi(Solve2(atoi(value3.c_str()),atoi(value5.c_str()),1));
                                        J.Write("2",name,type,"1");
                                        J.CreateJsonFile();
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }

                                } else {
                                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                                }
                            }
                        } else if (type == type4){
                            if (atol(lineDivided[2].c_str()) && atol(lineDivided[4].c_str())){
                                //cout << "a ver " << atoi(lineDivided[2].c_str()) << endl;
                                if (runKind==1){
                                    Counting(name);

                                }
                                if (lineDivided[3]=="+"){
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,atol(Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),1).toUtf8().constData()),type1,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    //QString lue = QString::number(atol(Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),1));
                                    J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),1));
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="-"){
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,atol(Solve2(atol(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),2).toUtf8().constData()),type1,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    //QString lue = QString::number(atol(Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),2));
                                    J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),2));
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="*"){
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,atol(Solve2(atol(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),3).toUtf8().constData()),type1,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    //QString lue = QString::number(atol(Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),3));
                                    J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),3));
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="/"){
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,atol(Solve2(atol(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),4).toUtf8().constData()),type1,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    //QString lue = QString::number(atol(Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),4));
                                    J.Write("2",name,type,Solve2(atoi(lineDivided[2].c_str()),atol(lineDivided[4].c_str()),4));
                                    J.CreateJsonFile();
                                } else {
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de variable" << endl;
                                }
                            } else if (atol(lineDivided[4].c_str())){
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (runKind==1){
                                    Counting(name);
                                    Counting(name2);
                                }
                                if (alreadyIs==1){
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        //cout << value3 << endl;
                                        if (lineDivided[3]=="+"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),1).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),1));
                                            J.Write("2",name,type,Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),1));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="-"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),2).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),2));
                                            J.Write("2",name,type,Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),2));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="*"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),3).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),3));
                                            J.Write("2",name,type,Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),3));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="/"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),4).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),4));
                                            J.Write("2",name,type,Solve2(atol(value3.c_str()),atol(lineDivided[4].c_str()),4));
                                            J.CreateJsonFile();
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de la variable " << endl;
                                }
                            } else if(atol(lineDivided[2].c_str())){
                                string nombre2 = lineDivided[4];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        //cout << value3 << endl;
                                        if (lineDivided[3]=="+"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),1).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),1));
                                            J.Write("2",name,type,Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),1));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="-"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),2).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),2));
                                            J.Write("2",name,type,Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),2));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="*"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),3).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),3));
                                            J.Write("2",name,type,Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),3));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="/"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),4).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),4));
                                            J.Write("2",name,type,Solve2(atol(lineDivided[2].c_str()),atol(value3.c_str()),4));
                                            J.CreateJsonFile();
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de la variable " << endl;
                                }
                            } else if(1){
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                string nombre3 = lineDivided[4];
                                QString name3 = QString::fromStdString(nombre3);
                                IsOrNot(name2,name);
                                IsOrNot(name3,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                        Counting(name3);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    string tipo3 = searchInScope2(name3,scopeNum).toUtf8().constData();
                                    QString type3 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        QString value4 = searchInScope(name3, type3, scopeNum);
                                        string value5 = value4.toUtf8().constData();
                                        //cout << value3 << " yyyy " << value5 << endl;
                                        if (lineDivided[3]=="+"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),1).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),1));
                                            J.Write("2",name,type,Solve2(atol(value3.c_str()),atol(value5.c_str()),1));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="-"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),2).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),2));
                                            J.Write("2",name,type,Solve2(atol(value3.c_str()),atol(value5.c_str()),2));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="*"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),3).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),3));
                                            J.Write("2",name,type,Solve2(atol(value3.c_str()),atol(value5.c_str()),3));
                                            J.CreateJsonFile();
                                        } else if (lineDivided[3]=="/"){
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),4).toUtf8().constData()),type,scopeNum);
                                            sendMsg(name,this->J.ParseJson(1));
                                            //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),4));
                                            J.Write("2",name,type,Solve2(atol(value3.c_str()),atol(value5.c_str()),4));
                                            J.CreateJsonFile();
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de la variable " << endl;
                                }////////
                            } else {
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        string value2 = searchInScope(name2,type1,scopeNum).toUtf8().constData();
                                        log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                        setValue(name,1,type1,scopeNum);
                                        sendMsg(name,this->J.ParseJson(1));
                                        //QString lue = QString::number(atol(Solve2(atol(value3.c_str()),atol(value5.c_str()),1));
                                        J.Write("2",name,type,"1");
                                        J.CreateJsonFile();
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }

                                } else {
                                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                                }
                            }
                        } else if (type==type2 || type==type3){
                            double d;
                            double d2;
                            if (istringstream (lineDivided[2]) >> d && istringstream (lineDivided[4]) >> d2){
                                //cout << "a ver " << atoi(lineDivided[2].c_str()) << endl;
                                if (runKind==1){
                                    Counting(name);

                                }
                                if (lineDivided[3]=="+"){
                                    //cout << Solve2(d,d2,1).toUtf8().constData() << endl;
                                    istringstream(Solve2(d,d2,1).toUtf8().constData()) >> d;
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,d,type,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    QString lue = QString::number(d);
                                    J.Write("2",name,type,lue);
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="-"){
                                    istringstream(Solve2(d,d2,2).toUtf8().constData()) >> d;
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,d,type,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    QString lue = QString::number(d);
                                    J.Write("2",name,type,lue);
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="*"){
                                    istringstream(Solve2(d,d2,3).toUtf8().constData()) >> d;
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,d,type,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    QString lue = QString::number(d);
                                    J.Write("2",name,type,lue);
                                    J.CreateJsonFile();
                                } else if (lineDivided[3]=="/"){
                                    istringstream(Solve2(d,d2,4).toUtf8().constData()) >> d;
                                    log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                    setValue(name,d,type,scopeNum);
                                    sendMsg(name,this->J.ParseJson(1));
                                    QString lue = QString::number(d);
                                    J.Write("2",name,type,lue);
                                    J.CreateJsonFile();
                                } else {
                                    log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de variable" << endl;
                                }
                            } else if (istringstream (lineDivided[4]) >> d){
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);

                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        istringstream (value3) >> d2;
                                        //cout << value3 << endl;
                                        if (lineDivided[3]=="+"){
                                            istringstream(Solve2(d,d2,1).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="-"){
                                            istringstream(Solve2(d,d2,2).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="*"){
                                            istringstream(Solve2(d,d2,3).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="/"){
                                            istringstream(Solve2(d,d2,4).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de la variable " << endl;
                                }
                            } else if(istringstream (lineDivided[2]) >> d){
                                string nombre2 = lineDivided[4];
                                QString name2 = QString::fromStdString(nombre2);

                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        istringstream (value3) >> d2;
                                        //cout << value3 << endl;
                                        if (lineDivided[3]=="+"){
                                            istringstream(Solve2(d,d2,1).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="-"){
                                            istringstream(Solve2(d,d2,2).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="*"){
                                            istringstream(Solve2(d,d2,3).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="/"){
                                            istringstream(Solve2(d,d2,4).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de la variable " << endl;
                                }
                            } else if(1){
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                string nombre3 = lineDivided[4];
                                QString name3 = QString::fromStdString(nombre3);
                                IsOrNot(name2,name);
                                IsOrNot(name3,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);
                                        Counting(name3);
                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    string tipo3 = searchInScope2(name3,scopeNum).toUtf8().constData();
                                    QString type3 = QString::fromStdString(tipo);
                                    //cout << tipo2 << endl;
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        QString value2 = searchInScope(name2, type2, scopeNum);
                                        string value3 = value2.toUtf8().constData();
                                        QString value4 = searchInScope(name3, type3, scopeNum);
                                        string value5 = value4.toUtf8().constData();
                                        //cout << value3 << " yyyy " << value5 << endl;
                                        istringstream(value3) >> d;
                                        istringstream(value5) >> d2;

                                        if (lineDivided[3]=="+"){
                                            istringstream(Solve2(d,d2,1).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="-"){
                                            istringstream(Solve2(d,d2,2).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="*"){
                                            istringstream(Solve2(d,d2,3).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else if (lineDivided[3]=="/"){
                                            istringstream(Solve2(d,d2,4).toUtf8().constData()) >> d;
                                            log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                            setValue(name,d,type,scopeNum);
                                            QString lue = QString::number(d);
                                            J.Write("2",name,type,lue);
                                            J.CreateJsonFile();
                                            sendMsg(name,this->J.ParseJson(1));
                                        } else {
                                            log("[ERROR]","Operador desconocido. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                            cout << "Error en la asignacion de variable" << endl;
                                        }
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }
                                } else {
                                    log("[ERROR]","Variable fuera del scope o indefinida. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Error en la asignacion de la variable " << endl;
                                }////////
                            } else {
                                string nombre2 = lineDivided[2];
                                QString name2 = QString::fromStdString(nombre2);
                                IsOrNot(name2,name);
                                if (alreadyIs==1){
                                    if (runKind==1){
                                        Counting(name);
                                        Counting(name2);

                                    }
                                    string tipo2 = searchInScope2(name2,scopeNum).toUtf8().constData();
                                    QString type2 = QString::fromStdString(tipo);
                                    if (tipo2!="char" && tipo2!="struct" && tipo2!="reference"){
                                        string value2 = searchInScope(name2,type1,scopeNum).toUtf8().constData();
                                        log("[INFO]","Variable " +name+ " ha cambiado su valor");
                                        setValue(name,1,type1,scopeNum);
                                        //QString lue = QString::number(d);
                                        J.Write("2",name,type,"1");
                                        J.CreateJsonFile();
                                        sendMsg(name,this->J.ParseJson(1));
                                    } else {
                                        log("[ERROR]","Tipo de variable incompatible. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                        cout << "Tipo de variable incompatible" << endl;
                                    }

                                } else {
                                    log("[ERROR]","Variable ya existente. Error en la asignacion de valor a una variable en linea "+QString::number(i));
                                    cout << "Variable ya existente. Error en la asignacion de valor a una variable en linea " << i << endl;
                                }
                            }


                        }
                    }

                } else {
                    log("[ERROR]", "Error al declarar variable");
                }
                qDebug() << this->variables << endl;

            }
            //qDebug() << searchInScope2(name,scopeNum) << endl;
/////////////////////////////////////

        }

    }
}




void Widget::on_pushButton_6_clicked()
{
    QString plainTextEditContents = ui->plainTextEdit->toPlainText();
    QStringList lines = plainTextEditContents.split("\n");
    //cout << lines[0].toUtf8().constData() << endl;
    Recon(lines,0);
    //this->J.ParseJson(2);



}

void Widget::sendMensaje()
{
    conexion->setMensaje(ui->lineEdit_16->text().toStdString().c_str());

}

void Widget::printMensaje(QString msn)
{
    ui->plainTextEdit->setPlainText(msn);
}

void Widget::on_pushButton_clicked()
{

    QString plainTextEditContents = ui->plainTextEdit->toPlainText();
    QStringList lines = plainTextEditContents.split("\n");
    //cout << lines[0].toUtf8().constData() << endl;
    this->codeLines2 = plainTextEditContents.split("\n");
    Recon(lines,1);
    this->pos+=1;
    cout << this->pos << endl;
    //this->variables.clear();

}

void Widget::on_dial_3_sliderPressed()
{
    ui->plainTextEdit_3->clear();
}

void Widget::on_pushButton_2_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit_4->clear();
    this->variables.clear();
    this->pos=1;
    qDebug() << this->variables << endl;
}

void Widget::on_pushButton_3_clicked()
{
    log("[WARN]","Garbage Collector activado");

    QString plainTextEditContents = ui->plainTextEdit->toPlainText();
    this->codeLines2 = plainTextEditContents.split("\n");
    for (int k = 0; k<this->variables.size();k++){
        QStringList variables2 = this->variables[k].split("|");
        qDebug() << this->codeLines2 << endl;

        for (int i = 0;i<this->codeLines2.size();i++){
            string line = this->codeLines2[i].toUtf8().constData();
            qDebug() << variables2 << endl;
            //cout << line << "\n"; // Toda la linea
            vector<string> lineDivided;
            boost::split(lineDivided, line, boost::is_any_of(" "));
            for (int z = 0;z<lineDivided.size();z++){
                if(lineDivided[z]==variables2[0].toUtf8().constData()){
                    this->VarCont+=1;
                }

            }

        }
        cout << "Essssss : " << this->VarCont << endl;
        QString vc = QString::number(this->VarCont);
        this->variables3.append(variables2[0] + "|" +vc);
        this->variables3Copy.append(variables2[0] + "|" +"0");
        //qDebug() << variables2[0] << endl;
        qDebug() << this->variables3 << endl;
        //qDebug() << this->variables3Copy[0][0] << endl;
        //qDebug() << this->variables3Copy << endl;

        this->VarCont=0;

    }
}

void Widget::on_pushButton_4_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit_4->clear();
    this->variables.clear();
    this->pos=1;
    ui->plainTextEdit_3->clear();
    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_5->clear();

    this->contScope = 0;
    this->scopes.clear();

    this->codeLines2.clear();
    this->VarCont = 0;
    this->refCont.clear();
    this->variables3.clear();
    this->variables3Copy.clear();
    for (int u = 0;u<15;u++){
        this->counters[u]=0;

    }
    this->alreadyIs = false;
}
