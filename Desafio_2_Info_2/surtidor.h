#ifndef SURTIDOR_H
#define SURTIDOR_H

#include <string>


using namespace std;
class Surtidor
{
public:
    //Constructor
    Surtidor(short int _codigoID, string _modelo, bool estado);
    //Atributos
    bool estado;
    int intRegistro =0; //Numero de ventas que se pueden hacer por surtidor
    const int maxVentas = 5;//Si modifico este modifico el tamaño de *registro ventas
    short int codigoID;
    string* registroVentas[5];
    string modelo;
    //Métodos
    void Vender(string vender,string fecha, string hora, string cantidad, string categoria, string metPago, string cedula, string dinero);
    void desactivar();
    void activar();
};

#endif // SURTIDOR_H
