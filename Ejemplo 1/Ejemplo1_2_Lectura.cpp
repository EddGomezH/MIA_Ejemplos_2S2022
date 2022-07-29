#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    FILE *file;
    char cont[100];
    
    file = fopen("ejemplo1_2.txt","r");
    while(!feof(file))
    {
        fread(&cont,sizeof(cont),1,file);
        cout << cont;
    }
    
    return 0;
}