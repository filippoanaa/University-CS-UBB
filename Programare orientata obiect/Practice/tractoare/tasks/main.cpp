#include "tasks.h"
#include <QtWidgets/QApplication>
#include<Repo.h>
#include<Service.h>
#include<GUI.h>
#include<Validator.h>
#include<teste.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Teste t;
    t.testAll();
    Repo repo{ "tractoare.txt" };
    Validator val;
    Service srv{ repo,val };
    GUI gui{ srv };
    gui.show();
    return a.exec();
}
