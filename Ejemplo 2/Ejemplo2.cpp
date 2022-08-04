#include <fstream>
#include <cstdio>
#include <iostream>
#include "stdlib.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;

typedef struct
{
    int id;
    char nombre[15];
    int telefono;
    char direccion[15];
} Ejemplo;

void crear_archivo(int tamano, char dim);
void mostrar_struct(Ejemplo ejm);

void crear_archivo(int tamano, char dim)
{
    // Calculo Tamaño del Archivo
    int size_file = 0;
    if (dim == 'k' || dim == 'K')
    {
        size_file = tamano;
    }
    else if (dim == 'm' || dim == 'M')
    {
        size_file = tamano * 1024;
    }
    else if (dim == 'g' || dim == 'G')
    {
        size_file = tamano * 1024 * 1024;
    }

    // Preparacion Bloque
    char bloque[1024];
    for (int i = 0; i < 1024; i++)
    {
        bloque[i] = '\0';
    }

    // Escritura de Bloque en Archivo
    int limite = 0;
    FILE *archivo_binario;
    archivo_binario = fopen("Ejemplo2.dsk", "w");
    while (limite != size_file)
    {
        fwrite(&bloque, 1024, 1, archivo_binario);
        limite++;
    }
    fclose(archivo_binario);
}

void mostrar_struct(Ejemplo ejm)
{
    if(ejm.id > 0 && ejm.nombre != "" && ejm.telefono > 0 && ejm.direccion != ""){
        cout << "ID: ";
        cout << ejm.id;
        cout << ", Nombre: ";
        cout << ejm.nombre;
        cout << ", Telefono: ";
        cout << ejm.telefono;
        cout << ", Direccion: ";
        cout << ejm.direccion << endl;
    }
}

int main()
{
    string opcion = "", opcionsub = "", nombre = "", direccion = "";
    int eleccion = 0, tamano = 0, registros = 0, xreg = 0, cont = 0;
    char dim = 0;
    FILE *archivo_binario;
    Ejemplo ejm, aux;
    while (eleccion != 5)
    {
        cout << "-----------------------------------------" << endl;
        cout << "  Manejo e Implementacion de Archivos A+ " << endl;
        cout << "      Ejemplo Practico Laboratorio 3     " << endl;
        cout << "-----------------------------------------" << endl;
        cout << "      Selecciona una opcion:             " << endl;
        cout << "      1. Crear Archivo Binario           " << endl;
        cout << "      2. Escribir en Archivo             " << endl;
        cout << "      3. Ver Todos los Registros         " << endl;
        cout << "      4. Ver X Registro                  " << endl;
        cout << "      5. Salir                           " << endl;
        cout << "-----------------------------------------" << endl;
        getline(cin, opcion);
        eleccion = atoi(opcion.c_str());
        switch (eleccion)
        {
        case 1:
            cout << "-----------------------------------------" << endl;
            cout << "         Creacion Archivo Binario        " << endl;
            cout << "-----------------------------------------" << endl;
            cout << "      Ingrese el tamano del Archivo      " << endl;
            getline(cin, opcionsub);
            tamano = atoi(opcionsub.c_str());
            cout << "      Ingrese el dimensional del Archivo " << endl;
            getline(cin, opcionsub);
            dim = opcionsub.at(0);
            crear_archivo(tamano, dim);
            cout << "Archivo Binario  creado con exito!!!" << endl;
            break;
        case 2:
            cout << "-----------------------------------------" << endl;
            cout << " Escritura de X registros en el Archivo  " << endl;
            cout << "-----------------------------------------" << endl;
            cout << "    Ingrese la cantidad de escrituras    " << endl;
            getline(cin, opcionsub);
            registros = atoi(opcionsub.c_str());
            cout << "-----------------------------------------" << endl;
            archivo_binario = fopen("Ejemplo2.dsk", "rb+");
            for (int i = 0; i < registros; i++)
            {
                ejm.id = i + 1;
                nombre = "registro ";
                nombre += to_string(ejm.id);
                strcpy(ejm.nombre, nombre.c_str());
                ejm.telefono = (rand() + i) + 1;
                direccion = "direccion ";
                direccion += to_string(ejm.id);
                strcpy(ejm.direccion, direccion.c_str());
                fseek(archivo_binario, i * sizeof(Ejemplo), SEEK_SET);
                fwrite(&ejm, sizeof(ejm), 1, archivo_binario);
                mostrar_struct(ejm);
                nombre = "";
                direccion = "";
            }
            fclose(archivo_binario);
            break;
        case 3:
            cout << "-----------------------------------------" << endl;
            cout << "  Ver todos los registros en el archivo  " << endl;
            cout << "-----------------------------------------" << endl;
            archivo_binario = fopen("Ejemplo2.dsk", "rb+");
            while (ejm.id > 0)
            {
                fseek(archivo_binario,cont*sizeof(Ejemplo), SEEK_SET);
                fread(&ejm, sizeof(ejm), 1, archivo_binario);
                mostrar_struct(ejm);
                cont++;
            }
            cont = 0;
            fclose(archivo_binario);
            break;
        case 4:
            cout << "-----------------------------------------" << endl;
            cout << "      Ver X registro en el archivo       " << endl;
            cout << "-----------------------------------------" << endl;
            cout << "   Ingrese el indice del registro (>0)   " << endl;
            getline(cin, opcionsub);
            xreg = atoi(opcionsub.c_str()) - 1;
            cout << "-----------------------------------------" << endl;
            archivo_binario = fopen("Ejemplo2.dsk", "rb+");
            fseek(archivo_binario, xreg * sizeof(Ejemplo), SEEK_SET);
            fread(&ejm, sizeof(ejm), 1, archivo_binario);
            mostrar_struct(ejm);
            fclose(archivo_binario);
            break;
        }
    }
    return 0;
}