#pragma once
#include<TableModel.h>
#include<Service.h>
#include<QWidget>
#include<QVBoxLayout>
#include<QTableView>
#include<QLineEdit>
#include<QPushButton>
class GUI:public QWidget
{
private:
	Service& srv;

	QVBoxLayout* mainLy;
	QHBoxLayout* secondLy;
	QVBoxLayout* rightLy;
	QTableView* tblV;
	TableModel* model;

	QLineEdit* txtDim;
	QLineEdit* txtId;
	QLineEdit* txtGamer;
	QLineEdit* txtBoard;
	QLineEdit* txtStatus;

	QPushButton* btnAdd;

	QPushButton* btnUpdate;

	QVBoxLayout* boardLy;
	QVBoxLayout* createBoard(int dim, const string& board);
	void connect();
	void loadData(vector<Game>& games);
	void innitGUI();
	void clearLayout(QLayout* layout);



public:
	GUI(Service& srv) :srv{ srv } {
		innitGUI();
		model = new TableModel{ srv.getAllGames() };
		tblV->setModel(model);
		connect();
	}

};

