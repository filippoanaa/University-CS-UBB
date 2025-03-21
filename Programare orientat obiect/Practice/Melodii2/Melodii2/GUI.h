#pragma once
#include<Service.h>
#include<QWidget>
#include<TableModel.h>
#include<QTableView>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QPushButton>
class GUI : public QWidget
{
private:
	Service& srv;

	QHBoxLayout* mainLy = new QHBoxLayout;
	QVBoxLayout* lyDr = new QVBoxLayout;
	QTableView* tblV = new QTableView;
	TableModel* model;

	QLineEdit* txtId = new QLineEdit;
	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtArtist = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QPushButton* btnAdd = new QPushButton{ "Adauga melodie" };

	QPushButton* btnDel = new QPushButton{ "Sterge melodie" };

	void innit();
	void connect();
	void loadData(vector<Melodie>& melodii);
	void paintEvent(QPaintEvent* e) override;
public:
	GUI(Service srv) : srv{ srv } {
		innit();
		model = new TableModel{ srv.getAllMelodii() };
		tblV->setModel(model);
		connect();
		loadData(srv.getAllMelodii());
		repaint();
	}
};

