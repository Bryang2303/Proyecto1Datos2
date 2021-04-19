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
