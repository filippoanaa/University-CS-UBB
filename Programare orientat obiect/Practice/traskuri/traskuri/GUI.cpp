#include "GUI.h"
#include<QMessageBox>
#include<QFormLayout>
#include<sstream>
void GUI::innitGUI()
{
	this->srv.addObserver(this);

	mainLy = new QVBoxLayout;
	setLayout(mainLy);

	tabel = new QTableWidget;
	tabel->setColumnCount(4);
	tabel->setHorizontalHeaderLabels({ "Id", "Descriere", "Programatori", "Stare" });
	mainLy->addWidget(tabel);

	QFormLayout* formLayout = new QFormLayout;
	txtId = new QLineEdit;
	txtDesc = new QLineEdit;
	txtProg = new QLineEdit;
	txtStare = new QLineEdit;

	formLayout->addRow("Id:", txtId);
	formLayout->addRow("Descriere:", txtDesc);
	formLayout->addRow("Programatori:", txtProg);
	formLayout->addRow("Stare:", txtStare);

	mainLy->addLayout(formLayout);

	btnAdd = new QPushButton("Adaugă Task");
	mainLy->addWidget(btnAdd);

	QHBoxLayout* searchLayout = new QHBoxLayout;
	txtCauta = new QLineEdit;
	txtCauta->setPlaceholderText("Programator");
	btnCauta = new QPushButton("Caută task-urile programatorului");

	searchLayout->addWidget(txtCauta);
	searchLayout->addWidget(btnCauta);

	mainLy->addLayout(searchLayout);

}

void GUI::loadData(vector<Task>& tasks)
{
	tabel->clearContents();
	tabel->setRowCount(tasks.size());
	std::sort(tasks.begin(), tasks.end(), [&](const Task& t1, const Task& t2) {
		return t1.getStare() < t2.getStare();
		});
	int lineNo = 0;
	for (auto& t : tasks) {
		tabel->setItem(lineNo, 0, new QTableWidgetItem(QString::number(t.getId())));
		tabel->setItem(lineNo, 1, new QTableWidgetItem(QString::fromStdString(t.getDesc())));
		tabel->setItem(lineNo, 2, new QTableWidgetItem(QString::number(t.getProgramatori().size())));
		tabel->setItem(lineNo, 3, new QTableWidgetItem(QString::fromStdString(t.getStare())));
		lineNo++;
	}
}

void GUI::connect()
{
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		int id = txtId->text().toInt();
		string desc = txtDesc->text().toStdString();
		string prog = txtProg->text().toStdString();
		string stare = txtStare->text().toStdString();
		txtId->clear();
		txtStare->clear();
		txtProg->clear();
		txtDesc->clear();
		vector<string> lst;
		std::stringstream ss(prog);
		string token;
		while (getline(ss, token, ' ')) {
			lst.push_back(token);
		}
		try {
			srv.storeTask(id, desc, lst, stare);
			loadData(srv.getAllTasks());
			QMessageBox::information(nullptr, "Info", "Task adaugat cu succes");
		}
		catch (RepoException& r) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(r.getError()));
		}
		catch (ValException& v) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(v.getErrorMessage()));
		}

		});
	QObject::connect(btnCauta, &QPushButton::clicked, [&]() {
		string pr = txtCauta->text().toStdString();
		try {
			auto tasks = srv.findTasks(pr);
			loadData(tasks);
		}
		catch (RepoException& r) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(r.getError()));
		}
		});
}

void GUI::addWindows()
{
	Window* w1 = new Window(srv, "done");
	Window* w2 = new Window(srv, "inprogress");
	Window* w3 = new Window(srv, "closed");
	w1->show();
	w2->show();
	w3->show();
}

void Window::loadDataWindow(vector<Task> tasks)
{
	lst->clear();
	for (const auto& t : tasks)
		lst->addItem(QString::fromStdString(std::to_string(t.getId()) + " " + t.getDesc() + " " + std::to_string(t.getProgramatori().size()) + " " + t.getStare()));
}

void Window::connectWindow()
{
	connect(btnDone, &QPushButton::clicked, [&]() {
		auto selected = lst->selectedItems().at(0)->text().split(" ");
		int id = selected.at(0).toInt();
		srv.updateStare(id, "done");
		});

	connect(btnInP, &QPushButton::clicked, [&]() {
		auto selected = lst->selectedItems().at(0)->text().split(" ");
		int id = selected.at(0).toInt();
		srv.updateStare(id, "inprogress");
		});
	connect(btnOpen, &QPushButton::clicked, [&]() {
		auto selected = lst->selectedItems().at(0)->text().split(" ");
		int id = selected.at(0).toInt();
		srv.updateStare(id, "closed");
		});
}

void Window::innitWindow()
{
	srv.addObserver(this);
	mainLy = new QVBoxLayout;
	setLayout(mainLy);
	lst = new QListWidget;
	btnDone = new QPushButton("Done");
	btnInP = new QPushButton("In progress");
	btnOpen = new QPushButton("Closed");
	mainLy->addWidget(lst);
	mainLy->addWidget(btnDone);
	mainLy->addWidget(btnInP);
	mainLy->addWidget(btnOpen);
	this->setWindowTitle(QString::fromStdString(str));
}
