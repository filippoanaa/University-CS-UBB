#include "traskuri.h"
#include <QtWidgets/QApplication>
#include<Repo.h>
#include<Service.h>
#include<GUI.h>
#include<Validator.h>
#include<Teste.h>
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Tests t;
	Repo repo("tasks.txt");
	Validator val;
	Service srv(repo, val);
	GUI gui(srv);
	t.testAll();
	gui.show();
	return a.exec();
}
