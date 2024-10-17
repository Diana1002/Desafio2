#include "surtidor.h"
#include <iostream>


using namespace std;

/*@class Surtidor:
 * Representa un surtidor de gasolina que registra las ventas realizadas por un
 * surtidor de gasolina. Cada venta incluye información sobre la fecha, la hora,
 * cantidad de combustible, categoria, método de pago, cédula del cliente y dinero
 * a pagar
*/

/**Parametros:
 * El constructor de la clase Surtidor: Inicializa con;
 * Codigo ID(1-12) con el que se
 * cada surtidor
 * Modelo de este(MX-(1-3),(MY-(1-3),(MZ-(1-3)). Y asegura que el registro de ventas esté
 * vacío al incio
*/

Surtidor::Surtidor(short int _codigoID, string _modelo, bool _estado) {
    codigoID = _codigoID;
    modelo = _modelo;
    estado = _estado;
    intRegistro = 0;
    for (string*&ptr:registroVentas){
        ptr = nullptr;

    }
}

/*Vender: Registra una nueva venta en el surtidor
 * ALmacena una nueva venta en el registro, para esto necesita, fecha, hora,
 * cantidad, categoria de combustible, método de pago, cédula del cielte
 * y dinero. El registro tiene un limite de ventas, por lo que se sobreescribe
 * la venta más antigua cuando el limite se alcanza.
*/
/**Parametros:
 * fecha: Fecha de la venta (Formato sugerido: DD/MM)
 * hora: Hora de la venta (formato sugerido: hh:mm)
 * cantidad: Cantidad de comustible en litros
 * categoria: Categoria del combustible ej: Regular, Premium, EcoExtra
 * metPago: Método de pago: Efectivo, TDebito, TCrédito
 * cedula: Cédula del cliente
 * dinero:Monto de dinero recibido
*/
void Surtidor::Vender(string id, string fecha, string hora, string cantidad, string categoria, string metPago, string cedula, string dinero)
{
    string venta = id + "," + fecha + "," + hora + "," + cantidad + "," + categoria + "," + metPago + "," + cedula + "," + dinero;
    registroVentas[intRegistro] = new string(venta);
    intRegistro = (intRegistro + 1) % maxVentas; // Actualiza el índice
}
