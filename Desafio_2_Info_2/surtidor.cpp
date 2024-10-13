#include "surtidor.h"

Surtidor::Surtidor(short int _codigoID, string _modelo) {
    codigoID = _codigoID;
    modelo = _modelo;
    intRegistro = 0;
    for (string*&ptr:registroVentas){
        ptr = nullptr;

    }
}

void Surtidor::Vender(string fecha, string hora, string cantidad, string categoria, string metPago, string cedula, string dinero)
{

    string venta = fecha+","+hora+","+cantidad+","+categoria+","+metPago+","+cedula+","+dinero;
    registroVentas[intRegistro] = new string(venta);

    intRegistro += 1;
    intRegistro %= maxVentas;//Cuando el maximo de ventas es 5 se reinicia a la posicion 0

}

