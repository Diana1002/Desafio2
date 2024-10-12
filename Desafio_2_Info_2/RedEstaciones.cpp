#include "RedEstaciones.h"

RedEstaciones::RedEstaciones() {}
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
void RedEstaciones:: abrirBaseDatos(short int id){
    string nombreArchivo = getNomArchivo();
    ifstream archivo(nombreArchivo);
    string linea;
    char delimitador = ',';
    bool encontrado = false;

    if (!archivo){
        cerr<< "No se pudo abrir el archivo"<<endl;
        return ;
    }

    while (getline(archivo, linea)){
        int i = 0;
        string campos[9];
        string campo = "";

        for (size_t j = 0; j<linea.length();j++){
            if (linea[j] == delimitador){
                campos[i++] = campo;
                campo = "";
            }
            else{
                campo += linea[j];
            }
        }
        campos[i] = campo;

        short int idEstacion = convertirAEntero(campos[0]);

        if (idEstacion == id){
            identificador = idEstacion;
            nombre = campos[1];
            gerente = campos[2];
            region = campos[3];

            ubicacionGPS[0] = convertirAFloat(campos[4]);
            ubicacionGPS[1] = convertirAFloat(campos[5]);

            tanqueCentral[0] = convertirAEntero(campos[6]);
            tanqueCentral[1] = convertirAEntero(campos[7]);
            tanqueCentral[2] = convertirAEntero(campos[8]);
            encontrado = true;
            break;
        }
    }
    if(!encontrado){
        cout<<"No se encontro la estacion con el ID: "<<id<<endl;
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
    string nombreArchivo = getNomArchivo();
    // Abrir el archivo en modo append
    ofstream archivo(nombreArchivo, ios::app);

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
string RedEstaciones::getNombre() const
{
    return nombre;
}
string RedEstaciones::getGerente() const
{
    return gerente;
}
string RedEstaciones::getRegion() const
{
    return region;
}
short RedEstaciones::getIdentificador() const
{
    return identificador;
}
const float* RedEstaciones::getUbicacionGPS() const
{
    return ubicacionGPS;
}
const int* RedEstaciones::getTanqueCentral() const
{
    return tanqueCentral;
}
string RedEstaciones::getNomArchivo() const
{
    return nomArchivo;
}
void RedEstaciones::setNomArchivo(const string &newNomArchivo)
{
    nomArchivo = newNomArchivo;
}
