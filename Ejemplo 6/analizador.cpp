#include "analizador.h"

void Analizador::LeerEntrada(QString txt){
    QString filename = "Entrada.txt";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << txt << endl;
    }
    file.close();
}

void Analizador::Recorrer(Nodo *raiz){
        if(raiz->Nombre == "INICIO"){
           // INICIO -> LCMD
           Recorrer(raiz->Hojas[0]);
        }else if(raiz->Nombre == "LCMD") {
            switch (raiz->Hojas.size()) {
                case 1:
                // LCMD -> COMANDOS
                Recorrer(raiz->Hojas[0]);
                break;
                case 2:
                // LCMD -> LCMD COMANDOS
                Recorrer(raiz->Hojas[0]);
                Recorrer(raiz->Hojas[1]);
                break;
            }
        }
        else if(raiz->Nombre == "COMANDOS"){
            // COMANDOS -> LCOMANDOS LOPCIONES
            if(raiz->Hojas[0]->Nombre == "Crear"){
                cout << "*----------------------------------------------------------*" << endl;
                cout << "Ejecucion de Crear..." << endl;
                ComandoC = "Crear";
            }else if(raiz->Hojas[0]->Nombre == "Escribir"){
                cout << "*----------------------------------------------------------*" << endl;
                cout << "Ejecucion de Escribir..." << endl;
                ComandoC = "Escribir";
            }else if(raiz->Hojas[0]->Nombre == "Vertodo"){
                cout << "*----------------------------------------------------------*" << endl;
                cout << "Ejecucion de Vertodo..." << endl;
                ComandoC = "Vertodo";
            }else if(raiz->Hojas[0]->Nombre == "Verx"){
                cout << "*----------------------------------------------------------*" << endl;
                cout << "Ejecucion de Verx..." << endl;
                ComandoC = "Verx";
            }else if(raiz->Hojas[0]->Nombre == "Graficartodo"){
                cout << "*----------------------------------------------------------*" << endl;
                cout << "Ejecucion de Graficartodo..." << endl;
                ComandoC = "Graficartodo";
            }else if(raiz->Hojas[0]->Nombre == "Graficarx"){
                cout << "*----------------------------------------------------------*" << endl;
                cout << "Ejecucion de Graficarx..." << endl;
                ComandoC = "Graficarx";
            }
            if(raiz->Hojas.size()==2){
                Recorrer(raiz->Hojas[1]);
            }
        }else if(raiz->Nombre == "LOPCIONES"){
            switch(raiz->Hojas.size()){
                case 1:
                // LOPCIONES -> OPCIONES
                Recorrer(raiz->Hojas[0]);
                break;
                case 2:
                // LOPCIONES -> LOPCIONES OPCIONES
                Recorrer(raiz->Hojas[0]);
                Recorrer(raiz->Hojas[1]);
                break;
            }
        }else if(raiz->Nombre == "OPCIONES"){
            if(raiz->Hojas[0]->Nombre == "Tamano"){
                // - Tamano -> Entero
                Tamano = raiz->Hojas[1]->Token;
                cout << "Tamano: " << Tamano << endl;
            }else if(raiz->Hojas[0]->Nombre == "Dimensional"){
                // -Dimensional -> Texto
                Dimensional = raiz->Hojas[1]->Token;
                cout << "Dimensional: " << Dimensional << endl;
            }else if(raiz->Hojas[0]->Nombre == "Id"){
                // -Id -> Entero
                Id = raiz->Hojas[1]->Token;
                cout << "Id: " << Id << endl;
            }else if(raiz->Hojas[0]->Nombre == "Nombre"){
                // -Nombre -> Texto
                Nombre = raiz->Hojas[1]->Token;
                cout << "Nombre: " << Nombre << endl;
            }else if(raiz->Hojas[0]->Nombre == "Telefono"){
                // -Telefono -> Entero
                Telefono = raiz->Hojas[1]->Token;
                cout << "Telefono: " << Telefono << endl;
            }else if(raiz->Hojas[0]->Nombre == "Direccion"){
                // -Direccion -> Texto
                Direccion = raiz->Hojas[1]->Token;
                cout << "Direccion: " << Direccion << endl;
            }else if(raiz->Hojas[0]->Nombre == "X"){
                // -X -> Entero
                X = raiz->Hojas[1]->Token;
                cout << "X: " << X << endl;
            }
        }
}

Resultado Analizador::Resultados(){
    Resultado res;
    res.Comando = ComandoC;
    res.Tamano = Tamano;
    res.Dimensional = Dimensional;
    res.Id =  Id;
    res.Nombre = Nombre;
    res.Telefono = Telefono;
    res.Direccion = Direccion;
    res.X = X;
    return res;
}

void Analizador::Ejecutar(Nodo *raiz){
    Resultado res;
    Recorrer(raiz);
    res = Resultados();
    EjecutarComando(res);
    LimpiarGlobales();
}

void Analizador::LimpiarGlobales(){
    ComandoC = " ";
    Tamano = " ";
    Dimensional = " ";
    Id = " ";
    Nombre = " ";
    Telefono = " ";
    Direccion = " ";
    X = " ";
}


void Analizador::EjecutarComando(Resultado r){
    if(r.Comando == "Crear"){
        EjecutarCrear(r);
    }else if (r.Comando == "Escribir") {
        EjecutarEscribir(r);
    }else if (r.Comando == "Vertodo") {
        EjecutarVertodo(r);
    }else if (r.Comando == "Verx") {
        EjecutarVerx(r);
    }else if (r.Comando == "Graficartodo"){
        EjecutarGraficartodo(r);
    }else if (r.Comando == "Graficarx"){
        EjecutarGraficarx(r);
    }
}


void Analizador::EjecutarCrear(Resultado r){
    if(r.Tamano != " " && r.Dimensional != " "){
       cout << "Crear: OK" << endl;
       QString dim = QString::fromUtf8(r.Dimensional.c_str());
       com.crearArchivo(r.Tamano,dim.replace("\"","").toStdString());
   }else{
        cout << "ERROR: Se debe definir el tamano y la dimensional..." << endl;
    }
}

void Analizador::EjecutarEscribir(Resultado r){
    if(r.Id != " " && r.Nombre != " " && r.Telefono != " " && r.Direccion != " " && r.X != " "){
       cout << "Escribir: OK" << endl;
       com.escribir(r.Id,r.Nombre,r.Telefono,r.Direccion,r.X);
   }else{
        cout << "ERROR: Se debe definir los atributos para registrar la informacion..." << endl;
   }
}

void Analizador::EjecutarVertodo(Resultado r){
    cout << "Vertodo: OK" << endl;
    com.vertodo();
}

void Analizador::EjecutarVerx(Resultado r){
    if(r.X != " "){
       cout << "Verx: OK" << endl;
       com.verX(r.X);
   }else{
        cout << "ERROR: Se debe definir los atributos para obtener la informacion..." << endl;
   }
}

void Analizador::EjecutarGraficartodo(Resultado r){
    cout << "Graficartodo: OK" << endl;
    com.graficartodo();
}

void Analizador::EjecutarGraficarx(Resultado r){
    cout << "Graficarx: OK" << endl;
    if(r.X != " "){
        com.graficarX(r.X);
    }else{
        cout << "ERROR: Se debe definir los atributos para obtener la informacion..." << endl;
   }
}


void Analizador::Analizar(){
    FILE* in;
    Nodo* raiz = nullptr;
    in = fopen("Entrada.txt","r");
    yyrestart(in); //Lexico
    yyparse(); //Sintactico
    raiz = getRaiz();
    if(raiz != nullptr){
       Ejecutar(raiz);
    }
    fclose(in);
}
