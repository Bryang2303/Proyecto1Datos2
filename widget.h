#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include "socketcliente.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool scope = false;
    int contScope = 0;
    QStringList variables;
    QList<int> scopes = {0};
    bool alreadyIs = false;


    QStringList op = {"+","-","*","/"};
    QList<QString> inS;
    QList<QString> outS;

    void IsOrNot(QString n, QString t);
    QString searchInScope(QString n, QString t, QString scp);
    QString Solve(int first, int second, int action);
    void Recon(QStringList codelines);

private:
    Ui::Widget *ui;
    SocketCliente *conexion;

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void printMensaje(QString msn);
    void sendMensaje();

};

#endif // WIDGET_H
