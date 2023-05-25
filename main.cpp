#include "telaprincipalaluno.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TelaPrincipalAluno w;
    w.show();
    return a.exec();
}
