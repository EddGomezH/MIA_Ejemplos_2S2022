#include "analizador.h"

vector<string> Analizador::split_txt(string text){ // Split para separar tipo de comando y parametros
    stringstream text_to_split(text);
    string segment;
    vector<string> splited;

    while(std::getline(text_to_split, segment, ' ')){
       splited.push_back(segment);
    }
    return splited;
}

string Analizador::replace_txt(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void Analizador::analizar(string entrada){
    string entradacmd = entrada;
    // Transformacion de toda la entrada a minusculas
    transform(entradacmd.begin(), entradacmd.end(), entradacmd.begin(), ::tolower);
    vector<string> cmdentrada = split_txt(entradacmd);
    vector<string> parametros;
    string comando = "";
    for(int i = 0; i< cmdentrada.size(); i++){
        if(i == 0){
            comando = cmdentrada.at(i);
        }else{
            parametros.push_back(cmdentrada.at(i));
        }
    }
    // Identificacion de comando, parametros y ejecucion
    identificarParametros(comando, parametros);
}

void Analizador::identificarParametros(string comando, vector<string> parametros){
    string param = "";
    if(comando == "crear"){
        cmd.param.Comando = "crear";
        // Guardado de parametros en Struct
        for(int i=0; i<parametros.size(); i++){
            param = parametros.at(i);
            if(param.find("-t->") == 0){
                param = replace_txt(param, "-t->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.Tamano = param;
            } else if(param.find("-d->") == 0){
                param = replace_txt(param, "-d->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.Dimensional = param;
            }
        }
        // Ejecucion de metodo
        cmd.identificacionCMD(cmd.param);
    } else if(comando == "escribir"){
        cmd.param.Comando = "escribir";
        // Guardado de parametros en Struct
        for(int i=0; i<parametros.size(); i++){
            param = parametros.at(i);
            if(param.find("-id->") == 0){
                param = replace_txt(param, "-id->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.Id = param;
            } else if(param.find("-nombre->") == 0){
                param = replace_txt(param, "-nombre->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.Nombre = param;
            } else if(param.find("-telefono->") == 0){
                param = replace_txt(param, "-telefono->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.Telefono = param;
            } else if(param.find("-direccion->") == 0){
                param = replace_txt(param, "-direccion->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.Direccion = param;
            } else if(param.find("-x->") == 0){
                param = replace_txt(param, "-x->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.X = param;
            }
        }
        // Ejecucion de metodo
        cmd.identificacionCMD(cmd.param);
    } else if(comando == "vertodo"){
        cmd.param.Comando = "vertodo";
        // Ejecucion de metodo
        cmd.identificacionCMD(cmd.param);   
    } else if(comando == "verx"){
        cmd.param.Comando = "verx";
        // Guardado de parametros en Struct
        for(int i=0; i<parametros.size(); i++){
            param = parametros.at(i);
            if(param.find("-x->") == 0){
                param = replace_txt(param, "-x->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.X = param;
            }
        }
        // Ejecucion de metodo
        cmd.identificacionCMD(cmd.param);
    } else if(comando == "eliminarx"){
        cmd.param.Comando = "eliminarx";
        // Guardado de parametros en Struct
        for(int i=0; i<parametros.size(); i++){
            param = parametros.at(i);
            if(param.find("-x->") == 0){
                param = replace_txt(param, "-x->", "");
                param = replace_txt(param, "\"", "");
                cmd.param.X = param;
            }
        }
        // Ejecucion de metodo
        cmd.identificacionCMD(cmd.param);
    }
}