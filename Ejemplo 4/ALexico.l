%option case-insensitive
%option noyywrap
%option nounput

%{
#include <parser.h>
#include <iostream>

using namespace std;

int yyfila = 1;
int yycolum = 0;
%}

Letra [a-zñA-ZÑ]
Entero -?[0-9]+
Palabra {Letra}({Letra}|{Entero}|".")*
Cadena "\""[^"\""]*"\""
Texto ({Palabra}|{Cadena})
Espacios (" "|"\r"|"\t"|"n")
%x ComentarioSimple

%%
"#"                         {  BEGIN ComentarioSimple; }
"Crear"                     {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return crear;}
"Escribir"                  {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return escribir;}
"Vertodo"                   {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return vertodo;}
"Verx"                      {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return verx;}
"Tamano"                    {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return tamano;}
"Dimensional"               {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return dimensional;}
"Id"                        {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return id;}
"Nombre"                    {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return nombre;}
"Telefono"                  {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return telefono;}
"Direccion"                 {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return direccion;}
"X"                         {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return x;}
"-"                         {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return guion;}
">"                         {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return mayor;}
{Entero}                    {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return entero;}
{Texto}                     {  yycolum+=yyleng; strcpy(yylval.TEXT, yytext); return txt;}
{Espacios}                  { /* Nada */}
.                           {  cout<<"Error lexico, no se esperaba token:   "<<yytext<<endl;}
<ComentarioSimple>.         {  /* No hace nada */ }
<ComentarioSimple>"\n"      {  yyfila++; yycolum = 0; BEGIN INITIAL; }
%%
