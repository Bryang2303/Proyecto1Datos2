#ifndef JSON_H
#define JSON_H
#include<QString>
/**
 * @brief The Json class Clase encagada de la integracion y manejo del archivo json
 */
class Json
{

public:
    /**
     * @brief ParseJson
     * @param posicion
     * @return
     */
    QString ParseJson(int posicion);
    Json();
};

#endif // JSON_H
