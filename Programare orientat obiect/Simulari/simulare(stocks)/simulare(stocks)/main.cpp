#include "simularestocks.h"
#include <QtWidgets/QApplication>
#include<Repo.h>
#include<Service.h>
#include<GUI.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo{ "stocks.txt" };
    Service srv{ repo };
    GUI gui{ srv };
    gui.show();
    return a.exec();
}
