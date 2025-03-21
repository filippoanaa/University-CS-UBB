#include "GUI.h"
#include<QMessageBox>
#include<QPainter>
void GUI::innit()
{
	this->setLayout(mainLy);

	mainLy->addWidget(tblV);
	mainLy->addLayout(lyDr);

	txtId->setPlaceholderText("Id(nu completati pentru adaugare!)");
	lyDr->addWidget(txtId);
	txtTitlu->setPlaceholderText("Titlu");
	lyDr->addWidget(txtTitlu);
	txtArtist->setPlaceholderText("Artist");
	lyDr->addWidget(txtArtist);
	txtGen->setPlaceholderText("Gen");
	lyDr->addWidget(txtGen);
	lyDr->addWidget(btnAdd);
	lyDr->addWidget(btnDel);


}

void GUI::connect()
{
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		string titlu = txtTitlu->text().toStdString();
		string artist = txtArtist->text().toStdString();
		string gen = txtGen->text().toStdString();
		try {
			srv.storeMelodie(titlu, artist, gen);
			loadData(srv.getAllMelodii());
			QMessageBox::information(nullptr, "Info", "Melodie adaugata cu succes!");
		}
		catch (std::exception& e) {
			QMessageBox::warning(nullptr, "warning", e.what());

		}
		});
	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		const auto selectedIndexes = tblV->selectionModel()->selectedIndexes();
		if (selectedIndexes.isEmpty())	return;

		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto i1 = tblV->model()->index(selRow, 0);
		auto val1 = tblV->model()->data(i1, Qt::DisplayRole).toInt();
		txtId->setText(QString::number(val1));
		auto i2 = tblV->model()->index(selRow, 1);
		auto val2 = tblV->model()->data(i2, Qt::DisplayRole).toString();
		txtTitlu->setText(val2);
		auto i3 = tblV->model()->index(selRow, 2);
		auto val3 = tblV->model()->data(i3, Qt::DisplayRole).toString();
		txtArtist->setText(val3);
		auto i4 = tblV->model()->index(selRow, 3);
		auto val4 = tblV->model()->data(i4, Qt::DisplayRole).toString();
		txtGen->setText(val4);
		});
	QObject::connect(btnDel, &QPushButton::clicked, [&]() {
		int id = txtId->text().toInt();
		string titlu = txtTitlu->text().toStdString();
		string artist = txtArtist->text().toStdString();
		string gen = txtGen->text().toStdString();
		srv.removeMelodie(id, titlu, artist, gen);
		loadData(srv.getAllMelodii());
		QMessageBox::information(nullptr, "Info", "Melodie stearsa cu succes!");

		});
}

void GUI::loadData(vector<Melodie>& melodii)
{
	model->setMelodii(melodii);
}

void GUI::paintEvent(QPaintEvent* e)
{
	QPainter p{ this };
	p.setPen(Qt::darkMagenta);
	int pop = 0, rock = 0, folk = 0, disco = 0;
	for (auto& m : srv.getAllMelodii())
	{
		if (m.getGen() == "pop") {
			pop++;
			p.drawEllipse(QPoint(0, 0), pop * 8, pop * 8);
		}
		if (m.getGen() == "folk") {
			folk++;
			p.drawEllipse(QPoint(p.device()->width(), 0), folk * 8, folk * 8);
		}
		if (m.getGen() == "disco") {
			disco++;
			p.drawEllipse(QPoint(0, p.device()->height()), disco * 8, disco * 8);
		}
		if (m.getGen() == "rock") {
			rock++;
			p.drawEllipse(QPoint(p.device()->width(), p.device()->height()), rock * 8, rock * 8);
		}
	}



}
