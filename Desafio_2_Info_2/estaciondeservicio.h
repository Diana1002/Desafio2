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
    //Constructor
    EstacionDeServicio(short int _identificador, string _nombre, string _gerente, string _region, string _longitud, string _altitud, short int _Regular, short int _Premium, short int _EcoExtra);
    //ATRIBUTOS
    int nSurtidores = 0;
    const int maxSurtidores = 12;
    Surtidor* Surtidores[12];
    bool estado;
    string nombre;
    string gerente;
    string region;
    string longitud;
    string latitud;
    short int Regular;
    short int Premium;
    short int EcoExtra;
    short int identificador;
    //METODOS
    void crearSurtidor(short int _codigoID, string _modelo, bool _estado);
    void eliminarSurtidor(short codigoID);
    void activarDesactivarSurtidor(short codigoID);
    bool verificarCapacidades(string categoria, int cantidad);

    short getIdentificador() const;
    void setIdentificador(short newIdentificador);
    string getNombre() const;
    void setNombre(const string &newNombre);
    string getGerente() const;
    void setGerente(const string &newGerente);
    string getRegion() const;
    void setRegion(const string &newRegion);
    string getLongitud() const;
    void setLongitud(string newLongitud);
    string getLatitud() const;
    void setLatitud(string newLatitud);
    short getRegular() const;
    void setRegular(short newRegular);
    short getPremium() const;
    void setPremium(short newPremium);
    short getEcoExtra() const;
    void setEcoExtra(short newEcoExtra);
};

#endif // ESTACIONDESERVICIO_H
