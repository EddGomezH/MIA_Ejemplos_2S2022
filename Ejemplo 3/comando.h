#ifndef COMANDO_H
#define COMANDO_H

#include <fstream>
#include <cstdio>
#include <iostream>
#include "stdlib.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;

typedef struct{
    string Comando = " ";
    string Tamano = " ";
    string Dimensional = " ";
    string Id = " ";
    string Nombre = " ";
    string Telefono = " ";
    string Direccion = " ";
    string X = " ";
}Parametros;

typedef struct{
    int id;
    char nombre[15];
    int telefono;
    char direccion[15];
} Ejemplo;

class Comando{
    public:
        Parametros param;
        void identificacionCMD(Parametros p);
        void crearArchivo(string tam, string dim);
        void escribir(string id, string nombre, string tel, string dir, string x);
        void vertodo();
        void verX(string x);
        void eliminarX(string x);
        void mostrar_struct(Ejemplo ejm);
};

#endif // COMANDO_H