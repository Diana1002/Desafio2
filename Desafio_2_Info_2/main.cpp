#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include "RedEstaciones.h"
#include "estaciondeservicio.h"
using namespace std;

int main(){
    EstacionDeServicio estacion;
    short int n = 2;
    short int* surtidor1 = estacion.crearSurtidor(n);

    cout<< surtidor1[0]<<endl;
    cout<< surtidor1[1]<<endl;
    cout<< surtidor1[2]<<endl;
    cout<< surtidor1[3]<<endl;
    cout<< surtidor1[4]<<endl;
    cout<< surtidor1[5]<<endl;

    delete[] surtidor1;
}
