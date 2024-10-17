#ifndef REDESTACIONES_H
#define REDESTACIONES_H
#include "estaciondeservicio.h"
#include <iostream>
#include <fstream>

using namespace std;

class RedEstaciones
{
public:
    RedEstaciones();
    //ATRIBUTOS PUBLICOS
    int litrosVendidoR;
    int litrosVendidoP;
    int litrosVendidoE;
    EstacionDeServicio* Estaciones[35];
    //METODOS PUBLICOS
    void abrirBaseDatos();
    void crearEstacion();
    void cargarRed(string path);
    void eliminarEstacion(short int identificador);
    void calcularMontoTotalPorCategoria();
    void guardarBaseDatos(string path);
    short int convertirAEntero(const string& str);
    void liberarMemoria();
private:
    //ATRIBUTOS PRIVADOS
    int nEstaciones = 0;
    int precioRegular;
    int precioPremium;
    int preciosEcoExtra;
    string nomArchivo;
    const int maxEstaciones = 35;
    //METODOS PRIVADOS
    void SepararString(const string& texto, const string& limitador1, const string& limitador2, string* bloques, int& cantidadBloques);
    float convertirAFloat(const string& str);
};

#endif // REDESTACIONES_H
