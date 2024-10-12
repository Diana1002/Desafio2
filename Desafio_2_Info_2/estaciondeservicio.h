#ifndef ESTACIONDESERVICIO_H
#define ESTACIONDESERVICIO_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class EstacionDeServicio
{
public:
    EstacionDeServicio();
    short int* crearSurtidor(short int nEstacion);

    short getIdentificador() const;
    void setIdentificador(short newIdentificador);

private:
    int tanqueCentral[3];
    short int identificador;
    string modelosMaquina[5] = {"MS-1","MS-2","MS-3","MS-4","MS-5"};

};

#endif // ESTACIONDESERVICIO_H
