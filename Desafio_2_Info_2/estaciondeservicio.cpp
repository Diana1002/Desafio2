#include "EstacionDeServicio.h"

EstacionDeServicio::EstacionDeServicio() {}


short int* EstacionDeServicio::crearSurtidor(short int nEstacion){
    srand(static_cast<unsigned int>(time(0)));

    short int* Surtidor = new short int[6];

    short int identificador = rand() % 13;
    short int modelo = rand() % 6;

    Surtidor[0] = nEstacion;     // Número de estación
    Surtidor[1] = identificador; // Identificador del surtidor
    Surtidor[2] = modelo;        // Modelo del surtidor
    Surtidor[3] = 0;             // Otros valores (puedes cambiar según tu lógica)
    Surtidor[4] = 0;
    Surtidor[5] = 0;


    return Surtidor; // Retorna el puntero al arreglo
}

short EstacionDeServicio::getIdentificador() const
{
    return identificador;
}

void EstacionDeServicio::setIdentificador(short newIdentificador)
{
    identificador = newIdentificador;
}


