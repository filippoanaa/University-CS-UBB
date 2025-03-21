#pragma once
#include<Service.h>
#include<QWidget>
#include<QListWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QLineEdit>
class GUI:public QWidget {
private:
	Service& srv;
	QVBoxLayout* mainLy = new QVBoxLayout;
	QListWidget* lstPr = new QListWidget;
	QListWidget* lstPl = new QListWidget;

	QLineEdit* editNumePl = new QLineEdit;
	QLineEdit* editSocluPl = new QLineEdit;
	QLineEdit* editprePl = new QLineEdit;
	QPushButton* btnAdauga = new QPushButton("Adauga Placa");

	void init();
	void loadData(vector<Procesor>& procesoare, vector<PlacaDeBaza>& placi);
	void connect();
public:
	GUI(Service& srv) :srv{ srv } {
		init();
		loadData(srv.getProcesoare(), srv.getPlaci());
		connect();
	}
};

