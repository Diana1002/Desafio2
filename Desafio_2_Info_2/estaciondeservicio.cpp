#include "estaciondeservicio.h"

EstacionDeServicio::EstacionDeServicio() {}
short int EstacionDeServicio::convertirAEntero(const string& str){
    short int resultado = 0;
    for (char c:str){
        resultado = resultado*10+(c-'0');
    }return resultado;
}
float EstacionDeServicio::convertirAFloat(const string& str){
    float resultado = 0.0;
    float factor = 1.0;
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
void EstacionDeServicio::leerArchivo(short int id, string& nomArchivo){
    ifstream archivo(nomArchivo);
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

string EstacionDeServicio::getNombre() const
{
    return nombre;
}
string EstacionDeServicio::getGerente() const
{
    return gerente;
}
string EstacionDeServicio::getRegion() const
{
    return region;
}
short EstacionDeServicio::getIdentificador() const
{
    return identificador;
}
const float* EstacionDeServicio::getUbicacionGPS() const
{
    return ubicacionGPS;
}
const int* EstacionDeServicio::getTanqueCentral() const
{
    return tanqueCentral;
}
