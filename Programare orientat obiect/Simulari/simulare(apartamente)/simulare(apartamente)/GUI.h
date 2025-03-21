#pragma once
#include<Service.h>
#include<QWidget>
#include<QVBoxLayout>
#include<QListWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QCheckBox>
class GUI :public QWidget {
private:
	Service& srv;

	QVBoxLayout* mainLy = new QVBoxLayout;
	QListWidget* lst = new QListWidget;

	QPushButton* btnDel = new QPushButton{ "Sterge" };

	QLineEdit* supraf1 = new QLineEdit;
	QLineEdit* supraf2 = new QLineEdit;
	QPushButton* btnFiltrareSupraf = new QPushButton{ "Filtreaza dupa suprafata" };

	QLineEdit* pret1 = new QLineEdit;
	QLineEdit* pret2 = new QLineEdit;
	QPushButton* btnFiltrarePret = new QPushButton{ "Filtreaza dupa pret" };


	void init();
	void loadData(vector<Apartament>& aps);
	void connect();

public:
	GUI(Service& srv) :srv{ srv } {
		init();
		loadData(srv.getAllAp());
		connect();
	}

};

