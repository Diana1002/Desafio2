#include <QCoreApplication>

#include "RedEstaciones.h"

using namespace std;

int main(){
    RedEstaciones Red;
    //string n = "C:\\Users\\Asus\\Documents\\DIANA BAEZA RUIZ\\SEMESTRE 2024-2\\Desafio2\\BaseDeDatos.txt";
    string n = "C:\\Users\\Asus\\Documents\\DIANA BAEZA RUIZ\\SEMESTRE 2024-2\\Desafio2\\BaseDeDatos.txt";

    Red.cargarRed(n);

    /*EstacionDeServicio Estacion(1, "La Maria", "William", "Sur",12.34,-13.56, 130,20,50);
    Estacion.crearSurtidor(2, "m_19");
    Estacion.Surtidores[0]->Vender("Gj","Gj","Gj","Gj","Gj","Gj","Gj");

    cout<<Estacion.getGerente()<<endl;
    cout<<*(Estacion.Surtidores[0]->registroVentas[0])<<endl;*/


}
