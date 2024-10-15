#include "RedEstaciones.h"
/**class RedEstaciones
 * Gestiona la red de estaciones de servicio.
 * Permite cargar los datos de estaciones de servicio desde un archivo y organizarlas, gestionando
 * los surtidores y las ventas asociadas.
 * COntiene metodos para separar cadenas de caracteres y convertir datos en diferentes formatos
*/
/**contructor de la clase estaciones
 * Inicializa la red de estaciones vacia, asegurando que todas las posiciones de las
 * estaciones estén en nullptr.
*/
RedEstaciones::RedEstaciones() {
    for (EstacionDeServicio*&ptr:Estaciones){
        ptr = nullptr;
    }
}
/** cargarRed: carga la red de estaciones de servicio desde un archivo.
 *  Establece la ruta del archivo y llama a la función que abre y procesa la base de datos.
 *  Parametro: path es la ruta del archivo de texto que contiene los datos de la red de estaciones.
*/
void RedEstaciones::cargarRed(string path)
{
    nomArchivo = path;
    abrirBaseDatos();
}
/**SepararString: Separa una cadena de texto en bloques basados en delimitadores.
 * El método divide un texto entre dos delimitadores y almacena los bloques resultantes
 * en un arreglo. Se utiliza para procesar los datos de estaciones y surtidores.
*/
/**Parametros:
 * texto: la cadena de texto que sera dividida.
 * limitador1: primer delimitador.
 * limitador2: segundo delimitador.
 * bloques: Arreglo donde se almacenarán los bloques de texto.
 * cantidadBloque: Referencia a la cantidad de bloques generados.
*/
void RedEstaciones::SepararString(const string &texto, const string &limitador1, const string &limitador2, string *bloques, int &cantidadBloques)
{
    size_t pos1 = 0, pos2 = 0;
    cantidadBloques = 0;
    size_t capacidad = 10;  // Tamaño inicial del arreglo
    bloques[0] = "";  // Inicializar el primer bloque

    while ((pos1 = texto.find(limitador1, pos2)) != string::npos) {
        pos1 += limitador1.length();  // Saltar el primer delimitador
        pos2 = texto.find(limitador2, pos1);

        if (pos2 != string::npos) {
            // Si hay espacio, extraer el bloque y guardarlo
            if (cantidadBloques >= capacidad) {
                // Si se excede la capacidad, aumentar el tamaño del arreglo
                capacidad *= 2;
            }
            bloques[cantidadBloques] = texto.substr(pos1, pos2 - pos1);  // Guardar el bloque
            cantidadBloques++;
        } else {
            break;  // Si no se encuentra el segundo delimitador, salir
        }
    }
}
/**convertirAEntero: convierte una cadena de texto en un entero corto
 * Toma una cadena que representa un número entero y lo convierte en un tipo 'short int'.
*/
/*Parametros:
 * str: cadena de texto que representa un numero.
 * resultado: el numero convertido a tipo short int
*/
short int RedEstaciones::convertirAEntero(const string& str){
    short int resultado = 0;
    for (char c:str){
        resultado = resultado*10+(c-'0');
    }return resultado;
}
/**convertirAFloat: convierte una cadena de texto en un número flotante
 * Toma una cadena que representa un número decimal y lo convierte en un tipo 'float'.
*/
/*Parametros:
 * str: cadena de texto que representa un numero.
 * resultado: el numero convertido a tipo float
*/
float RedEstaciones::convertirAFloat(const string& str){
    float resultado = 0.0;
    bool negativo = false;
    bool puntoDecimal = false;

    for (char c:str){
        if(c=='-'){
            negativo = true;
        }
        else if(c =='.'){
            puntoDecimal = true;
        }else{
            if(!puntoDecimal){
                resultado = resultado*10+(c-'0');
            }
        }
    }
    if (negativo) resultado = -resultado;
    return resultado;
}
/**abrirBaseDatos: Abre el archivo que contiene la base de datos y carga las estaciones y surtidores.
 * Procesa un archivo de texto donde cada línea contiene los datos de una estación de servicio y sus surtidores asociados.
 * Se separan los datos relevantes, se crean las estaciones y surtidores, y se registran las ventas.
 */
void RedEstaciones:: abrirBaseDatos(){

    ifstream archivo(nomArchivo);
    string linea;

    if (!archivo.is_open()){
        cerr<< "No se pudo abrir el archivo"<<endl;
        return ;
    }
    while (getline(archivo, linea)){
        const int MAX_BLOQUES = 61;  // Número máximo de bloques (1 de la info de la estacion, 12 surtidores y 5 ventas max por cada uno
        string bloques[MAX_BLOQUES];  // Arreglo de bloques
        int cantidadBloques = 0;  // Contador de bloques

        SepararString(linea, "[", "]", bloques, cantidadBloques);

        const int maxBloque1 = 9;  // Número máximo de bloques (1 de la info de la estacion, 12 surtidores y 5 ventas max por cada uno
        string bloque1[maxBloque1];  // Arreglo de bloques
        int cantBloque1 = 0;  // Contador de bloques
        SepararString(bloques[0], ",",",", bloque1, cantBloque1);

        string nomEstacion = bloque1[1], gerente = bloque1[2], region = bloque1[3];
        short int codID = convertirAEntero(bloque1[0]);
        float longitud = convertirAFloat(bloque1[4]);
        float latitud = convertirAFloat(bloque1[5]);
        short int capRegular = convertirAEntero(bloque1[6]);
        short int capPremium = convertirAEntero(bloque1[7]);
        short int capEcoExtra = convertirAEntero(bloque1[8]);


        Estaciones[nEstaciones] = new EstacionDeServicio(codID, nomEstacion, gerente, region, longitud, latitud, capRegular, capPremium, capEcoExtra);

        //Para los surtidores
        const int maxBloque2 = 24;  // Número máximo de bloques (1 de la info de la estacion, 12 surtidores y 5 ventas max por cada uno
        string bloque2[maxBloque2];  // Arreglo de bloques
        int cantBloque2 = 0;  // Contador de bloques
        SepararString(bloques[1],",",",",bloque2,cantBloque2);

        for (int i = 0; i<cantBloque2; i+=2 ){
            short codigoSurtidor = convertirAEntero(bloque2[i]);
            string modeloSurtidor = bloque2[i+1];
            Estaciones[nEstaciones]->crearSurtidor(codigoSurtidor, modeloSurtidor);
        }
        for(int i = 2; i<cantidadBloques;i++){
            string Bloquesi[9];
            int cantBloquesi = 0;
            SepararString(bloques[i],",",",",Bloquesi,cantBloquesi);
            bool encontrado = false;
            for(Surtidor*&ptr:Estaciones[nEstaciones]->Surtidores){
                if (!ptr){
                    continue;
                }
                if(ptr->codigoID == convertirAEntero(Bloquesi[0])){
                    ptr->Vender(Bloquesi[2],Bloquesi[3],Bloquesi[4],Bloquesi[5],Bloquesi[6],Bloquesi[7],Bloquesi[8]);
                    encontrado = true;
                    break;
                }
            }
            if(!encontrado){
                Estaciones[nEstaciones]->crearSurtidor(convertirAEntero(Bloquesi[0]), Bloquesi[1]);
                int posicion = Estaciones[nEstaciones]->nSurtidores;
                Estaciones[nEstaciones]->Surtidores[posicion-1]->Vender(Bloquesi[2],Bloquesi[3],Bloquesi[4],Bloquesi[5],Bloquesi[6],Bloquesi[7],Bloquesi[8]);
            }
        }
        nEstaciones++;
    }
    archivo.close();
}
void RedEstaciones::crearEstacion() {
    // Verificar si ya se alcanzó el límite de estaciones
    if (nEstaciones >= 35) {
        cout << "No se pueden crear más estaciones. Se ha alcanzado el límite de 35 estaciones." << endl;
        return;
    }

    string nombre, gerente, region;
    float longitud, latitud;
    short capacidadRegular, capacidadPremium, capacidadEcoExtra;

    // Asignar el identificador automáticamente según la posición en el arreglo
    short identificador = nEstaciones + 1; // Asignar un identificador secuencial

    // Solicitar los datos de la nueva estación
    cout << "Ingresa el nombre de la estacion: ";
    getline(cin, nombre);

    cout << "Ingresa el nombre del gerente: ";
    getline(cin, gerente);

    cout << "Ingresa la region: ";
    getline(cin, region);

    // Validar la entrada para la longitud
    cout << "Ingresa la longitud: ";
    while (true) {
        string aux;
        getline(cin, aux);
        longitud = convertirAFloat(aux); // Usamos la función convertirAFloat
        if (longitud != 0.0 || aux == "0") break; // Acepta si es un número válido o es cero
        cout << "Error: Ingresa un valor válido para la longitud." << endl;
    }

    // Validar la entrada para la latitud
    cout << "Ingresa la latitud: ";
    while (true) {
        string aux;
        getline(cin, aux);
        latitud = convertirAFloat(aux); // Usamos la función convertirAFloat
        if (latitud != 0.0 || aux == "0") break; // Acepta si es un número válido o es cero
        cout << "Error: Ingresa un valor válido para la latitud." << endl;
    }

    // Validar las capacidades de combustible (máximo 200)
    cout << "Ingresa la capacidad maxima de combustible Regular (máximo 200): ";
    while (true) {
        string aux;
        getline(cin, aux);
        capacidadRegular = convertirAEntero(aux); // Usamos la función convertirAEntero
        if (capacidadRegular >= 0 && capacidadRegular <= 200) break;
        cout << "Error: Ingresa un número válido (0-200) para la capacidad de combustible Regular." << endl;
    }

    cout << "Ingresa la capacidad maxima de combustible Premium (máximo 200): ";
    while (true) {
        string aux;
        getline(cin, aux);
        capacidadPremium = convertirAEntero(aux); // Usamos la función convertirAEntero
        if (capacidadPremium >= 0 && capacidadPremium <= 200) break;
        cout << "Error: Ingresa un número válido (0-200) para la capacidad de combustible Premium." << endl;
    }

    cout << "Ingresa la capacidad maxima de combustible EcoExtra (máximo 200): ";
    while (true) {
        string aux;
        getline(cin, aux);
        capacidadEcoExtra = convertirAEntero(aux); // Usamos la función convertirAEntero
        if (capacidadEcoExtra >= 100 && capacidadEcoExtra <= 200) break;
        cout << "Error: Ingresa un número válido (0-200) para la capacidad de combustible EcoExtra." << endl;
    }

    // Crear la nueva estación de servicio con los datos ingresados
    EstacionDeServicio* nuevaEstacion = new EstacionDeServicio(
        identificador, nombre, gerente, region, longitud, latitud,
        capacidadRegular, capacidadPremium, capacidadEcoExtra
        );

    // Agregar la nueva estación al arreglo de estaciones
    Estaciones[nEstaciones++] = nuevaEstacion;

    cout << "Estacion creada y agregada correctamente. Identificador asignado: " << identificador << endl;
}
void RedEstaciones::eliminarEstacion(short int identificador){
    bool estacionEliminada = false;
    // Buscar la estación con el identificador
    for (int i = 0; i < nEstaciones; ++i) {
        if (Estaciones[i] && Estaciones[i]->getIdentificador() == identificador) {
            // Liberar la memoria de la estación encontrada
            delete Estaciones[i];
            estacionEliminada = true;

            // Mover las estaciones siguientes una posición hacia atrás
            for (int j = i; j < nEstaciones - 1; ++j) {
                Estaciones[j] = Estaciones[j + 1];
            }

            // La última posición se marca como nullptr
            Estaciones[nEstaciones - 1] = nullptr;
            nEstaciones--;  // Reducir el número total de estaciones

            cout << "Estacion con identificador " << identificador << " eliminada y reorganizada." << endl;
            return;
        }
    }
    if (!estacionEliminada) {
        cout << "No se encontró ninguna estación con el identificador " << identificador << "." << endl;
    }
}
