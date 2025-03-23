#include "GUI.h"
#include<QMessageBox>;
void GUI::init()
{
	mainLy = new QVBoxLayout;
	this->setLayout(mainLy);
	lst = new QListWidget;
	mainLy->addWidget(lst);

	txtId = new QLineEdit;
	txtNume = new QLineEdit;
	txtPret = new QLineEdit;
	barMc = new QProgressBar;
	barMc->setMinimum(0);
	barMc->setMaximum(100);

	lyProgress = new QHBoxLayout;
	lbl = new QLabel;


	btnStergere = new QPushButton("Sterge stock");
	mainLy->addWidget(btnStergere);
	mainLy->addLayout(lyProgress);

}

void GUI::loadData(vector<Stock>& stocks)
{
	lst->clear();
	for (const auto& s : stocks) {
		//qDebug() << "Stock ID:" << QString::fromStdString(s.getId()) << "MC:" << s.getMChange();
		QListWidgetItem* it = new  QListWidgetItem;
		it->setText(QString::fromStdString(s.getId() + " " + std::to_string(s.getPret())));
		it->setData(Qt::UserRole, QString::fromStdString(s.getNume()));
		it->setData(Qt::UserRole+1, s.getMChange());
		lst->addItem(it);
		if (s.getMChange() >= 0) {
			it->setBackground(Qt::green);
		}
		else {
			it->setBackground(Qt::red);
		}
	}
}

void GUI::connect()
{
	QObject::connect(lst, &QListWidget::clicked, [&]() {
		auto selectedItems = lst->selectedItems().first()->text().split(" ");
		auto nume = lst->selectedItems().first()->data(Qt::UserRole).toString();
		auto mc = lst->selectedItems().first()->data(Qt::UserRole+1).toInt();
		if (mc > 0) {
			lbl->setText("+");
			barMc->setValue(mc);
		}
		else {
			lbl->setText("-");
			barMc->setValue(0);
		}
		txtId->setText(selectedItems.at(0));
		txtNume->setText(nume);
		txtPret->setText(selectedItems.at(1));
		
		mainLy->addWidget(txtId);
		mainLy->addWidget(txtNume);
		mainLy->addWidget(txtPret);
		lyProgress->addWidget(barMc);
		lyProgress->addWidget(lbl);

		});
	QObject::connect(btnStergere, &QPushButton::clicked, [&]() {
		QMessageBox msg;
		msg.setInformativeText("Vrei sa stergi stockul?");
		msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		int ret = msg.exec();
		switch (ret) {
		case QMessageBox::Yes:
		{
			try {
				string id = txtId->text().toStdString();
				srv.removeStock(id);
				loadData(srv.getAllStocks());
			}
			catch (RepoException&) {
				QMessageBox::information(nullptr, "Info", "Trebuie sa fie continut in qline uri");
			}

		}
		case QMessageBox::No: {
			break;
		}
		default:break;
		}
		});
}
