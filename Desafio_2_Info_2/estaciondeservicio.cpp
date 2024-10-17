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
EstacionDeServicio::EstacionDeServicio(short _identificador, string _nombre, string _gerente, string _region, string _longitud, string _latitud, short _Regular, short _Premium, short _EcoExtra)
{
    identificador = _identificador;
    nombre = _nombre;
    gerente = _gerente;
    region = _region;
    longitud = _longitud;
    latitud = _latitud;
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

void EstacionDeServicio::crearSurtidor(short int _codigoID, string _modelo, bool _estado)
{
    Surtidores[nSurtidores++] = new Surtidor(_codigoID, _modelo, _estado);
    nSurtidores %= maxSurtidores;
}
/**
 * eliminarSurtidor: Eliminar un surtidor de la estación de servicio basado en su código ID.
 *
 * Este método busca el surtidor con el código ID proporcionado, lo elimina y reorganiza
 * el arreglo de surtidores, desplazando todos los elementos subsiguientes una posición
 * hacia atrás. Si no se encuentra el surtidor, imprime un mensaje indicándolo.
 *
 * codigoID: Código identificador del surtidor que se desea eliminar.
 */
void EstacionDeServicio::eliminarSurtidor(short codigoID) {
    bool surtidorEliminado = false;

    // Buscar el surtidor con el identificador dado
    for (int i = 0; i < nSurtidores; ++i) {
        if (Surtidores[i] && Surtidores[i]->codigoID == codigoID) {
            // Liberar la memoria del surtidor encontrado
            //delete Surtidores[i];
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

/**
 * activarDesactivarSurtidor: Activa o desactiva un surtidor basado en su código ID.
 * Busca el surtidor con el código ID proporcionado y cambia su estado de activo
 * a inactivo o viceversa. Si no se encuentra el surtidor, imprime un mensaje indicándolo.
 *
 * codigoID: Código identificador del surtidor que se desea activar/desactivar.
 */

void EstacionDeServicio::activarDesactivarSurtidor(short codigoID) {
    for (Surtidor *&ptr : Surtidores) {  // Iteramos sobre el arreglo de punteros a Surtidor

        if (ptr != nullptr && ptr->codigoID == codigoID) {  // Verificamos que el puntero no sea nulo y que coincida el ID

            ptr->estado = !ptr->estado;  // Invertir el estado del surtidor
            cout << "Surtidor con código " << codigoID << " ha sido "
                 << (ptr->estado ? "activado." : "desactivado.") << endl;
            return;
        }
    }
    cout << "No se encontró ningún surtidor con el código " << codigoID << "." << endl;
}
/**
 * verificarCapacidades: Verifica si hay suficiente combustible disponible en una categoría específica.
 *
 * Verifica si la cantidad solicitada de combustible en una categoría específica
 * está disponible en la estación de servicio. Imprime un mensaje si la cantidad solicitada
 * excede la capacidad disponible o si la categoría de combustible no es válida.
 *
 * categoria: Nombre de la categoría de combustible ("Regular", "Premium", "EcoExtra").
 * cantidad: Cantidad de combustible solicitada.
 * Retorna true: Si la cantidad solicitada está disponible.
 * Retorna false: Si no hay suficiente combustible disponible.
 */

bool EstacionDeServicio::verificarCapacidades(string categoria, int cantidad) {
    if (categoria == "Regular") {
        if (cantidad > Regular) {
            cout << "No hay suficiente combustible Regular disponible." << endl;
            return false;
        }
    } else if (categoria == "Premium") {
        if (cantidad > Premium) {
            cout << "No hay suficiente combustible Premium disponible." << endl;
            return false;
        }
    } else if (categoria == "EcoExtra") {
        if (cantidad > EcoExtra) {
            cout << "No hay suficiente combustible EcoExtra disponible." << endl;

            return false;
        }
    } else {
        cout << "Categoría de combustible no válida." << endl;
        return false;
    }
    return true; // La cantidad está disponible
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
string EstacionDeServicio::getLongitud() const
{
    return longitud;
}
void EstacionDeServicio::setLongitud(string newLongitud)
{
    longitud = newLongitud;
}
string EstacionDeServicio::getLatitud() const
{
    return latitud;
}
void EstacionDeServicio::setLatitud(string newLatitud)
{
    latitud = newLatitud;
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
