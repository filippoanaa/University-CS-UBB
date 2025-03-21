#include "GUI.h"
#include<QMessageBox>
void GUI::init()
{
	this->setLayout(mainLy);

	mainLy->addWidget(lstPr);
	mainLy->addWidget(lstPl);

	editNumePl->setPlaceholderText("Nume");
	editSocluPl->setPlaceholderText("Soclu");
	editprePl->setPlaceholderText("Pret");
	mainLy->addWidget(editNumePl);
	mainLy->addWidget(editSocluPl);
	mainLy->addWidget(editprePl);
	mainLy->addWidget(btnAdauga);

}

void GUI::loadData(vector<Procesor>& procesoare, vector<PlacaDeBaza>& placi)
{
	lstPl->clear();
	lstPr->clear();
	for (const auto& pr : procesoare) {
		QListWidgetItem* it = new QListWidgetItem;
		it->setText(QString::fromStdString(pr.getNumeProcesor() + " " + std::to_string(pr.getNrT())));
		lstPr->addItem(it);
	}
	for (const auto& pl : placi) {
		QListWidgetItem* it = new QListWidgetItem;
		it->setText(QString::fromStdString(pl.getNumePlaca()));
		lstPl->addItem(it);
	}
}

void GUI::connect()
{
	QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
		try {
			string nume = editNumePl->text().toStdString();
			string soclu = editSocluPl->text().toStdString();
			int pret = editprePl->text().toInt();
			editNumePl->clear();
			editprePl->clear();
			editSocluPl->clear();
			srv.adaugaPlaca(nume, soclu, pret);
			loadData(srv.getProcesoare(), srv.getPlaci());
		}
		catch (RepoException& e) {
			QMessageBox::warning(nullptr, "Info", QString::fromStdString(e.getError()));
		}
		});

	QObject::connect(lstPr, &QListWidget::itemClicked, [&]() {
		QList<QListWidgetItem*> selectedItemsPr = lstPr->selectedItems();
		QList<QListWidgetItem*> selectedItemsPl = lstPl->selectedItems();

		if (selectedItemsPr.size() > 0)
		{
			string numePr = selectedItemsPr.first()->text().split(" ").at(0).toStdString();
			auto pr = srv.findProcesor(numePr);

			//verifica daca sunt placi selectate 
			if (selectedItemsPl.size() > 0)
			{
				string numePl = selectedItemsPl.first()->text().toStdString();
				try {
					auto placa = srv.findPlaca(numePl);
					int pretTotal = placa.getPretPlaca() + pr.getPretProceor();
					QMessageBox::information(nullptr, "Info", "Pret total: " + QString::fromStdString(std::to_string(pretTotal)));
				}
				catch (const std::exception& e) {
					QMessageBox::warning(nullptr, "Info", QString::fromStdString(e.what()));
				}
			}
			else
			{
				// daca nu sunt selectate placi, executa filtrarea
				auto filtrare = srv.filtrare(pr.getSocluProcesor());
				QMessageBox::information(nullptr, "Info", "S-a realizat filtrarea");
				loadData(srv.getProcesoare(), filtrare);
			}

			// Dezactiveaza selectia pentru liste
			lstPr->clearSelection();
			lstPl->clearSelection();
		}
		else
			QMessageBox::warning(nullptr, "Info", "Selectati un procesor!");
		});

	QObject::connect(lstPl, &QListWidget::itemClicked, [&]() {
		QList<QListWidgetItem*> selectedItemsPl = lstPl->selectedItems();
		QList<QListWidgetItem*> selectedItemsPr = lstPr->selectedItems();

		if (selectedItemsPl.size() > 0 && selectedItemsPr.size() > 0)
		{
			string numePl = selectedItemsPl.first()->text().toStdString();
			string numePr = selectedItemsPr.first()->text().split(" ").at(0).toStdString();

			try {
				auto placa = srv.findPlaca(numePl);
				auto procesor = srv.findProcesor(numePr);
				int pretTotal = placa.getPretPlaca() + procesor.getPretProceor();
				QMessageBox::information(nullptr, "Info", "Pret total: " + QString::fromStdString(std::to_string(pretTotal)));
			}
			catch (const std::exception& e) {
				QMessageBox::warning(nullptr, "Info", QString::fromStdString(e.what()));
			}
			lstPl->clearSelection();
		}
		});
}

