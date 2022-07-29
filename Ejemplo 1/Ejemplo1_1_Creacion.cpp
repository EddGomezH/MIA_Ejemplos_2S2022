#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
	int c;
	FILE *fp;
	// Requiere existencia del Archivo
	//fp = fopen("ejemplo1_1.txt", "r"); // Lectura de Archivo
	//fp = fopen("ejemplo1_1.txt", "a"); // Añadir en Archivo
	//fp = fopen("ejemplo1_1.txt", "r+"); // Lectura y Escribe al final del Archivo

	// No es necesaria la existencia del Archivo
	//fp = fopen("ejemplo1_1.txt", "w"); // Crea y Sobreescribe en Archivo
	//fp = fopen("ejemplo1_1.txt", "w+"); // Crea y Sobreescribe en Archivo
	//fp = fopen("ejemplo1_1.txt", "a+"); // Crea y Escribe al final del Archivo
	char str[500] = "Ejemplo 1, Creacion de Archivos con fopen y sus distintos modos de operacion.\n";
	if (fp)
	{
		for(int i=0; i<strlen(str); i++){
			putc(str[i],fp);
		}
	}
	fclose(fp);
}