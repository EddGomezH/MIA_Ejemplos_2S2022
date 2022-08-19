#include <QCoreApplication>
#include <analizador.h>
#include <string>

using namespace std;
static Analizador analizador;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string Entrada = "";
    QString qtEntrada = "";
    while(!(Entrada.compare("Exit") == 0)){
        cout << "[MIA]@Ejemplo4:~$ ";
        getline(cin,Entrada);
        qtEntrada = QString::fromStdString(Entrada);
        analizador.LeerEntrada(qtEntrada);
        analizador.Analizar();
    }
    return a.exec();
}
