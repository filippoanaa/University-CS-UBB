#include "simulareDeviceuri.h"
#include <QtWidgets/QApplication>
#include<repo.h>
#include<service.h>
#include<ui.h>
#include<teste.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testAll();
    Repo repo{ "devices.txt" };
    Service srv{ repo };
    GUI gui{ srv };
    gui.show();
    return a.exec();
}
