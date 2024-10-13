#ifndef ESTACIONDESERVICIO_H
#define ESTACIONDESERVICIO_H
#include "surtidor.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class EstacionDeServicio
{
public:
    EstacionDeServicio(short int _identificador, string _nombre, string _gerente, string _region, float _longitud, float _altitud, short int _Regular, short int _Premium, short int _EcoExtra);
    int nSurtidores = 0;
    const int maxSurtidores = 12;
    Surtidor* Surtidores[12];

    void crearSurtidor(short int _codigoID, string _modelo);

    short getIdentificador() const;
    void setIdentificador(short newIdentificador);
    string getNombre() const;
    void setNombre(const string &newNombre);
    string getGerente() const;
    void setGerente(const string &newGerente);
    string getRegion() const;
    void setRegion(const string &newRegion);
    float getLongitud() const;
    void setLongitud(float newLongitud);
    float getAltitud() const;
    void setAltitud(float newAltitud);
    short getRegular() const;
    void setRegular(short newRegular);
    short getPremium() const;
    void setPremium(short newPremium);
    short getEcoExtra() const;
    void setEcoExtra(short newEcoExtra);

private:

    short int identificador;
    string nombre;
    string gerente;
    string region;
    float longitud;
    float altitud;
    short int Regular;
    short int Premium;
    short int EcoExtra;
};

#endif // ESTACIONDESERVICIO_H
