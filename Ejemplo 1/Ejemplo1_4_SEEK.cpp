
#include <stdio.h>
#include <iostream>
#include <cstring>  

using namespace std;

int main()
{
    FILE *file;
    file = fopen("ejemplo1_4.txt", "r");
    char cont[11];
      
    //fseek(file, 0, SEEK_SET);   // Desde el inicio hasta donde el indice indicado.
    //fseek(file, -5, SEEK_END);  // Desde el final hasta donde el indice indicado (Indices negativos).
    //fseek(file, 5, SEEK_CUR);   // Desde la posicion actual del punto, avanza las nuevas posiciones indicadas.

    cout << "Puntero:   " << ftell(file) << endl;
    
    fread(&cont,10,1, file);

    for(int i = 0; i < strlen(cont); i++){
		cout << cont[i];     
	}
  
    return 0;
}