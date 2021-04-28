#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include "socketcliente.h"
#include <json.h>
namespace Ui {

class Widget;
}
/**
 * @brief The Widget class La clase que maneja todo lo relacionado con la Interfaz Grafica, asi como las operaciones dentro de la misma.
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Widget : El constructor de la interfaz
     */
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    /**
     * @brief scope Permite diferenciar el scope global de otro
     */
    bool scope = false;
    /**
     * @brief contScope Un contador de cada scope definido
     */
    int contScope = 0;
    /**
     * @brief variables Lista de todas las variables asignadas, con su respectivo valor, tipo y scope en el que se encuentra
     */
    QStringList variables;
    QList<int> scopes = {0};
    /**
     * @brief alreadyIs Permite saber si una variable existe o no
     */
    bool alreadyIs = false;
    /**
     * @brief pos La posicion (linea de codigo) que se esta ejecutando
     */
    int pos = 1;
    /**
     * @brief fecha Donde se almacena la fecha con su repectivo formato
     */
    char fecha[25];//ctime devuelve 26 caracteres pero tambien se podría usar un puntero de char
    /**
     * @brief current_time La hora actual
     */
    time_t current_time;
    /**
     * @brief J El json que se utiliza
     */
    Json J;

    //QString convert(auto);
    /**
     * @brief date Para la obtencion de la fecha que se muestra en los Logs
     */
    void date();
    /**
     * @brief log Permite mostrar en pantalla los Logs
     * @param T tipo de aviso
     * @param msgL mensaje de aviso
     */
    void log(QString T, QString msgL);
    /**
     * @brief IsOrNot Permite saber si la variable que se va a declarar, ya ha sido declarado antes o no
     * @param n Nombre de la variable a buscar
     * @param t Tipo de la variable a buscar
     */
    void IsOrNot(QString n, QString t);
    /**
     * @brief Solve2 Permite retornar el resultado de tipo auto de una operacion especifica entre dos valores.
     * @param uno Primer valor a operar
     * @param dos Segundo valor a operar
     * @param tres La operacion a realizar. 1.Suma, 2.Resta, 3.Multiplicacion, 4. Division
     */
    auto Solve2(auto uno, auto dos, auto tres);
    /**
     * @brief searchInScope Permite obtener el valor de una variable ya existente. Si no existe, retorna una negacion.
     * @param n Nombre de la variable a buscar
     * @param t Tipo de la variable a buscar
     * @param scp Scope en el que se encuentra la variable
     * @return El valor de la variable buscada, en formato QString
     */
    QString searchInScope(QString n, QString t, QString scp);
    /**
     * @brief searchInScope2 Permite obtener el tipo de una variable ya existente. Si no existe, retorna una negacion.
     * @param n Nombre de la variable a buscar
     * @param scp Scope en el que se encuentra la variable
     * @return El tipo de la variable buscada, en formato QString
     */
    QString searchInScope2(QString n, QString scp);
    /**
     * @brief setValue Permite asignar un nuevo valor a una variable ya asignada con anterioridad
     * @param n Nombre de la variable a la que se le reasigna el valor
     * @param v Valor a asignar
     * @param t Tipo de la variable
     * @param scp Scope en el que se encuentra la variable
     */
    void setValue(QString n, auto v, QString t, QString scp);
    /**
     * @brief Solve Permite resolver una operacion especifica para numeros enteros unicamente.
     * @param first Primer entero
     * @param second Segundo entero
     * @param action Operacion a realizar. 1.Suma, 2.Resta, 3.Multiplicacion, 4. Division
     * @return El resultado de la operacion, en tipo QString
     */
    QString Solve(int first, int second, int action);
    /**
     * @brief Recon Permite reconocer cada linea de codigo introducida en el IDE de C!. La funcion avanza linea por linea, identificando cada ejecucion, cada asignacion de variable, cada reasignacion de valor, realizando cada operacion y en general cada instruccion. Lo puede realizar de manera en forma de Run o en forma de Debug.
     * @param codelines La lista de las instrucciones, donde cada elemento de la misma es una linea de codigo.
     * @param runKind El tipo de ejecucion a realizar. 0. Un unico Run que ejecuta todo el codigo 1. Ejecucion linea por linea controlada porr un contador.
     */
    void Recon(QStringList codelines, int runKind);
    /**
     * @brief sendMsg Se encarga del envio de mensajes al servidor, buscando los datos de una variable especifica para posteriormente armar el mismo mensaje como un conjunto de atributos de la variable.
     * @param n Nombre de la variable a buscar
     * @param Jaction Tipo de solicitud que realiza el Json
     */
    void sendMsg(QString n, QString Jaction);

private:
    Ui::Widget *ui;
    /**
     * @brief conexion El socket Cliente
     */
    SocketCliente *conexion;

private slots:

    /**
     * @brief on_pushButton_6_clicked Al pulsar este boton, se ejecutan todas las lineas del codigo
     */
    void on_pushButton_6_clicked();
    /**
     * @brief printMensaje Para imprimir el mensaje en la interfaz, aunque no es necesario
     * @param msn El mensaje que el CLiente recibe del Servidor
     */
    void printMensaje(QString msn);
    /**
     * @brief sendMensaje Permite el envio de un mensaje especifico, al servidor
     */
    void sendMensaje();
    /**
     * @brief on_pushButton_clicked Permite ir recoriendo y ejecutando cada instruccion, linea por linea por medio de un contador
     */
    void on_pushButton_clicked();
    /**
     * @brief on_dial_3_sliderPressed Eliminar el historial de Logs actual
     */
    void on_dial_3_sliderPressed();
    /**
     * @brief on_pushButton_2_clicked Detiene el proceso de ejecucion, reiniciando la lista de variables y el contador de recorrido de lineas. Tambien borra todas las instrucciones en el IDE.
     */
    void on_pushButton_2_clicked();
};

#endif // WIDGET_H
