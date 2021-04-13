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
