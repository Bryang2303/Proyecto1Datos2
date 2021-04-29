#ifndef MALLOC_H
#define MALLOC_H
#include <QString>
/**
 * @brief The Malloc class La Clase encargada del control de la memoria por parte del servidor
 */
class Malloc
{
public:
    /**
     * @brief peticion La peticion
     */
    int peticion;
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
     * @brief v_asignadas La variable asignada
     */
    QString v_asignadas;
    /**
     * @brief v_A Variables asignadas anteriormente
     */
    QString v_A;

    /**
     * @brief Malloc El constructor de la clase
     */
    Malloc();
    /**
     * @brief Principal Donde se realiza todo el reconocimiento de los valores
     */
    void Principal();
    /**
     * @brief Dividir Divide el mensaje que ha sido enviado por el cliente
     * @param ejemplo Ejemplo del mensaje dividido
     */
    void Dividir(QString ejemplo);
};

#endif // MALLOC_H
