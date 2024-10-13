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

private:
    //EstacionDeServicio Estaciones;
    string nomArchivo;
    short int convertirAEntero(const string& str);
    float convertirAFloat(const string& str);
};

#endif // REDESTACIONES_H
