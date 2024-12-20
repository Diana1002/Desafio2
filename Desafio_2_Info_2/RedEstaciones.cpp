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
/**class abrirBaseDatos: Abre el archivo que contiene la base de datos y carga las estaciones y surtidores.
 * Procesa un archivo de texto donde cada línea contiene los datos de una estación de servicio y sus surtidores asociados.
 * Se separan los datos relevantes, se crean las estaciones y surtidores, y se registran las ventas.
 */
bool ContadorLinea1=true;
void RedEstaciones:: abrirBaseDatos(){
    //Abrir el archvio de la base de datos
    ifstream archivo(nomArchivo);
    string linea;
    bool ContadorLinea1=true;
    //Verificar si el archivo pudo abrirse correctamente
    if (!archivo.is_open()){
        cerr<< "No se pudo abrir el archivo"<<endl;
        return ;
    }
    //Procesa cada linea del archvio (cada linea representa una E/S)
    while (getline(archivo, linea)){
        if(ContadorLinea1==true){
            int maxBLinea0 =1;
            string linea0[maxBLinea0];
            string precios[3];
            int cntB=0;
            SepararString(linea,"[","]",linea0, cntB);
            cntB=0;
            SepararString(linea0[0], ",",",", precios, cntB);
            precioRegular = convertirAEntero(precios[0]);
            precioPremium = convertirAEntero(precios[1]);
            preciosEcoExtra = convertirAEntero(precios[2]);

            ContadorLinea1=false;
            continue;
        }

        const int MAX_BLOQUES = 62;  // Número máximo de bloques (1 de la info de la estacion, 12 surtidores y 5 ventas max por cada uno
        string bloques[MAX_BLOQUES];  // Arreglo que almacena los bloques de datos de la E/S
        int cantidadBloques = 0;  // Contador de bloques de datos

        SepararString(linea, "[", "]", bloques, cantidadBloques);//Separar la linea en bloques delimitador por '[,,,]'

        //Procesa el primer bloque, que contiene la información de la estación
        const int maxBloque1 = 9;  // Número de bloques para la información de la estación
        string bloque1[maxBloque1];  // Arreglo de bloques
        int cantBloque1 = 0;  // Contador de bloques de información de la estación


        SepararString(bloques[0], ",",",", bloque1, cantBloque1); //Separar los campos del primer bloque de la estación por comas(,)

        //Asigna los valores de los campos a la varriable que corresponda
        string nomEstacion = bloque1[1], gerente = bloque1[2], region = bloque1[3];
        short int codID = convertirAEntero(bloque1[0]);
        string longitud = bloque1[4];
        string latitud = bloque1[5];
        short int capRegular = convertirAEntero(bloque1[6]);
        short int capPremium = convertirAEntero(bloque1[7]);
        short int capEcoExtra = convertirAEntero(bloque1[8]);

        //Crea una nueva estacion de servicio y la agrega a la lista de estaciones
        Estaciones[nEstaciones] = new EstacionDeServicio(codID, nomEstacion, gerente, region, longitud, latitud, capRegular, capPremium, capEcoExtra);

        //Para los surtidores
        //Se procesa el segundo bloque, que contiene la información de los surtidores
        const int maxBloque2 = 24;  // Número máximo de bloques para la información de los surtidores
        string bloque2[maxBloque2];  // Arreglo para los campos de los surtidores
        int cantBloque2 = 0;  // Contador de bloques de los surtidores

        SepararString(bloques[1],",",",",bloque2,cantBloque2);//Separar los campos de los surtidores por comas (,)
        //Crear los surtidores asociados a la estación
        bool estado;
        for (int i = 0; i<cantBloque2; i+=3){
            short int codigoSurtidor = convertirAEntero(bloque2[i]);
            string modeloSurtidor = bloque2[i+1];

            if(bloque2[i+2]=="activo"){
                estado = true;
            }
            Estaciones[nEstaciones]->crearSurtidor(codigoSurtidor, modeloSurtidor, estado);
        }
        estado = false;

        //Procesa el resto de bloques que son las ventas realizadas en los surtidores
        for(int i = 2; i<cantidadBloques;i++){
            string Bloquesi[8]; //Arreglo para los campos de cada venta
            int cantBloquesi = 0;//Contador de los campos de la venta

            //Separa los campos de la venta por comas
            SepararString(bloques[i],",",",",Bloquesi,cantBloquesi);
            bool encontrado = false;

            for(Surtidor*&ptr:Estaciones[nEstaciones]->Surtidores){//Busca el surtidor correspondiente a la venta actual
                if (!ptr){ //Si el puntero al surtidor es nulo, lo omiten es decir si el surtidor es no existe
                    continue;
                }
                //Verifica si el codigo del surtidor coincide con el de la venta
                if(ptr->codigoID == convertirAEntero(Bloquesi[0])){
                    //Realiza la venta en el surtidor encontrado
                    ptr->Vender(Bloquesi[0],Bloquesi[1],Bloquesi[2],Bloquesi[3],Bloquesi[4],Bloquesi[5],Bloquesi[6],Bloquesi[7]);
                    encontrado = true;
                    break;
                }
            }
            //Si no se encontro el surtidor, entonces lo creaa
            if(!encontrado){
                Estaciones[nEstaciones]->crearSurtidor(convertirAEntero(Bloquesi[0]), Bloquesi[1], estado);
                int posicion = Estaciones[nEstaciones]->nSurtidores;
                Estaciones[nEstaciones]->Surtidores[posicion-1]->Vender(Bloquesi[0],Bloquesi[1],Bloquesi[2],Bloquesi[3],Bloquesi[4],Bloquesi[5],Bloquesi[6],Bloquesi[7]);
            }
        }

        nEstaciones++;//Incrementa el contador de estaciones
    }
    archivo.close();//Cierra el archivo despues de procesar todas las estaciones
    return;
}
/**crearEstacion: Crea una nueva estación de servicio y la agrega al arreglo de estaciones.
 *
 * Este método verifica si se ha alcanzado el límite de estaciones permitidas (35). Si no se ha alcanzado,
 * solicita al usuario los datos de la nueva estación, valida las capacidades de combustible y la añade
 * al arreglo de estaciones.
 *
 */
void RedEstaciones::crearEstacion() {
    // Verificar si ya se alcanzó el límite de estaciones
    if (nEstaciones >= 35) {
        cout << "No se pueden crear más estaciones. Se ha alcanzado el límite de 35 estaciones." << endl;
        return;
    }

    string nombre, gerente, region, longitud, latitud;
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
    EstacionDeServicio* nuevaEstacion = new EstacionDeServicio(identificador, nombre, gerente, region, longitud, latitud, capacidadRegular, capacidadPremium, capacidadEcoExtra);

    // Agregar la nueva estación al arreglo de estaciones
    Estaciones[nEstaciones++] = nuevaEstacion;

    cout << "Estacion creada y agregada correctamente. Identificador asignado: " << identificador << endl;
}
/**
 * eliminarEstacion: Elimina una estación de servicio dado su identificador.
 *
 * Este método busca una estación de servicio usando su identificador y la elimina, reorganizando
 * el arreglo de estaciones. Antes de eliminar, verifica si la estación tiene surtidores activos
 * y, de ser así, no permite la eliminación.
 *
 * identificador: El identificador de la estación a eliminar.
 */
void RedEstaciones::eliminarEstacion(short int identificador) {
    bool estacionEliminada = false;

    // Buscar la estación con el identificador
    for (int i = 0; i < nEstaciones; ++i) {
        if (Estaciones[i] && Estaciones[i]->getIdentificador() == identificador) {

            // Verificación de surtidores activos antes de eliminar la estación
            bool tieneSurtidoresActivos = false;
            for (int j = 0; j < Estaciones[i]->nSurtidores; ++j) {
                if (Estaciones[i]->Surtidores[j] && Estaciones[i]->Surtidores[j]->estado == true) { // Asegúrate de que `estado` es la forma correcta de acceder al estado del surtidor
                    tieneSurtidoresActivos = true;
                    break;
                }
            }
            // Si hay surtidores activos, no se puede eliminar la estación
            if (tieneSurtidoresActivos) {
                cout << "No se puede eliminar la estacion porque tiene surtidores activos." << endl;
                return;
            }
            // Si no tiene surtidores activos, procede a eliminar la estación
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
        cout << "No se encontro ninguna estacion con el identificador " << identificador << "." << endl;
    }
}
/**
 * calcularMontoTotalporCategoria: Calcula el monto total de ventas por categoría de combustible.
 *
 * Este método recorre todas las estaciones de la red, accediendo a los surtidores y sus ventas
 * para calcular el monto total por cada categoría de combustible (Regular, Premium, EcoExtra).
 */
void RedEstaciones::calcularMontoTotalPorCategoria() {
    int totalRegular = 0, totalPremium = 0, totalEcoExtra = 0;
    string bloques[8];
    int cantidadBloques;

    for (EstacionDeServicio *estacion : Estaciones) {  // Recorrer todas las estaciones
        if (estacion != nullptr) {
            for (Surtidor *surtidor : estacion->Surtidores) {  // Recorrer todos los surtidores de la estación
                if (surtidor != nullptr) {
                    for (int i = 0; i < surtidor->maxVentas; i++) {  // Recorrer todas las ventas del surtidor
                        if (surtidor->registroVentas[i] != nullptr) {
                            // Separar los datos de la venta
                            SepararString(*surtidor->registroVentas[i], ",", ",", bloques, cantidadBloques);

                            // Obtener la categoría y la cantidad de litros
                            string categoria = bloques[3];  // Categoría de combustible (Regular, Premium, EcoExtra)
                            short int cantidadLitros = convertirAEntero(bloques[2]);

                            // Calcular el total según la categoría
                            if (categoria == "Regular") {
                                totalRegular += cantidadLitros * precioRegular;
                            } else if (categoria == "Premium") {
                                totalPremium += cantidadLitros * precioPremium;
                            } else if (categoria == "EcoExtra") {
                                totalEcoExtra += cantidadLitros * preciosEcoExtra;
                            }
                        }
                    }
                }
            }
        }
    }

    litrosVendidoR = totalRegular/precioRegular;
    litrosVendidoP = totalPremium/precioPremium;
    litrosVendidoE = totalEcoExtra/preciosEcoExtra;
    // Mostrar resultados
    cout << "Monto y total de ventas por categoria de combustible:" << endl;
    cout << "Regular: $" << totalRegular <<" Litros vendidos: "<<litrosVendidoR <<endl;
    cout << "Premium: $" << totalPremium <<" Litros vendidos: "<<litrosVendidoP<< endl;
    cout << "EcoExtra: $" << totalEcoExtra <<" Litros vendidos: "<<litrosVendidoE<< endl;
}
/**
 * guardarBaseDatos: Guarda la base de datos de estaciones y surtidores en un archivo.
 *
 * Este método guarda la información de las estaciones, sus surtidores y las ventas
 * realizadas en los surtidores, todo en un archivo de texto. El formato de salida
 * incluye los precios de los combustibles y los detalles de cada estación.
 *
 * path: La ruta donde se guardará el archivo.
 */
void RedEstaciones::guardarBaseDatos(string path) {
    string nom = path;
    ofstream archivo(nom);
    // Verifica si se pudo abrir el archivo
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para guardar los datos" << endl;
        return;
    }
    // Guardar los precios de los combustibles
    archivo << "[," << precioRegular << "," << precioPremium << "," << preciosEcoExtra << ",]" << endl;
    // Iterar sobre las estaciones
    for (int i = 0; i < nEstaciones; ++i) {
        EstacionDeServicio* estacion = Estaciones[i];
        // Guardar la información de la estación
        archivo << "[," << estacion->identificador << ","
                << estacion->nombre << ","
                << estacion->gerente << ","
                << estacion->region << ","
                << estacion->longitud << ","
                << estacion->latitud << ","
                << estacion->Regular << ","
                << estacion->Premium << ","
                << estacion->EcoExtra << ",]";

        // Guardar la información de los surtidores asociados a la estación
        archivo << "[,";
        for (int j = 0; j < estacion->nSurtidores; ++j) {
            Surtidor* surtidor = estacion->Surtidores[j];
            archivo << surtidor->codigoID << ","<< surtidor->modelo << ","<< (surtidor->estado ? "activo" : "inactivo");
            // Si no es el último surtidor, agregar una coma
            if (j != estacion->nSurtidores - 1) {
                archivo << ",";
            }
        }
        archivo << ",]";
        // Guardar las ventas realizadas en los surtidores
        for (int j = 0; j < estacion->nSurtidores; ++j) {
            Surtidor* surtidor = estacion->Surtidores[j];

            // Iterar sobre el registro de ventas del surtidor
            for (int k = 0; k < surtidor->maxVentas; ++k) {
                if (surtidor->registroVentas[k] != nullptr) {
                    archivo << "[,"
                            << *surtidor->registroVentas[k] << ",]";
                }
            }
        }
        // Nueva línea para la próxima estación
        archivo << endl;
    }
    // Cierra el archivo
    archivo.close();
}
/**
 * Libera la memoria utilizada por los arreglos dinámicos de estaciones y surtidores.
 *
 * Este método recorre todas las estaciones y libera la memoria asociada a los surtidores y
 * las ventas. Luego, libera las estaciones en sí, asegurándose de evitar fugas de memoria.
 */
void RedEstaciones::liberarMemoria() {
    // Recorrer todas las estaciones
    for (int i = 0; i < nEstaciones; ++i) {
        if (Estaciones[i] != nullptr) {
            // Recorrer todos los surtidores de la estación
            for (int j = 0; j < Estaciones[i]->nSurtidores; ++j) {
                if (Estaciones[i]->Surtidores[j] != nullptr) {
                    // Liberar las ventas de cada surtidor
                    for (int k = 0; k < Estaciones[i]->Surtidores[j]->maxVentas; ++k) {
                            delete Estaciones[i]->Surtidores[j]->registroVentas[k];
                        }
                }
                // Liberar el surtidor
                delete Estaciones[i]->Surtidores[j];
            }
        }
        // Liberar la estación
        delete Estaciones[i];
    }
}
