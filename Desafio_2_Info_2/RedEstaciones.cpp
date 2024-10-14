#include "RedEstaciones.h"

RedEstaciones::RedEstaciones() {
    for (EstacionDeServicio*&ptr:Estaciones){
        ptr = nullptr;

    }
}

void RedEstaciones::cargarRed(string path)
{
    nomArchivo = path;
    abrirBaseDatos();



}

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
short int RedEstaciones::convertirAEntero(const string& str){
    short int resultado = 0;
    for (char c:str){
        resultado = resultado*10+(c-'0');
    }return resultado;
}
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
        for(int i = 1; i<cantidadBloques;i++){
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
void RedEstaciones::crearEstacion(){
    string nueva = "", aux = "";
    cout<<"Ingresa el numero identificador"<<endl;
    getline(cin, aux);
    nueva += aux + ",";
    cout<<"Ingresa el nombre de la estacion"<<endl;
    getline(cin, aux);
    nueva += aux + ",";
    cout<<"Ingresa el nombre del gerente"<<endl;
    getline(cin, aux);
    nueva += aux + ",";
    cout<<"Ingresa la region"<<endl;
    getline(cin, aux);
    nueva += aux + ",";
    cout<<"Ingresa la longitud"<<endl;
    getline(cin, aux);
    nueva += aux + ",";
    cout<<"Ingresa latitud"<<endl;
    getline(cin, aux);
    nueva += aux + ",";
    cout<<"Ingresa la capacidad maxima de combustible Regular"<<endl;
    getline(cin, aux);
    nueva += aux + ",";
    cout<<"Ingresa la capacidad maxima de combustible premium"<<endl;
    getline(cin, aux);
    nueva += aux + ",";
    cout<<"Ingresa la capacidad maxima de combustible EcoExtra"<<endl;
    getline(cin, aux);
    nueva += aux;
    cout<<nueva<<endl;
    // Abrir el archivo en modo append
    ofstream archivo(nomArchivo, ios::app);

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        archivo<<endl;
        archivo << nueva << endl; // Escribir el texto y añadir un salto de línea
        archivo.close(); // Cerrar el archivo
        cout << "Estacion agregada exitosamente." << endl;
    } else {
        cerr << "Error al abrir la base de datos" << endl;
    }
}
