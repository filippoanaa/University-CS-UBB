#pragma once
#include <QWidget>
#include<QVBoxLayout>
#include<TableView.h>
#include<qtableview.h>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>
#include<Service.h>
#include<QPainter>
#include<QWidget>

class Painter : public QWidget {
	Q_OBJECT
private:
	int id, nrRoti;
	vector<QRect> circles;
public:
	explicit Painter(int id, int nrRoti) :id{ id }, nrRoti{ nrRoti } {
		this->repaint();
	};
	void paintEvent(QPaintEvent* ev) override;
	void mousePressEvent(QMouseEvent* event) override;
signals:
	void decrementeazaRoti(int id, int newNrRoti);
};

class GUI : public QWidget
{
private:
	Service& srv;
	QVBoxLayout* mainLy;
	Table* tabel;
	QTableView* tabelV;

	QLineEdit* txtId;
	QLineEdit* txtDenumire;
	QLineEdit* txtTip;
	QLineEdit* txtRoti;
	QPushButton* btnAdd;

	QComboBox* box;

	Painter* painter;
	QVBoxLayout* lyPaint = new QVBoxLayout;

	void connect();
	void innit();
	void loadData(vector<Tractor>& tractoare);
	void updateComboBox();

public:
	GUI(Service& srv) :srv{ srv } {
		innit();
		tabel = new Table{ srv.getAllTractoare() };
		tabelV->setModel(tabel);
		loadData(srv.getAllTractoare());
		connect();
	}

};
