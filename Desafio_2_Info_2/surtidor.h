#ifndef SURTIDOR_H
#define SURTIDOR_H

#include <string>


using namespace std;
class Surtidor
{
public:
    Surtidor(short int _codigoID, string _modelo, bool estado);
    bool estado = true;
    ~Surtidor();
    short int codigoID;
    string modelo;
    const int maxVentas = 5;//Si modifico este modifico el tamaño de *registro ventas
    int intRegistro; //Numero de ventas que se pueden hacer por surtidor
    string* registroVentas[5];
    string cantLitros;

    void Vender(string fecha, string hora, string cantidad, string categoria, string metPago, string cedula, string dinero);
};

#endif // SURTIDOR_H
