#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    int retVal;
    FILE *file;
    char cont[] = "Ejemplo 1, Escritura de Archivos con fwrite.\n";

    file = fopen("ejemplo1_3.txt","w");
    retVal = fwrite(cont,sizeof(cont),1,file);
    
    cout << "fwrite returned " << retVal;
    return 0;
}