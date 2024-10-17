#ifndef SURTIDOR_H
#define SURTIDOR_H

#include <string>


using namespace std;
class Surtidor
{
public:
    Surtidor(short int _codigoID, string _modelo, bool estado);
    short int codigoID;
    string modelo;
    bool estado;

    const int maxVentas = 5;//Si modifico este modifico el tamaño de *registro ventas
    int intRegistro =0; //Numero de ventas que se pueden hacer por surtidor
    string* registroVentas[5];


    void Vender(string vender,string fecha, string hora, string cantidad, string categoria, string metPago, string cedula, string dinero);
    void desactivar();
    void activar();
};

#endif // SURTIDOR_H
