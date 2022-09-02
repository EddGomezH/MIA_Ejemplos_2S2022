#include "comando.h"

void Comando::crearArchivo(string tam, string dim){
    // Calculo Tamaño del Archivo
    int size_file = 0, tamano = atoi(tam.c_str());
    char dimen = dim.at(0);
    if (dimen == 'k' || dimen == 'K')
    {
        size_file = tamano;
    }
    else if (dimen == 'm' || dimen == 'M')
    {
        size_file = tamano * 1024;
    }
    else if (dimen == 'g' || dimen == 'G')
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
    archivo_binario = fopen("Ejemplo6.dsk", "w");
    while (limite != size_file)
    {
        fwrite(&bloque, 1024, 1, archivo_binario);
        limite++;
    }
    fclose(archivo_binario);
}

void Comando::escribir(string id, string nombre, string tel, string dir, string x){
    FILE *archivo_binario;
    Ejemplo ejm;
    string nm = "", direc = "";
    int registros = atoi(x.c_str());

    archivo_binario = fopen("Ejemplo6.dsk", "rb+");
    for (int i = 0; i < registros; i++){
        // Seteo de parametros en Struct
        ejm.id = i + atoi(id.c_str());
        nm = nombre;
        nm += " " + to_string(ejm.id);
        strcpy(ejm.nombre, nm.c_str());
        ejm.telefono = (rand() + i) + atoi(tel.c_str());
        direc = dir;
        direc += " " + to_string(ejm.id);
        strcpy(ejm.direccion, direc.c_str());
        // Movimiento de puntero y escritura de Struct en archivo binario
        fseek(archivo_binario, i * sizeof(Ejemplo), SEEK_SET);
        fwrite(&ejm, sizeof(ejm), 1, archivo_binario);
        nm = "";
        direc = "";
    }
    fclose(archivo_binario);
}

void Comando::vertodo(){
    FILE *archivo_binario;
    Ejemplo ejm;
    int cont = 0;
    archivo_binario = fopen("Ejemplo6.dsk", "rb+");
    while (!feof(archivo_binario)){
        // Movimiento de puntero y lectura de Struct en archivo binario
        fseek(archivo_binario,cont*sizeof(Ejemplo), SEEK_SET);
        fread(&ejm, sizeof(ejm), 1, archivo_binario);
        mostrar_struct(ejm);
        cont++;
    }
    cont = 0;
    fclose(archivo_binario);
}

void Comando::verX(string x){
    FILE *archivo_binario;
    Ejemplo ejm;
    int xreg = atoi(x.c_str()) - 1;
    archivo_binario = fopen("Ejemplo6.dsk", "rb+");
    // Movimiento de puntero y lectura de Struct en archivo binario
    fseek(archivo_binario, xreg * sizeof(Ejemplo), SEEK_SET);
    fread(&ejm, sizeof(ejm), 1, archivo_binario);
    mostrar_struct(ejm);
    fclose(archivo_binario);
}

void Comando::graficartodo(){
    Ejemplo ejm, aux;
    ofstream all;
        int cont = 0, cont2 = 0;
        FILE *archivo_binario;
        archivo_binario = fopen("Ejemplo6.dsk", "rb+");
        string cmd = "dot -Tjpg Ejemplo6_1.dot -o Ejemplo6_1.jpg";
        all.open("Ejemplo6_1.dot");
        all << "digraph Ejemplo6_1 {\n";
        all << "rankdir = \"LR\"\n";
        all << "edge [arrowhead=vee style=dashed]\n";
        do{
            fseek(archivo_binario, cont * sizeof(Ejemplo), SEEK_SET);
            fread(&ejm, sizeof(ejm), 1, archivo_binario);
            if (ejm.id > 0){
                all << "node";
                all << ejm.id-1;
                all << "[ label = \"<f0>" + to_string(ejm.id) + " | ";
                all << "<f1>";
                all << ejm.nombre;
                all << " | ";
                all << "<f2>";
                all << ejm.telefono;
                all << " | ";
                all << "<f3>";
                all << ejm.direccion;
                all << "\" shape = \"record\" style=filled fillcolor=\"cadetblue1\"];\n";
                fseek(archivo_binario, (cont + 1) * sizeof(Ejemplo), SEEK_SET);
                fread(&aux, sizeof(aux), 1, archivo_binario);
                if(aux.id > 0){
                    all << "node";
                    all <<  ejm.id - 1;
                    all << ":f0 -> node";
                    all << aux.id - 1;
                    all << ":f0\n";
                }
            }
            cont++;
        } while (ejm.id > 0);
        cont = 0;
        all << "}\n";
        all.close();
        fclose(archivo_binario);
        system(cmd.c_str());
        system("fim -a Ejemplo6_1.jpg");
}

void Comando::graficarX(string x){
        FILE *archivo_binario;
        Ejemplo ejm;
        int xreg = atoi(x.c_str()) - 1;
        archivo_binario = fopen("Ejemplo6.dsk", "rb+");
        // Movimiento de puntero y lectura de Struct en archivo binario
        fseek(archivo_binario, xreg * sizeof(Ejemplo), SEEK_SET);
        fread(&ejm, sizeof(ejm), 1, archivo_binario);
        ofstream registrox;
        string cmd = "dot -Tjpg Ejemplo6_2.dot -o Ejemplo6_2.jpg";
        registrox.open("Ejemplo6_2.dot");
        registrox << "digraph Ejemplo6_2 {\n";
        registrox << "node[shape=plaintext];\n";
        registrox << "T[label=<\n<table border=\"1\" cellborder =\"1\">\n";
        registrox << "<tr><td bgcolor=\"yellow\">Ejemplo6_2</td></tr>\n";
        registrox << "<tr><td bgcolor=\"aquamarine\">Atributo</td><td bgcolor=\"darkseagreen3\">Valor</td></tr>\n";
        registrox << "<tr><td bgcolor=\"aquamarine\">id</td><td bgcolor=\"darkseagreen3\">";
        registrox << ejm.id;
        registrox << "</td></tr>\n";
        registrox << "<tr><td bgcolor=\"aquamarine\">nombre</td><td bgcolor=\"darkseagreen3\">";
        registrox << ejm.nombre;
        registrox << "</td></tr>\n";
        registrox << "<tr><td bgcolor=\"aquamarine\">telefono</td><td bgcolor=\"darkseagreen3\">";
        registrox << ejm.telefono;
        registrox << "</td></tr>\n";
        registrox << "<tr><td bgcolor=\"aquamarine\">direccion</td><td bgcolor=\"darkseagreen3\">";
        registrox << ejm.direccion;
        registrox << "</td></tr>\n";
        registrox << "</table>>];\n";
        registrox << "}\n";
        registrox.close();
        system(cmd.c_str());
        system("fim -a Ejemplo6_2.jpg");
}

void Comando::graficarDirectorio(){

}


void Comando::mostrar_struct(Ejemplo ejm){
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
