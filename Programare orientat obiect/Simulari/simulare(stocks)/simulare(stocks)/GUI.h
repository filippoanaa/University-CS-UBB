#pragma once
#include<Service.h>
#include<QWidget>
#include<QListWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QProgressBar>
#include<QLabel>
#include<QPushButton>
class GUI :public QWidget
{
private:
	Service& srv;

	QVBoxLayout* mainLy;
	QListWidget* lst;

	QLineEdit* txtId;
	QLineEdit* txtNume;
	QLineEdit* txtPret;
	QHBoxLayout* lyProgress;
	QProgressBar* barMc;
	QLabel* lbl;

	QPushButton* btnStergere;

	//initializeaza gui ul
	void init();

	//incarca datele din fisier
	void loadData(vector<Stock>& stocks);

	//conecteaza componente
	void connect();
public:
	GUI(Service& srv) :srv{ srv } {
		init();
		loadData(srv.getAllStocks());
		connect();
	}


};

