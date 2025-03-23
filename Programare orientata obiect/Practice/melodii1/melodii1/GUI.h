#pragma once
#include<Service.h>
#include<QWidget>
#include<TableModel.h>
#include<QTableView>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QSlider>
#include<QPushButton>
#include<QLabel>
#include<QPainter>
#include<QGroupBox>

class Painter : public QWidget {
private:
	vector<int> ranks;
public:

	explicit Painter(vector<int> ranks) :ranks{ ranks } {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev) override;

};

class GUI : public QWidget
{
private:
	Service& srv;

	QHBoxLayout* mainLy = new QHBoxLayout;
	QTableView* tblV = new QTableView;
	TableModel* model;

	QGroupBox* groupBoxUpdate = new QGroupBox(QString::fromStdString("Update options"));
	QLineEdit* txtNume = new QLineEdit;
	QSlider* sldRank = new QSlider;
	QLabel* lblSlider = new QLabel;

	QPushButton* btnUpdate = new QPushButton{ "Modifica melodie" };
	QPushButton* btnDelete = new QPushButton{"Sterge melodie"};

	Painter* painter;
	QVBoxLayout* lyPaint = new QVBoxLayout;

	void innitGUI();
	void connect();
	void loadData(vector<Melodie> melodii);
public:
	GUI(Service& srv):srv{srv}{
		innitGUI();
		model = new TableModel{ srv.getAllMelodii() };
		tblV->setModel(model);
		connect();
	}

};


