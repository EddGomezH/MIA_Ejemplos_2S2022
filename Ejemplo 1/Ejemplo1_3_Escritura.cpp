#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    int retVal;
    FILE *fp;
    char buffer[] = "Ejemplo 1, Escritura de Archivos con fwrite.\n";

    fp = fopen("ejemplo1_3.txt","w");
    retVal = fwrite(buffer,sizeof(buffer),1,fp);
    
    cout << "fwrite returned " << retVal;
    return 0;
}