#include "malloc.h"
#include <QString>
#include <iostream>
#include <QDebug>
#include <QLatin1String>
using namespace std;
/**
 * @brief The tipo struct EStructura que permite el manejo de los diferentes tipos de datos para el control de la memoria
 */
struct tipo{
    int entero;
    char cadena[10];
    double doble;
    float flotante;
    long longer;
};

void Malloc::Dividir(QString ejemplo){
      QStringList variables;
      variables.append(ejemplo.split("|"));
      this->peticion= variables[0].split(" ")[0].toInt();
      this->type= variables[1];
      this->valor= variables[2];
      this->nombre= variables[3];

}

Malloc::Malloc()
{

}
void Malloc::Principal(){
    int peticiones;
    struct tipo *blockmemory;
    int space_M; //Numeros de bytes,
    QString ejemplo = "1|long|5|num";
    Dividir(ejemplo);
    peticiones = this->peticion;
    space_M= 10;
    blockmemory =(tipo*) malloc(space_M * sizeof(tipo)); //es el type-cast


    switch (peticiones){
        case 1: //Asignar
            if(space_M==0){
                    cout << "Memoria no asignada"<< endl;
                }
            else if (space_M !=0) {
                int offset=0;
                int referencia = 1 ;
                if(type == "int"){
                    int valorint = valor.toInt();
                    QString re = QString::number(referencia);
                    (blockmemory+offset)->entero  = valorint;
                    QString p_memi = QString::fromUtf16((const char16_t *)(&(blockmemory+offset)->entero));
                    this->v_asignadas.append( p_memi + "|" + valor + "|" + this->nombre+ "|"+ re);
                    this->v_A.append( valor + "|" + this->nombre + "|" + offset);
                    qDebug() << v_asignadas<<endl;
                    printf("%p",&(blockmemory+offset)->entero);
                    printf("\n");
                    printf("%i",(blockmemory+offset)->entero);
                    printf("\n");
                    referencia ++;
                    offset++;
                }
                else if(type == "float"){
                    float valorflo = valor.toFloat();
                    QString re = QString::number(referencia);
                    (blockmemory+offset)->flotante  = valorflo;
                    QString p_memf = QString::fromUtf16((const char16_t*)(&(blockmemory+offset)->flotante));
                    this->v_asignadas.append( p_memf + "|" + valor+ "|" + this->nombre+ "|"+ re);
                    this->v_A.append( valor + "|" + this->nombre + "|" + offset);
                    qDebug() << v_asignadas<<endl;
                    printf("%p",&(blockmemory+offset)->flotante);
                    printf("\n");
                    printf("%5.2f",(blockmemory+offset)->flotante);
                    referencia ++;
                    offset++;
                }
                else if (type =="double") {
                    double valordo = valor.toDouble();
                    QString re = QString::number(referencia);
                    (blockmemory+offset)->doble  = valordo;
                    QString p_memd = QString::fromUtf16((ushort *)(&(blockmemory+offset)->doble));
                    this->v_asignadas.append( p_memd + "|" + valor+ "|" + this->nombre+ "|"+ re);
                    this->v_A.append( valor + "|" + this->nombre + "|" + offset);
                    qDebug() << v_asignadas<<endl;
                    printf("%p",&(blockmemory+offset)->doble);
                    printf("\n");
                    printf("%5.2f",(blockmemory+offset)->doble);
                    printf("\n");
                    referencia ++;
                    offset++;
                }
                else if (type =="char") {
                    //char valorch = valor.toStdString();
                    QString re = QString::number(referencia);
                    strcpy((blockmemory+offset)->cadena, "hola");
                    QString p_memc = QString::fromUtf16((ushort *)(&(blockmemory+offset)->cadena));
                    this->v_asignadas.append( p_memc + "|" + valor+ "|" + this->nombre+ "|"+ re);
                    this->v_A.append( valor + "|" + this->nombre + "|" + offset);
                    qDebug() << v_asignadas<<endl;
                    printf("%p",&(blockmemory+offset)->cadena);
                    printf("\n");
                    printf("%s",(blockmemory+offset)->cadena);
                    printf("\n");
                    referencia ++;
                    offset++;
                }
                else if (type =="long") {
                    long valorlo = valor.toLong();
                    cout << valorlo << endl;
                    QString re = QString::number(referencia);
                    (blockmemory+offset)->longer  = valorlo;
                    QString p_meml = QString::fromUtf16((ushort *)(&(blockmemory+offset)->longer));
                    this->v_asignadas.append( p_meml + "|" + valor+ "|" + this->nombre+ "|"+ re);
                    this->v_A.append( valor + "|" + this->nombre + "|" + offset);
                    qDebug() << v_asignadas<<endl;
                    printf("%p",&(blockmemory+offset)->longer);
                    printf("\n");
                    printf("%i",(blockmemory+offset)->longer);
                    printf("\n");
                    referencia ++;
                    offset++;
                }
            }
                break;
            case 2://  cambiar
                break;
            case 3:// Consultar
                break;
        }

}


