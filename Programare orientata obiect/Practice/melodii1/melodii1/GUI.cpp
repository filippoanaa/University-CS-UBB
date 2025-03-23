#include "GUI.h"
#include<QMessageBox>
void GUI::innitGUI()
{
	setLayout(mainLy);
	mainLy->addWidget(tblV);

	auto lyVertical = new QVBoxLayout;

	auto lyUpdate = new QVBoxLayout;
	groupBoxUpdate->setLayout(lyUpdate);
	txtNume->setPlaceholderText("Nume");
	sldRank->setRange(0, 10);
	lyUpdate->addWidget(txtNume);
	lyUpdate->addWidget(sldRank);
	lyUpdate->addWidget(lblSlider);
	lyUpdate->addWidget(btnUpdate);
	lyVertical->addLayout(lyUpdate);
	lyVertical->addWidget(groupBoxUpdate);

	lyVertical->addWidget(btnDelete);
	mainLy->addLayout(lyVertical);

	painter = new Painter{ srv.frecventaRankuri() };
	painter->setFixedSize(150, 200);  // Setează o dimensiune fixă pentru widget-ul de desenat

	lyPaint->addWidget(painter);
	mainLy->addLayout(lyPaint);


}

void GUI::connect()
{
	QObject::connect(sldRank, &QSlider::valueChanged, [this]() {
		lblSlider->setText(QString::number(sldRank->value()));
		});
	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		const auto selectedIndexes = tblV->selectionModel()->selectedIndexes();
		if (selectedIndexes.isEmpty())	return;

		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto cel1Ind = tblV->model()->index(selRow, 1);
		auto valcel1 = tblV->model()->data(cel1Ind, Qt::DisplayRole).toString();
		auto cel3Ind = tblV->model()->index(selRow, 3);
		auto valcel3 = tblV->model()->data(cel3Ind, Qt::DisplayRole).toInt();

		txtNume->setText(valcel1);
		sldRank->setValue(valcel3);
		painter->repaint();
		});
	QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
		if (tblV->selectionModel()->selectedIndexes().empty()) {
			QMessageBox::warning(nullptr, "Warning", "selecteaza din tabel!");
			return;
		}
		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Ind = tblV->model()->index(selRow, 0);
		int id = tblV->model()->data(cel0Ind, Qt::DisplayRole()).toInt();
		string nume = txtNume->text().toStdString();
		int rank = lblSlider->text().toInt();
		try {
			srv.updateMelodie(id, nume, rank);
			QMessageBox::information(this, "Info", "Update realizat cu succes!");
			loadData(srv.getAllMelodii());
			painter->repaint();
		}
		catch (std::exception& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});
	QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
		if (tblV->selectionModel()->selectedIndexes().empty()) {
			QMessageBox::warning(nullptr, "Warning", "selecteaza din tabel!");
			return;
		}
		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto indexId = tblV->model()->index(selRow, 0);
		int id = tblV->model()->data(indexId, Qt::DisplayRole()).toInt();
		try {
			srv.deleteMelodie(id);
			QMessageBox::information(this, "Info", "Melodie stearsa cu succes!");
			loadData(srv.getAllMelodii());
			painter->repaint();
		}
		catch (std::exception& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		});
}

void GUI::loadData(vector<Melodie> melodii)
{
	model->setMelodii(melodii);
}

//void GUI::paintEvent(QPaintEvent* e)
//{
//	QPainter painter{ this };
//	QPen pen(Qt::black);
//	pen.setWidth(5); // Seteaza grosimea liniei
//	painter.setPen(pen);
//	vector<int> ranks(11, 0);
//	for (int i = 0; i < srv.getAllMelodii().size(); i++) {
//		int rank = srv.getAllMelodii()[i].getRank();
//		ranks[rank] += rank;
//	}
//	int rank = 0;
//	for (auto& c : ranks) {
//		int x = (rank + 1) * 10;
//		painter.drawLine(x,painter.device()->height(), x, painter.device()->height() - c *10);
//		rank++;
//	}
//}

void Painter::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };
	QPen pen(Qt::black); 
	pen.setWidth(6);
	p.setPen(pen);
	int rank = 0;
	for (auto& c : ranks) {
		int x = (rank + 1) * 10;
		p.drawLine(x, p.device()->height(), x, p.device()->height() - c * 10);
		rank++;
	}
}
