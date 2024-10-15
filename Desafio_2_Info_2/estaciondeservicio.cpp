#include "EstacionDeServicio.h"

/**class EstacionDeservicio:
 * Representa una estación de servicio que gestiona surtidores y varios tipos de combustible.
 * Almacena información relacionada con una estación de servicio, como su nombre, gerente, ubicación y disponibilidad de combustibles.
 * También gestiona los surtidores que pertenecen a la estación.
*/

/* Constructor de la clase EstaconDeServicio:
 * Inicializa cada estacion con un surtidor único, nombre, gerente, ubicación(longitud y altitud), disponibilidad de tres tipos
 * de combustible: Regular, Premium y EcoExtra.
 * Inicializa los surtidores de cada estación
*/

/*Parametros:
 * _identificador: Código Identificador único de la estación de servicio(1-30).
 * _nombre: Nombre de la estación.
 * _gerente: Nombre del gerente de la estación.
 * _region: Región geográfica donde se encuentra la estación(Norte, Centro y Sur).
 * _longitud: Coordenada de longitud de la estación.
 * _altitud: Coordenada de altitud de la estación.
 * _Regular: Disponibilidad de combustible Regular.
 * _Premium: Disponibilidad de combustible Premium.
 * _EcoExtra: Disponibilidad de combustible EcoExtra.
*/
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

/** crearSurtidor: Crea y añade un surtidor a la estación de servicio.
 * Añade un nuevo surtidor a la estación, basado en un código identificador y el modelo del surtidor.
 * La estación tiene un límite de surtidores(12), por lo que una vez alcanzado el máximo, se sobreescriben los surtidores más antiguos.
 * _codigoID: Código identificador del surtidor.
 * _modelo: Modelo del surtidor.
 */

void EstacionDeServicio::crearSurtidor(short _codigoID, string _modelo)
{
    Surtidores[nSurtidores++] = new Surtidor(_codigoID, _modelo);
    nSurtidores %= maxSurtidores;
}
/**
*/
void EstacionDeServicio::eliminarSurtidor(short codigoID) {
    bool surtidorEliminado = false;

    // Buscar el surtidor con el identificador dado
    for (int i = 0; i < nSurtidores; ++i) {
        if (Surtidores[i] && Surtidores[i]->codigoID == codigoID) {
            // Liberar la memoria del surtidor encontrado
            delete Surtidores[i];
            surtidorEliminado = true;

            // Mover los surtidores restantes una posición hacia atrás
            for (int j = i; j < nSurtidores - 1; ++j) {
                Surtidores[j] = Surtidores[j + 1];
            }

            // La última posición se marca como nullptr
            Surtidores[nSurtidores - 1] = nullptr;
            nSurtidores--;  // Reducir el número total de surtidores

            cout << "Surtidor con codigo " << codigoID << " eliminado y reorganizado." << endl;
            return;
        }
    }
    if (!surtidorEliminado) {
        cout << "No se encontró ningún surtidor con el código " << codigoID << "." << endl;
    }
}

//Devuelve el identificador de la estación. Retorna Identificador de la estación.
short EstacionDeServicio::getIdentificador() const
{
    return identificador;
}
//Asirna un nuevo identificador a la estación. newIdentidicador es el nuevo identificador para la estación
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
