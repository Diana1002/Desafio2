#include "EstacionDeServicio.h"

EstacionDeServicio::EstacionDeServicio(short _identificador, string _nombre, string _gerente, string _region, float _longitud, float _altitud, short _Regular, short _Premium, short _EcoExtra)
{
    identificador = _identificador;
    nombre = _nombre;
    gerente = _gerente;
    region = _region;
    longitud = _longitud;
    altitud = _altitud;
    Regular = _Regular;
    Premium = _Premium;
    EcoExtra = _EcoExtra;
    for (Surtidor*&ptr:Surtidores){
        ptr = nullptr;

    }
}

void EstacionDeServicio::crearSurtidor(short _codigoID, string _modelo)
{

    Surtidores[nSurtidores++] = new Surtidor(_codigoID, _modelo);
    nSurtidores %= maxSurtidores;
}


short EstacionDeServicio::getIdentificador() const
{
    return identificador;
}

void EstacionDeServicio::setIdentificador(short newIdentificador)
{
    identificador = newIdentificador;
}

string EstacionDeServicio::getNombre() const
{
    return nombre;
}

void EstacionDeServicio::setNombre(const string &newNombre)
{
    nombre = newNombre;
}

string EstacionDeServicio::getGerente() const
{
    return gerente;
}

void EstacionDeServicio::setGerente(const string &newGerente)
{
    gerente = newGerente;
}

string EstacionDeServicio::getRegion() const
{
    return region;
}

void EstacionDeServicio::setRegion(const string &newRegion)
{
    region = newRegion;
}

float EstacionDeServicio::getLongitud() const
{
    return longitud;
}

void EstacionDeServicio::setLongitud(float newLongitud)
{
    longitud = newLongitud;
}

float EstacionDeServicio::getAltitud() const
{
    return altitud;
}

void EstacionDeServicio::setAltitud(float newAltitud)
{
    altitud = newAltitud;
}

short EstacionDeServicio::getRegular() const
{
    return Regular;
}

void EstacionDeServicio::setRegular(short newRegular)
{
    Regular = newRegular;
}

short EstacionDeServicio::getPremium() const
{
    return Premium;
}

void EstacionDeServicio::setPremium(short newPremium)
{
    Premium = newPremium;
}

short EstacionDeServicio::getEcoExtra() const
{
    return EcoExtra;
}

void EstacionDeServicio::setEcoExtra(short newEcoExtra)
{
    EcoExtra = newEcoExtra;
}


