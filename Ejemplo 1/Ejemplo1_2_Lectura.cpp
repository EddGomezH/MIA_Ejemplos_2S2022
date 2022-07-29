#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    FILE *fp;
    char buffer[100];
    
    fp = fopen("ejemplo1_2.txt","r");
    while(!feof(fp))
    {
        fread(buffer,sizeof(buffer),1,fp);
        cout << buffer;
    }
    
    return 0;
}