#ifndef REDESTACIONES_H
#define REDESTACIONES_H
#include "estaciondeservicio.h"
#include <iostream>
#include <fstream>

using namespace std;

class RedEstaciones
{
public:
    //Métodos
    RedEstaciones();
    void abrirBaseDatos();
    void crearEstacion();
    void cargarRed(string path);
    void eliminarEstacion(short int identificador);
    EstacionDeServicio* Estaciones[35];
    void calcularMontoTotalPorCategoria();
private:
    int nEstaciones = 0;
    const int maxEstaciones = 35;
    int precioRegular;
    int precioPremium;
    int preciosEcoExtra;

    string nomArchivo;
    void SepararString(const string& texto, const string& limitador1, const string& limitador2, string* bloques, int& cantidadBloques);
    short int convertirAEntero(const string& str);
    float convertirAFloat(const string& str);
};

#endif // REDESTACIONES_H
