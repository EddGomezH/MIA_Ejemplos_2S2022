#ifndef ANALIZADOR_H
#define ANALIZADOR_H
#include <iostream>
#include <nodo.h>
#include <parser.h>
#include <string>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include "comando.h"

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
} Resultado;

extern Nodo* getRaiz();
extern int yyrestart(FILE* entrada);
extern int yyparse();

class Analizador
{
public:
    Comando com;
    string ComandoC=" ", Tamano=" ", Dimensional=" ", Id=" ", Nombre=" ", Telefono=" ", Direccion=" ", X=" ";
    void LeerEntrada(QString txt);
    void Recorrer(Nodo *raiz);
    void Ejecutar(Nodo* raiz);
    Resultado Resultados();
    void LimpiarGlobales();
    void EjecutarComando(Resultado r);
    void EjecutarCrear(Resultado r);
    void EjecutarEscribir(Resultado r);
    void EjecutarVertodo(Resultado r);
    void EjecutarVerx(Resultado r);
    void Analizar();
};

#endif // ANALIZADOR_H
