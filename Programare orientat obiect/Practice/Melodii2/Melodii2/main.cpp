#include "Melodii2.h"
#include <QtWidgets/QApplication>
#include<Repo.h>
#include<Service.h>
#include<Validator.h>
#include<GUI.h>
#include<Teste.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Teste t;
    t.testAll();
    Repo repo{ "melodii.txt" };
    Service srv{ repo };
    GUI gui{ srv };
    gui.show();
    return a.exec();
}
