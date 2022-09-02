%defines
%{
    #include <scanner.h>
    #include <stdlib.h>
    #include <qstring.h>
    #include <iostream>
    #include <nodo.h>
    #include <QString>

    using namespace std;

    extern int yylineno;
    extern char *yytext;
    extern int yyfila;
    extern int yycolum;
    Nodo* Raiz = nullptr;
    QString ErrorS;

    int yyerror(const char* mensaje){
        QString m = mensaje;
        QString fila = QString::number(yyfila);
        QString column = QString::number(yycolum);
        ErrorS+="Error Sintactico "+m+" en Fila "+fila+" y Columna "+column+".\n";
        std::string me = m.toStdString();
        cout<<yytext<<" "<<mensaje<<" "<<yyfila<<" "<<yycolum<<std::endl;
        return 0;
    }

    Nodo* getRaiz(){
    return Raiz;
    }
%}

%define parse.error verbose

%union{
    char TEXT [300];
    struct Nodo* NODO;
}

%token<TEXT> crear
%token<TEXT> escribir
%token<TEXT> vertodo
%token<TEXT> verx
%token<TEXT> graficartodo
%token<TEXT> graficarx
%token<TEXT> tamano
%token<TEXT> dimensional
%token<TEXT> id
%token<TEXT> nombre
%token<TEXT> telefono
%token<TEXT> direccion
%token<TEXT> x
%token<TEXT> guion
%token<TEXT> mayor
%token<TEXT> entero
%token<TEXT> txt
%type<NODO> INICIO
%type<NODO> LCMD
%type<NODO> COMANDOS
%type<NODO> LCOMANDOS
%type<NODO> LOPCIONES
%type<NODO> OPCIONES

%start INICIO
%%

INICIO:LCMD { Raiz = $$; };

LCMD:LCMD COMANDOS
   {
        Nodo* n = new Nodo("LCMD","","");
        n->addHijo($1);
        n->addHijo($2);
        $$ = n;
   }
   |COMANDOS
   {
        Nodo* n = new Nodo("LCMD","","");
        n->addHijo($1);
        $$ = n;
   };

COMANDOS:LCOMANDOS LOPCIONES
        {
            Nodo* n = new Nodo("COMANDOS","","");
            n->addHijo($1);
            n->addHijo($2);
            $$ = n;
        }
        |LCOMANDOS
        {
            Nodo* n = new Nodo("COMANDOS","","");
            n->addHijo($1);
            $$ = n;
        };

LCOMANDOS:crear
         {
            Nodo* n = new Nodo("Crear",$1,"");
            $$ = n;
         }
         |escribir
         {
            Nodo* n = new Nodo("Escribir",$1,"");
            $$ = n;
         }
         |vertodo
         {
            Nodo* n = new Nodo("Vertodo",$1,"");
            $$ = n;
         }
         |verx
         {
            Nodo* n = new Nodo("Verx",$1,"");
            $$ = n;
         }
         |graficartodo
         {
            Nodo* n = new Nodo("Graficartodo",$1,"");
            $$ = n;
         }
         |graficarx
         {
            Nodo* n = new Nodo("Graficarx",$1,"");
            $$ = n;
         };

LOPCIONES:LOPCIONES OPCIONES
     {
        Nodo* n = new Nodo("LOPCIONES","","");
        n->addHijo($1);
        n->addHijo($2);
        $$ = n;
     }
     |OPCIONES
     {
        Nodo* n = new Nodo("LOPCIONES","","");
        n->addHijo($1);
        $$ = n;
     };

OPCIONES:guion tamano guion mayor entero
    {
        Nodo* n = new Nodo("OPCIONES","","");
        Nodo* ntamano = new Nodo("Tamano",$2,"Tamano");
        Nodo* nentero = new Nodo("Entero",$5,"Entero");
        n->addHijo(ntamano);
        n->addHijo(nentero);
        $$ = n;
    }
    |guion dimensional guion mayor txt
    {
        Nodo* n = new Nodo("OPCIONES","","");
        Nodo* ndimensional = new Nodo("Dimensional",$2,"Dimensional");
        Nodo* ntxt = new Nodo("Texto",$5,"Texto");
        n->addHijo(ndimensional);
        n->addHijo(ntxt);
     $$ = n;
    }
    |guion id guion mayor entero
    {
        Nodo* n = new Nodo("OPCIONES","","");
        Nodo* nid = new Nodo("Id",$2,"Id");
        Nodo* nentero = new Nodo("Entero",$5,"Entero");
        n->addHijo(nid);
        n->addHijo(nentero);
        $$ = n;
    }
    |guion nombre guion mayor txt
    {
        Nodo* n = new Nodo("OPCIONES","","");
        Nodo* nnombre = new Nodo("Nombre",$2,"Nombre");
        Nodo* ntxt = new Nodo("Texto",$5,"Texto");
        n->addHijo(nnombre);
        n->addHijo(ntxt);
     $$ = n;
    }
    |guion telefono guion mayor entero
    {
        Nodo* n = new Nodo("OPCIONES","","");
        Nodo* ntelefono = new Nodo("Telefono",$2,"Telefono");
        Nodo* nentero = new Nodo("Entero",$5,"Entero");
        n->addHijo(ntelefono);
        n->addHijo(nentero);
        $$ = n;
    }
    |guion direccion guion mayor txt
    {
        Nodo* n = new Nodo("OPCIONES","","");
        Nodo* ndireccion = new Nodo("Direccion",$2,"Direccion");
        Nodo* ntxt = new Nodo("Texto",$5,"Texto");
        n->addHijo(ndireccion);
        n->addHijo(ntxt);
     $$ = n;
    }
    |guion x guion mayor entero
    {
        Nodo* n = new Nodo("OPCIONES","","");
        Nodo* nx = new Nodo("X",$2,"X");
        Nodo* nentero = new Nodo("Entero",$5,"Entero");
        n->addHijo(nx);
        n->addHijo(nentero);
        $$ = n;
    };
