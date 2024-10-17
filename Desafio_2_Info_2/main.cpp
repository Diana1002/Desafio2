#include <QCoreApplication>
#include <iostream>
#include "RedEstaciones.h"
using namespace std;

void mostrarMenu() {
    cout << "\n===== Menu de Red de Estaciones de Servicio =====" << endl;
    cout << "1. Cargar Red desde archivo" << endl;
    cout << "2. Crear nueva estacion" << endl;
    cout << "3. Eliminar estacion" << endl;
    cout << "4. Crear surtidor en estacion" << endl;
    cout << "5. Eliminar surtidor de estacion" << endl;
    cout << "6. Activar/Desactivar surtidor" << endl;
    cout << "7. Registrar venta en surtidor" << endl;
    cout << "8. Calcular monto total de ventas por categoria de combustible" << endl;  // Nueva opción
    cout << "9. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    RedEstaciones redEstaciones;  // Crear instancia de RedEstaciones
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        cin.ignore();  // Limpiar el buffer de entrada para getline

        switch (opcion) {
            case 1: {
                string path;
                cout << "Ingrese la ruta del archivo para cargar la red de estaciones: ";
                getline(cin, path);
                redEstaciones.cargarRed(path);
                cout << "Red de estaciones cargada correctamente." << endl;
                break;
            }
            case 2: {
                redEstaciones.crearEstacion();
                break;
            }
            case 3: {
                short int idEstacion;
                cout << "Ingrese el identificador de la estacion a eliminar: ";
                cin >> idEstacion;
                redEstaciones.eliminarEstacion(idEstacion);
                break;
            }
            case 4: {  // Crear surtidor en estación
                short int idEstacion, codigoID;
                string modelo;
                bool estado;
                cout << "Ingrese el identificador de la estacion: ";
                cin >> idEstacion;
                idEstacion--;
                cout << "Ingrese el código del surtidor: ";
                cin >> codigoID;
                cout << "Ingrese el modelo del surtidor: ";
                cin.ignore();  // Limpiar el buffer
                getline(cin, modelo);
                cout << "Ingrese el estado del surtidor (1: Activo, 0: Inactivo): ";
                cin >> estado;
                // Llama al método para crear el surtidor
                // Necesitas implementar la lógica para acceder a la estación y crear el surtidor
                redEstaciones.Estaciones[idEstacion]->crearSurtidor(codigoID, modelo, estado);
                cout << "Surtidor creado correctamente." << endl;
                break;
            }
            case 5: {  // Eliminar surtidor de estación
                short int idEstacion, codigoID;
                cout << "Ingrese el identificador de la estacion: ";
                cin >> idEstacion;
                idEstacion--;
                cout << "Ingrese el codigo del surtidor a eliminar: ";
                cin >> codigoID;
                // Llama al método para eliminar el surtidor
                // Necesitas implementar la lógica para acceder a la estación y eliminar el surtidor
                redEstaciones.Estaciones[idEstacion]->eliminarSurtidor(codigoID);
                cout << "Surtidor eliminado correctamente." << endl;
                break;
            }
            case 6: {  // Activar/Desactivar surtidor
                short int idEstacion, codigoID;
                cout << "Ingrese el identificador de la estación: ";
                cin >> idEstacion;
                idEstacion-=1;
                cout << "Ingrese el codigo del surtidor a activar/desactivar: ";
                cin >> codigoID;

                redEstaciones.Estaciones[idEstacion]->activarDesactivarSurtidor(codigoID);

                break;
            }
            case 7: {  // Registrar venta en surtidor
                short int idEstacion, codigoID;
                string fecha, hora, cantidad, categoria, metPago, cedula, dinero;

                cout << "Ingrese el identificador de la estación (1-35): ";
                cin >> idEstacion;
                idEstacion-=1;
                if (idEstacion <=0 || idEstacion >= 34) {
                    cout << "Identificador de estación no válido. Debe estar entre 1 y 35." << endl;
                }

                cout << "Ingrese el código del surtidor (1-12): ";
                cin >> codigoID;
                codigoID-=1;
                if (codigoID <=0 || codigoID >=11) {
                    cout << "Código de surtidor no válido. Debe estar entre 1 y 12." << endl;
                }

                cin.ignore();  // Limpiar el buffer de entrada
                cout << "Ingrese la fecha de la venta (DD/MM): ";
                getline(cin, fecha);
                cout << "Ingrese la hora de la venta (hh:mm): ";
                getline(cin, hora);
                cout << "Ingrese la cantidad de combustible (en litros): ";
                getline(cin, cantidad);
                cout << "Ingrese la categoría de combustible: ";
                getline(cin, categoria);
                cout << "Ingrese el método de pago: ";
                getline(cin, metPago);
                cout << "Ingrese la cédula del cliente: ";
                getline(cin, cedula);
                cout << "Ingrese el monto de dinero recibido: ";
                getline(cin, dinero);

                // Llama al método para registrar la venta
                redEstaciones.Estaciones[idEstacion]->Surtidores[codigoID]->Vender(to_string(codigoID), fecha, hora, cantidad, categoria, metPago, cedula, dinero);
                cout << "Venta registrada correctamente." << endl;
                break;
            }
            case 8: {  // Calcular el monto total de ventas por categoría de combustible
                redEstaciones.calcularMontoTotalPorCategoria();
                break;
            }
            case 9: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default: {
                cout << "Opcion no valida. Por favor, intente de nuevo." << endl;
                break;
            }

        }
        } while (opcion != 9);

    return 0;
}
