#include "simulareapartamente.h"
#include <QtWidgets/QApplication>
#include<Repo.h>
#include<Service.h>
#include<GUI.h>
#include<Teste.h>
#include<iostream>
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TestAll();
	Repo repo{ "apartamente.txt" };
	Service srv{ repo };
	GUI gui{ srv };
	gui.show();
	return a.exec();


}
