#pragma once
#include<Service.h>
#include<QVBoxLayout>
#include<QTableWidget>
#include<QWidget>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include<QListWidget>

class GUI : public QWidget, public Observer
{
private:
	Service& srv;
	QVBoxLayout* mainLy;
	QTableWidget* tabel;

	QLineEdit* txtId;
	QLineEdit* txtDesc;
	QLineEdit* txtProg;
	QLineEdit* txtStare;
	QPushButton* btnAdd;

	QLineEdit* txtCauta;
	QPushButton* btnCauta;

	void innitGUI();
	void loadData(vector<Task>& tasks);
	void connect();
	void addWindows();
	void update() override {
		loadData(srv.getAllTasks());
	}
public:
	GUI(Service& srv) : srv{ srv } {
		innitGUI();
		loadData(srv.getAllTasks());
		connect();
		addWindows();
	}

};

class Window : public QWidget, public Observer {
private:
	Service& srv;
	string str;
	QVBoxLayout* mainLy;
	QListWidget* lst;
	QPushButton* btnOpen;
	QPushButton* btnDone;
	QPushButton* btnInP;

	void loadDataWindow(vector<Task> tasks);
	void connectWindow();
	void innitWindow();
	void update() override {
		loadDataWindow(srv.findStare(str));
	}
public:
	Window(Service& svr, string str) :srv{ svr }, str{ str } {
		innitWindow();
		loadDataWindow(srv.findStare(str));
		connectWindow();
	}


};