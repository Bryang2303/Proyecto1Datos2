#ifndef JSON_H
#define JSON_H
#include<QString>
#include <iostream>
using namespace std;

class Json
{

public:
    QString elemento;
    QString ParseJson(int posicion);
    void CreateJsonFile();
    void Write(QString action, QString n, QString t, QString v);
    int getAccion();
    string getName();
    string getType();
    string getValue();
    string getMemoria();
    int getReferencia();
    Json();
};

#endif // JSON_H

