#ifndef MALLOC_H
#define MALLOC_H
#include <QString>
#include <QStringList>
#include <iostream>
using namespace std;
/**
 * @brief The Malloc class La Clase encargada del control de la memoria por parte del servidor
 */
class Malloc
{
public:
    /**
     * @brief peticion La peticion
     */
    QString peticion;
    /**
     * @brief type El tipo de la variable
     */
    QString type;
    /**
     * @brief valor El valor de la variable
     */
    QString valor;
    /**
     * @brief nombre El nombre de la variable
     */
    QString nombre;
    /**
     * @brief v_asignada La variable asignada formato RAM VIEW
     */
    struct tipo *blockmemory;
    QStringList v_asignada;
    QStringList v_YA;
    /**
     * @brief memoryspace Variable que cumple el papel de offset para recorrer la memoria para obtener una posición
     */
    QString memoryspace;
    /**
     * @brief referencia Variable que indica la referencia de la variable
     */
    QString referencia;
    /**
     * @brief first Variables booleana que indica si se esta corriendo por primera ves o no
     */
    bool first = true;

    /**
     * @brief Malloc El constructor de la clase
     */
    Malloc();
    /**
     * @brief Principal Donde se realiza todo el reconocimiento de los valores
     */
    void Principal();
    /**
     * @brief CreateJsonServerFile Crea el archivo .json con la respuesta del servidor
     */
    void CreateJsonServerFile();
    /**
     * @brief WriteJsonServerEscribe el archivo .json con la respuesta del servidor
     */
    void WriteJsonServer();
    /**
     * @brief LeerJson Lee el archivo .json que envia el ciente
     */
    void LeerJson();
    /**
     * @brief Memoria Muestra la posición de memoria  de una variable
     * @param offset posicion en el bloque de memoria que se encuentra una variable
     */
    struct tipo* Memoria(int offset);
    /**
     * @brief getV_asignada return a la lista que se utilizar en la RAMVIEWLIVE
     */
    QStringList getV_asignada();
};

#endif // MALLOC_H
