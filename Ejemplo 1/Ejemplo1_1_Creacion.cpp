#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
	FILE *file;
	// Requiere existencia del Archivo
	//file = fopen("ejemplo1_1.txt", "r"); // Lectura de Archivo
	//file = fopen("ejemplo1_1.txt", "a"); // Añadir en Archivo
	//file = fopen("ejemplo1_1.txt", "r+"); // Lectura y Escribe al final del Archivo

	// No es necesaria la existencia del Archivo
	//file = fopen("ejemplo1_1.txt", "w"); // Crea y Sobreescribe en Archivo
	//file = fopen("ejemplo1_1.txt", "w+"); // Crea y Sobreescribe en Archivo
	//file = fopen("ejemplo1_1.txt", "a+"); // Crea y Escribe al final del Archivo
	char str[500] = "Ejemplo 1, Creacion de Archivos con fopen y sus distintos modos de operacion.\n";
	if (file)
	{
		for(int i=0; i<strlen(str); i++){
			putc(str[i],file);
		}
	}
	fclose(file);
}