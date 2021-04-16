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
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Recon(QStringList codelines){
    int i;
    for (i=0;i<codelines.size();i++){
        string line = codelines[i].toUtf8().constData();
        //cout << line << "\n"; // Toda la linea
        vector<string> lineDivided;
        boost::split(lineDivided, line, boost::is_any_of(" "));

        string last = lineDivided[lineDivided.size()-1];

        //remove(lineDivided.begin(), lineDivided.end(), lineDivided[lineDivided.size()-1][lineDivided[lineDivided.size()-1].size()-1]);
        //cout << lineDivided[lineDivided.size()-1][lineDivided[lineDivided.size()-1].size()-1] << endl;
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
            cout << "Doble" << endl;

        } else if (lineDivided[0]=="long"){
            cout << "Largo" << endl;

        }

    }
}


void Widget::on_pushButton_clicked()
{

    array<QLineEdit*, 15> const m_edits = {ui->lineEdit,ui->lineEdit_2,ui->lineEdit_3,ui->lineEdit_4,ui->lineEdit_5,ui->lineEdit_6,ui->lineEdit_7,ui->lineEdit_8,ui->lineEdit_9,ui->lineEdit_10,ui->lineEdit_11,ui->lineEdit_12,ui->lineEdit_13,ui->lineEdit_14,ui->lineEdit_15};

    //QLineEdit *key = m_edits[i];
    //QString qw = m_edits[1]->text();
    //string cadenaStd = qw.toUtf8().constData();;
    //cout << qw.toStdString() << " sdf" << endl;
    //QString key3 = ui->lineEdit->text();
    //cout << key3.toStdString() << endl;
    for (int i = 0; i < 15; i++) {
        QString linea = m_edits[i]->text();
        cout << linea.toStdString() << "\n";
    }
    //close();

}

void Widget::on_pushButton_2_clicked()
{
    auto key = ui->textE->toPlainText().toUtf8().constData();
    cout << key << endl;
    int longitud;
    longitud = strlen(key);
    cout << longitud << endl;

    int i;
    const char *w = " ";
    string q="";
    string foo[6];
    cout << w[0] << endl;
    for (int i = 0; i < longitud; i++) {
        if (key[i]==w[0]){
            cout << "key[i]" << "\n";
        } else {
            q+=key[i];

        }
        cout << q << "\n";
      //cout << key[i] << "\n";
    }


    //Client *s = new Client();

    ui->textEdit->setText(ui->textE->toPlainText());

}

void Widget::on_pushButton_3_clicked()
{
    Client *clientGUI = new Client();
}

void Widget::on_pushButton_5_clicked()
{

    string s1 = "int arise = 12;";
    string s2 = "int";
    string s3 = ";";

    if(strstr(s1.c_str(),s2.c_str()))
    {
        if(strstr(s1.c_str(),"=")){

            cout << " S1 Contains an equalizer";
        }
    }
}

void Widget::on_pushButton_6_clicked()
{
    QString plainTextEditContents = ui->plainTextEdit->toPlainText();
    QStringList lines = plainTextEditContents.split("\n");
    //cout << lines[0].toUtf8().constData() << endl;
    Recon(lines);


}
