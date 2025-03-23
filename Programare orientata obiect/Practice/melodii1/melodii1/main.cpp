#include "melodii1.h"
#include <QtWidgets/QApplication>
#include<Repo.h>
#include<Service.h>
#include<GUI.h>
#include<Tests.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tests t;
    t.testAll();
    Repo repo{ "melodii.txt" };
    Service srv{ repo };
    GUI gui{ srv };
    gui.show();
    return a.exec();
}
