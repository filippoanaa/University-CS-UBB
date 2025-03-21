#include "GUI.h"
#include<QMessageBox>
#include<qdebug.h>
#include<QMouseEvent>
void GUI::innit() {
	mainLy = new QVBoxLayout;
	this->setLayout(mainLy);

	tabelV = new QTableView;
	tabelV->setFixedSize(400, 300);
	mainLy->addWidget(tabelV);

	QHBoxLayout* formLy = new QHBoxLayout;
	txtId = new QLineEdit;
	txtId->setPlaceholderText("Id");
	txtDenumire = new QLineEdit;
	txtDenumire->setPlaceholderText("Denumire");
	txtTip = new QLineEdit;
	txtTip->setPlaceholderText("Tip");
	txtRoti = new QLineEdit;
	txtRoti->setPlaceholderText("Numar roti");
	btnAdd = new QPushButton("Adauga tractor");

	formLy->addWidget(txtId);
	formLy->addWidget(txtDenumire);
	formLy->addWidget(txtTip);
	formLy->addWidget(txtRoti);
	formLy->addWidget(btnAdd);

	mainLy->addLayout(formLy);

	box = new QComboBox;
	box->setDuplicatesEnabled(false);
	updateComboBox();
	mainLy->addWidget(box);

	lyPaint = new QVBoxLayout;
	mainLy->addLayout(lyPaint);

}

void GUI::loadData(vector<Tractor>& tractoare) {
	tabel->setTractoare(tractoare);
}

void GUI::updateComboBox() {
	box->clear();
	for (const auto& tip : srv.tipuriDistincte()) {
		box->addItem(QString::fromStdString(tip));
	}
}


void GUI::connect() {
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		auto id = txtId->text().toInt();
		auto denumire = txtDenumire->text().toStdString();
		auto tip = txtTip->text().toStdString();
		auto roti = txtRoti->text().toInt();
		txtId->clear();
		txtDenumire->clear();
		txtRoti->clear();
		txtTip->clear();
		try {
			srv.adaugaTractor(id, denumire, tip, roti);

			QMessageBox::information(this, "Info", "Tractor adaugat cu succes!");
		}
		catch (RepoExceptions& er) {
			QMessageBox::warning(this, "Invalid Data", QString::fromStdString(er.getError()));
		}
		catch (ValException& e) {
			QMessageBox::warning(this, "Invalid Data", QString::fromStdString(e.getErrors()));
		}
		loadData(srv.getAllTractoare());
		updateComboBox();
		});

	QObject::connect(box, &QComboBox::currentTextChanged, this, [&](const QString& text) {
		tabel->setTipFiltru(text.toStdString());
		});

	QObject::connect(tabelV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tabelV->selectionModel()->selectedIndexes().empty()) {
			QMessageBox::warning(nullptr, "Warning", "selecteaza din tabel!");
			return;
		}
		int selRow = tabelV->selectionModel()->selectedIndexes().at(0).row();
		auto celId = tabelV->model()->index(selRow, 0);
		auto id = tabelV->model()->data(celId, Qt::DisplayRole).toString();
		auto celnrRoti = tabelV->model()->index(selRow, 3);
		auto nrRoti = tabelV->model()->data(celnrRoti, Qt::DisplayRole).toString();

		txtId->setText(id);
		txtRoti->setText(nrRoti);

		if (painter) {
			lyPaint->removeWidget(painter);
			painter->deleteLater();  
			painter = nullptr;
		}

		painter = new Painter(id.toInt(), nrRoti.toInt());
		painter->setFixedSize(800, 100);
		lyPaint->addWidget(painter);
		mainLy->addWidget(painter);
		QObject::disconnect(painter, nullptr, this, nullptr);

		QObject::connect(painter, &Painter::decrementeazaRoti, this, [this](int id, int newNrRoti) {
			srv.updateNrRoti(id);
			loadData(srv.getAllTractoare());
			});
		});
}


void Painter::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen(Qt::black, 3);
	painter.setPen(pen);

	circles.clear();
	for (int i = 0; i < nrRoti; ++i) {
		QRect circle(50 + i * 60, height() /2 - 30, 60, 60); 
		painter.drawEllipse(circle);
		circles.push_back(circle);
	}

}

void Painter::mousePressEvent(QMouseEvent* event)
{
	int radius = 15;
	for (int i = 0; i < nrRoti; ++i) {
		int x = (i + 1) * (2 * radius) + 10;
		int y = this->height() / 2;
		QRect circleRect(x - radius, y - radius, 2 * radius, 2 * radius);
		if (circleRect.contains(event->pos())) {
			nrRoti -= 2;
			if (nrRoti < 0) nrRoti = 0;
			emit decrementeazaRoti(id, nrRoti); // Emit the signal with the updated number of wheels
			repaint();
			break;
		}
	}
}
