#include "json.h"
#include <QJsonDocument>
#include <QDir>
#include <QJsonObject>
#include <iostream>
#include <QDebug>
using namespace std;

Json::Json()
{
    }

QString Json::ParseJson(int posicion)
{
    QString jsonStr;
    QString fileName = "/home/bryang2303/Proyecto1Datos2/peticiones.json";
    QFile myFile(fileName);
    if (myFile.exists()){
        if(myFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            jsonStr = myFile.readAll();
            myFile.close();
            QJsonDocument myDoc = QJsonDocument:: fromJson(jsonStr.toUtf8());
            QJsonObject myObj = myDoc.object();
            if (myObj.isEmpty()){
                cout<<"Elemento vacio"<<endl;
            }
            else{
                auto it = myObj.begin();
                it=it+posicion;
                QString a =it.value().toString();
                qDebug()<< a << endl;
                return a;

                }
            }

    }
    else{
        cout<<"Archivo no existe"<<endl;
    }

}
