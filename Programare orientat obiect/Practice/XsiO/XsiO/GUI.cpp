#include "GUI.h"
#include<QMessageBox>
#include<QGroupBox>
QVBoxLayout* GUI::createBoard(int dim, const string& board)
{
	QVBoxLayout* column = new QVBoxLayout;
	int cnt = 0;
	for (int i = 0; i < dim; i++) {
		QHBoxLayout* line = new QHBoxLayout;
		for (int j = 0; j < dim; j++) {
			char s = board[cnt];
			if (s == '-')
				s = ' ';
			QPushButton* btn = new QPushButton(QChar(s));
			
			line->addWidget(btn);
			if (s == ' ') {
				QObject::connect(btn, &QPushButton::clicked, [this, cnt, btn]() {
					char gamer = txtGamer->text().toStdString()[0];
					auto board = txtBoard->text();
					board[cnt] = gamer;
					txtBoard->setText(board);
					btn->setText(QChar(gamer));
					if (gamer == 'X') {
						txtGamer->setText("O");
						srv.update(txtId->text().toInt(), txtDim->text().toInt(), txtBoard->text().toStdString(), txtGamer->text().toStdString()[0],"inprogress");

					}
					else {
						txtGamer->setText("X");
						srv.update(txtId->text().toInt(), txtDim->text().toInt(), txtBoard->text().toStdString(), txtGamer->text().toStdString()[0],"inprogress");
					}
					loadData(srv.getAllGames());
					});
			}
			cnt++;
		}
		column->addLayout(line);
	
	}
	return column;
}
void GUI::connect()
{
	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		auto selectedIndexes = tblV->selectionModel()->selectedIndexes();
		if (selectedIndexes.isEmpty())	return;  

		auto selrOW = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto c0i = tblV->model()->index(selrOW, 0);
		auto v0 = tblV->model()->data(c0i, Qt::DisplayRole).toString();
		txtId->setText(v0);
		auto c1i = tblV->model()->index(selrOW, 1);
		auto v1 = tblV->model()->data(c1i, Qt::DisplayRole).toString();
		txtDim->setText(v1);
		auto c2i = tblV->model()->index(selrOW, 2);
		auto v2 = tblV->model()->data(c2i, Qt::DisplayRole).toString();
		txtBoard->setText(v2);
		auto c3i = tblV->model()->index(selrOW, 3);
		auto v3 = tblV->model()->data(c3i, Qt::DisplayRole).toString();
		txtGamer->setText(v3);
		auto c4i = tblV->model()->index(selrOW, 4);
		auto v4 = tblV->model()->data(c4i, Qt::DisplayRole).toString();
		txtStatus->setText(v4);

		clearLayout(boardLy);
		boardLy->addLayout(createBoard(txtDim->text().toInt(), txtBoard->text().toStdString()));
		});
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		auto id = txtId->text().toInt();
		auto dim = txtDim->text().toInt();
		auto board = txtBoard->text().toStdString();
		auto gamer = txtGamer->text().toStdString()[0];
		try {
			srv.addGame(id, dim, board, gamer);
			loadData(srv.getAllGames());
			QMessageBox::information(this, "Info", "Game added successfully!");

		}
		catch (ValException& v) {
			QMessageBox::warning(nullptr, "Info",QString::fromStdString(v.getErro()));
		}
		catch (RepoException& re) {
			QMessageBox::warning(nullptr, "Info", QString::fromStdString(re.getError()));
		}
		});

	QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
		int id = txtId->text().toInt();
		int dim = txtDim->text().toInt();
		string board = txtBoard->text().toStdString();
		char gamer = txtGamer->text().toStdString()[0];
		string stare = txtStatus->text().toStdString();
		try {
			srv.update(id, dim, board, gamer, stare);
			loadData(srv.getAllGames());
			QMessageBox::information(this, "Info", "Game updated successfully!");
		}
		catch (RepoException & re) {
			QMessageBox::warning(nullptr, "Info", QString::fromStdString(re.getError()));
		}
		catch (ValException& ve) {
			QMessageBox::warning(nullptr, "Info", QString::fromStdString(ve.getErro()));
		}
		});
}

void GUI::loadData(vector<Game>& jocuri)
{
	model->setGames(jocuri);
	tblV->resizeColumnsToContents();
	tblV->resizeRowsToContents();
}

void GUI::innitGUI()
{
	mainLy = new QVBoxLayout;
	this->setLayout(mainLy);
	tblV = new QTableView;

	secondLy = new QHBoxLayout;
	rightLy = new QVBoxLayout;
	secondLy->addWidget(tblV);
	secondLy->addLayout(rightLy);
	mainLy->addLayout(secondLy);

	// GroupBox pentru Inputuri
	QGroupBox* inputBox = new QGroupBox("Game Details");
	QVBoxLayout* inputLy = new QVBoxLayout;
	inputBox->setLayout(inputLy);

	txtId = new QLineEdit;
	txtId->setPlaceholderText("Id");
	txtDim = new QLineEdit;
	txtDim->setPlaceholderText("Size");
	txtBoard = new QLineEdit;
	txtBoard->setPlaceholderText("Board");
	txtGamer = new QLineEdit;
	txtGamer->setPlaceholderText("Gamer");
	txtStatus = new QLineEdit;
	txtStatus->setPlaceholderText("Status(only for update)");

	// Adăugăm widget-uri în layout-ul inputBox
	inputLy->addWidget(txtId);
	inputLy->addWidget(txtDim);
	inputLy->addWidget(txtBoard);
	inputLy->addWidget(txtGamer);
	inputLy->addWidget(txtStatus);

	// Adăugăm GroupBox la rightLy
	rightLy->addWidget(inputBox);

	// Adăugăm butoane într-un QHBoxLayout
	QHBoxLayout* buttonLy = new QHBoxLayout;
	btnAdd = new QPushButton("Add");
	btnUpdate = new QPushButton("Update game");

	buttonLy->addWidget(btnAdd);
	buttonLy->addWidget(btnUpdate);
	rightLy->addLayout(buttonLy);

	// Adăugăm spațiu între elemente pentru o mai bună prezentare
	rightLy->setSpacing(10);
	rightLy->setContentsMargins(10, 10, 10, 10);

	boardLy = new QVBoxLayout;
	mainLy->addLayout(boardLy);

	this->setMinimumSize(1000, 400);
}

void GUI::clearLayout(QLayout* layout)
{
	QLayoutItem* item;
	while ((item = layout->takeAt(0)) != nullptr) {
		if (QWidget* widget = item->widget()) {
			widget->deleteLater();
		}
		if (QLayout* childLayout = item->layout()) {
			clearLayout(childLayout);
		}
		delete item;
	}
}
