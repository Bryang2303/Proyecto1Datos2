#include "json.h"
#include <QJsonDocument>
#include <QDir>
#include <QJsonObject>
#include <iostream>
#include <QDebug>
#include <vector>
#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QTextStream>
using namespace std;

vector < QJsonObject > mVec;

Json::Json()
{
    }

void Json::Write(QString action, QString n, QString t, QString v){
    QJsonObject myPetition;
    QString myMsg = "Mensaje ,";
    myPetition ["accion"]= action ;
    myPetition ["name"] = n ;
    myPetition ["type"]= t ;
    myPetition ["value"]= v ;
    mVec.push_back(myPetition);

}
void Json::CreateJsonFile(){
    QFile mfile("PeticionIDE.json");
    if (!mVec.empty()){
        cout << mVec.size() << "  Dates saved" << endl;
        if(mfile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&mfile);
            for(auto it = mVec.begin(); it != mVec.end(); it ++)
            {
                out << QJsonDocument(*it).toJson() << endl;
            }
            mVec.clear();
            mfile.flush();
            mfile.close();
        }
    }

}

QString Json::ParseJson(int posicion)
{
    QString jsonStr;
    QString fileName = "/home/bryang2303/build-Proyecto1Datos2-Desktop_Qt_5_9_1_GCC_64bit-Debug/PeticionIDE.json";
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
int Json::getAccion(){
    int accion= this->elemento.toInt();
    return accion;
}
string Json::getName(){
    string name= this->elemento.toStdString();
    return name;
}
string Json::getType(){
    string type= this->elemento.toStdString();
    return type;
}
string Json::getValue(){
    string value= this->elemento.toStdString();
    return value;
}
string Json::getMemoria(){
    string memoria= this->elemento.toStdString();
    return memoria;
}
int Json::getReferencia(){
    int referencia= this->elemento.toInt();
    return referencia;
}
