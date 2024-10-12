#ifndef REDESTACIONES_H
#define REDESTACIONES_H

#include <iostream>
#include <fstream>

using namespace std;

class RedEstaciones
{
public:
    //Métodos
    RedEstaciones();
    void abrirBaseDatos(short int id);
    void crearEstacion();
    //Métodos get
    string getNombre() const;
    string getGerente() const;
    string getRegion() const;
    short getIdentificador() const;
    const float* getUbicacionGPS() const;
    const int* getTanqueCentral() const;

    string getNomArchivo() const;
    void setNomArchivo(const string &newNomArchivo);

    void setIdentificador(short newIdentificador);

    void setNombre(const string &newNombre);

private:
    //Atributos
    string nombre, gerente, region;
    short int identificador;
    float ubicacionGPS[2];
    int tanqueCentral[3];

    string nomArchivo = "C:\\Users\\Asus\\Documents\\DIANA BAEZA RUIZ\\SEMESTRE 2024-2\\Desafio2\\BaseDeDatos.txt";

    short int convertirAEntero(const string& str);
    float convertirAFloat(const string& str);
};

#endif // REDESTACIONES_H
