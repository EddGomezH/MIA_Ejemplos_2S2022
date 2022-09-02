#ifndef NODO_H
#define NODO_H
#include <string>
#include <QList>
#include <stdio.h>
#include <stdlib.h>

class Nodo
{
public:
    Nodo(const std::string& nombre, const std::string& token, const std::string& tipo);
    std::string Nombre;
    std::string Token;
    std::string Tipo;
    QList<Nodo*> Hojas;
    void addHijo(Nodo* hoja);
};

#endif // NODO_H
