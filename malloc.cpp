#include "malloc.h"
#include "json.h"
#include <QString>
#include <iostream>
#include <QDebug>
#include <QLatin1String>
#include <QCharRef>
#include <vector>
#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
using namespace std;

/**
 * @brief The tipo struct EStructura que permite el manejo de los diferentes tipos de datos para el control de la memoria
 */
struct tipo{
    int entero;
    const char* cadena;
    double doble;
    float flotante;
    long longer;
    int reference;
    QString estructura;
};

/**
 * Constructor
*/
Malloc::Malloc()
{

}
/**
 * Vector que maneja el archivo Json
 */
vector < QJsonObject > mSVec;

/**
 * Funcion para asignar los que se desea escribir en el archivo Json
 */
void Malloc::WriteJsonServer(){
    QJsonObject myPetition;
    QString myMsg = "Mensaje ,";
    myPetition ["memoryD"]= this->memoryspace;
    myPetition ["name"] = this->nombre;
    myPetition ["o_value"]= this->valor ;
    myPetition ["reference"] = this->referencia;
    mSVec.push_back(myPetition);
}

/**
 * Funcion para crear el archivo Json correspondiente a la respuesta del servidor
 */
void Malloc::CreateJsonServerFile(){
    QFile mfile("respuestaS.json");
    if (!mSVec.empty()){
        cout << mSVec.size() << "Dates saved" << endl;
        if(mfile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&mfile);
            for(auto it = mSVec.begin(); it != mSVec.end(); it ++)
            {
                out << QJsonDocument(*it).toJson() << endl;
            }
            mSVec.clear();
            mfile.flush();
            mfile.close();
        }
    }

}


/**
 * Funcion para Leer el archivo .json creado por el IDE con la petición requerida
 */
void Malloc::LeerJson()
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
                it= it+0;
                this->peticion =it.value().toString();
                qDebug()<< this->peticion << endl;
                it++;
                this->nombre =it.value().toString();
                qDebug()<< this->nombre << endl;
                it++;
                this->type =it.value().toString();
                qDebug()<< this->type << endl;
                it++;
                this->valor =it.value().toString();
                qDebug()<< this->valor << endl;
                }
            }
    }
    else{
        cout<<"Archivo no existe"<<endl;
    }
}

/**
 * Funcion para devolver la posición de memoria solicitada
 */
struct tipo* Malloc::Memoria(int offset)
{
    return (blockmemory+offset);
}


QStringList Malloc::getV_asignada(){
    return v_asignada;
}

/**
 * Funcion donde se genera el unico malloc y se crean las funciones de cada petición
 */
void Malloc::Principal()
{
    int space_M = 100; //Numeros de bytes
    if (first == true){
        blockmemory =(tipo*) malloc(space_M * sizeof(tipo)); //es el type-cast
        this->referencia="1";
        this->memoryspace = "0";
        first = false;
    }
    LeerJson();

    int peticiones = this->peticion.toInt();
    switch (peticiones)
    {
        case 1: //Asignar
            if(space_M==0)
            {
                    cout << "Memoria no asignada"<< endl;
                }
            else if (space_M !=0)
            {

                if(type == "int")
                {
                    int valorint = valor.toInt();
                    int re = referencia.toInt();
                    int offset = memoryspace.toInt();
                    (blockmemory+offset)->entero  = valorint;
                    this->v_asignada.append( memoryspace + "|" + nombre+ "|" + valor +  "|"+ this->referencia);
                    this->v_YA.append( valor + "|" + this->nombre + "|" + memoryspace+ "|" + type + "|" +referencia);
                    //printf("%p",&(blockmemory+offset)->entero);
                    //printf("\n");
                    re ++;
                    offset++;
                    this->memoryspace =QString::number(offset);
                    this->referencia=QString::number(re);
                    qDebug() << v_asignada << endl;
                    WriteJsonServer();
                    CreateJsonServerFile();

                }

                else if(type == "float")
                {
                    float valorflo = valor.toFloat();
                    int re = referencia.toInt();
                    int offset = memoryspace.toInt();
                    (blockmemory+offset)->flotante  = valorflo;
                    this->v_asignada.append( memoryspace + "|" + nombre+ "|" + valor +  "|"+ this->referencia);
                    this->v_YA.append( valor + "|" + this->nombre + "|" + memoryspace+ "|" + type + "|" +referencia);
                    //printf("%p",&(blockmemory+offset)->float);
                    //printf("\n");
                    re ++;
                    offset++;
                    this->memoryspace =QString::number(offset);
                    this->referencia=QString::number(re);
                    qDebug() << v_asignada << endl;
                    WriteJsonServer();
                    CreateJsonServerFile();

                }

                else if (type =="double")
                {
                    double valordo = valor.toDouble();
                    int re = referencia.toInt();
                    int offset = memoryspace.toInt();
                    (blockmemory+offset)->doble  = valordo;
                    this->v_asignada.append( memoryspace + "|" + nombre+ "|" + valor +  "|"+ this->referencia);
                    this->v_YA.append( valor + "|" + this->nombre + "|" + memoryspace+ "|" + type + "|" +referencia);
                    //printf("%p",&(blockmemory+offset)->double);
                    //printf("\n");
                    re ++;
                    offset++;
                    this->memoryspace =QString::number(offset);
                    this->referencia=QString::number(re);
                    qDebug() << v_asignada << endl;
                    WriteJsonServer();
                    CreateJsonServerFile();
                }

                else if (type =="char")
                {
                    string valors = valor.toStdString();
                    const char* valorch= valors.c_str();
                    int re = referencia.toInt();
                    int offset = memoryspace.toInt();
                    (blockmemory +offset)->cadena= valorch;
                    this->v_asignada.append( memoryspace + "|" + nombre+ "|" + valor +  "|"+ this->referencia);
                    this->v_YA.append( valor + "|" + this->nombre + "|" + memoryspace+ "|" + type + "|" +referencia);
                    //printf("%p",&(blockmemory+offset)->cadena);
                    //printf("\n");
                    re ++;
                    offset++;
                    this->memoryspace =QString::number(offset);
                    this->referencia=QString::number(re);
                    qDebug() << v_asignada << endl;
                    WriteJsonServer();
                    CreateJsonServerFile();
                }

                else if (type =="long")
                {
                    long valorlo = valor.toLong();
                    int re = referencia.toInt();
                    int offset = memoryspace.toInt();
                    (blockmemory+offset)->longer  = valorlo;
                    this->v_asignada.append( memoryspace + "|" + nombre+ "|" + valor +  "|"+ this->referencia);
                    this->v_YA.append( valor + "|" + this->nombre + "|" + memoryspace+ "|" + type + "|" +referencia);
                    //printf("%p",&(blockmemory+offset)->longer);
                    //printf("\n");
                    re ++;
                    offset++;
                    this->memoryspace =QString::number(offset);
                    this->referencia=QString::number(re);
                    qDebug() << v_asignada << endl;
                    WriteJsonServer();
                    CreateJsonServerFile();
                }

                else if (type =="reference")
                {
                    qDebug() << v_asignada << endl;
                    for (int j = 0;j<this->v_asignada.size();j++){

                        QStringList variables = this->v_asignada[j].split("|");
                            if(variables[1]== valor)
                            {
                                this->valor = variables[3];
                                qDebug() << valor << endl;
                             }

                     }
                    int valorR= valor.toInt();
                    int re = referencia.toInt();
                    int offset = memoryspace.toInt();
                    (blockmemory+offset)->reference  = valorR;
                    this->v_asignada.append( memoryspace + "|" + nombre+ "|" + valor +  "|"+ this->referencia);
                    this->v_YA.append( valor + "|" + this->nombre + "|" + memoryspace+ "|" + type + "|" +referencia);
                    //printf("%p",&(blockmemory+offset)->reference);
                    //printf("\n");
                    re ++;
                    offset++;
                    this->memoryspace =QString::number(offset);
                    this->referencia=QString::number(re);
                    qDebug() << v_asignada << endl;
                    WriteJsonServer();
                    CreateJsonServerFile();
                }

                else if (type =="struct") {
                    int re = referencia.toInt();
                    int offset = memoryspace.toInt();
                    (blockmemory+offset)->estructura  = valor;
                    this->v_asignada.append( memoryspace + "|" + nombre+ "|" + valor +  "|"+ this->referencia);
                    this->v_YA.append( valor + "|" + this->nombre + "|" + memoryspace+ "|" + type + "|" +referencia);
                    //printf("%p",&(blockmemory+offset)->estructura);
                    //printf("\n");
                    re ++;
                    offset++;
                    this->memoryspace =QString::number(offset);
                    this->referencia=QString::number(re);
                    qDebug() << v_asignada << endl;
                    WriteJsonServer();
                    CreateJsonServerFile();
                }
            }
                break;

        case 2://  cambiar
                for (int j = 0;j<this->v_YA.size();j++){
                    QStringList variables = this->v_YA[j].split("|");
                    int offset = variables[2].toInt();
                    QString SaveRe = referencia;
                    QString SaveOffset = memoryspace;
                        if(variables[3]== "int")
                        {
                            if (variables[1]== nombre)
                            {
                                int valorint = valor.toInt();
                                this->memoryspace =variables[2];
                                this->referencia= variables[4];
                                (blockmemory + offset)->entero = valorint;
                                this->v_YA.append(valor+ "|" + nombre + "|" + memoryspace + "|"+ variables[3]+"|" + referencia);
                                this->v_asignada.append( memoryspace + "|"+this->nombre+ "|" + valor+ "|" + referencia);
                                this->v_asignada.removeAt(j);
                                this->v_YA.removeAt(j);
                                WriteJsonServer();
                                CreateJsonServerFile();
                                this->memoryspace =SaveRe;
                                this->referencia= SaveOffset;
                                break;
                            }
                         }

                        else if(variables[3]== "double")
                        {
                            if (variables[1]== nombre)
                            {
                                double valord = valor.toDouble();
                                this->memoryspace =variables[2];
                                this->referencia= variables[4];
                                (blockmemory + offset)->doble= valord;
                                this->v_YA.append(valor+ "|" + nombre + "|" + memoryspace + "|"+ variables[3]+"|" + referencia);
                                this->v_asignada.append( memoryspace + "|"+this->nombre+ "|" + valor+ "|" + referencia);
                                this->v_asignada.removeAt(j);
                                this->v_YA.removeAt(j);
                                WriteJsonServer();
                                CreateJsonServerFile();
                                this->memoryspace =SaveRe;
                                this->referencia= SaveOffset;
                                break;
                            }
                        }

                        else if(variables[3]== "float")
                        {
                            if (variables[1]== nombre)
                            {
                                float valorf = valor.toFloat();
                                this->memoryspace =variables[2];
                                this->referencia= variables[4];
                                (blockmemory + offset)->flotante = valorf;
                                this->v_YA.append(valor+ "|" + nombre + "|" + memoryspace + "|"+ variables[3]+"|" + referencia);
                                this->v_asignada.append( memoryspace + "|"+this->nombre+ "|" + valor+ "|" + referencia);
                                this->v_asignada.removeAt(j);
                                this->v_YA.removeAt(j);
                                WriteJsonServer();
                                CreateJsonServerFile();
                                this->memoryspace =SaveRe;
                                this->referencia= SaveOffset;
                                break;
                            }
                        }

                        else if(variables[3]== "long")
                        {
                            if (variables[1]== nombre)
                            {
                                 long valorl = valor.toLong();
                                this->memoryspace =variables[2];
                                this->referencia= variables[4];
                                (blockmemory + offset)->longer = valorl;
                                this->v_YA.append(valor+ "|" + nombre + "|" + memoryspace + "|"+ variables[3]+"|" + referencia);
                                this->v_asignada.append( memoryspace + "|"+this->nombre+ "|" + valor+ "|" + referencia);
                                this->v_asignada.removeAt(j);
                                this->v_YA.removeAt(j);
                                WriteJsonServer();
                                CreateJsonServerFile();
                                this->memoryspace =SaveRe;
                                this->referencia= SaveOffset;
                                break;
                            }
                        }

                    }
        case 3:// Consultar

        for (int j = 0;j<this->v_asignada.size();j++){
            QStringList variables = this->v_asignada[j].split("|");
            int offset = variables[2].toInt();
            QString SaveRe = referencia;
            QString SaveOffset = memoryspace;
                if(variables[2]== nombre)
                {
                    this->memoryspace =variables[0];
                    this->referencia= variables[3];
                    this->valor = variables[1];
                    WriteJsonServer();
                    CreateJsonServerFile();
                    this->memoryspace =SaveRe;
                    this->referencia= SaveOffset;
                    break;
                 }
         }
      }
    }

