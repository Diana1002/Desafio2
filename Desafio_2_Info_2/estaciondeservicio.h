#ifndef ESTACIONDESERVICIO_H
#define ESTACIONDESERVICIO_H

#include <iostream>
#include <fstream>

using namespace std;

class EstacionDeServicio
{
public:
    //Métodos
    EstacionDeServicio();
    void leerArchivo(short int id, string& nomArchivo);
    //Métodos get
    string getNombre() const;
    string getGerente() const;
    string getRegion() const;
    short getIdentificador() const;
    const float* getUbicacionGPS() const;
    const int* getTanqueCentral() const;

private:
    //Atributos
    string nombre, gerente, region;
    short int identificador;
    float ubicacionGPS[2];
    int tanqueCentral[3];

    short int convertirAEntero(const string& str);
    float convertirAFloat(const string& str);
};

#endif // ESTACIONDESERVICIO_H
