#include "GUI.h"
#include<QMessageBox>
void GUI::init()
{
	this->setLayout(mainLy);
	mainLy->addWidget(lst);

	mainLy->addWidget(btnDel);

	supraf1->setPlaceholderText("Suprafata minima");
	supraf2->setPlaceholderText("Suprafata maxima");
	mainLy->addWidget(supraf1);
	mainLy->addWidget(supraf2);
	mainLy->addWidget(btnFiltrareSupraf);

	pret1->setPlaceholderText("Pret minim");
	pret2->setPlaceholderText("Pret maxim");
	mainLy->addWidget(pret1);
	mainLy->addWidget(pret2);
	mainLy->addWidget(btnFiltrarePret);

}

void GUI::loadData(vector<Apartament>& aps)
{
	lst->clear();
	for (const auto& ap : aps) {
		QListWidgetItem* it = new QListWidgetItem;
		QString strada = QString::fromStdString(ap.getStrada());
		QString supraf = QString::fromStdString(std::to_string(ap.getSuprafata()));
		QString pret = QString::fromStdString(std::to_string(ap.getPret()));
		it->setText(strada + +" " + supraf + " " + pret);
		lst->addItem(it);

	}
}

void GUI::connect()
{
	QObject::connect(btnDel, &QPushButton::clicked, [&]() {
		auto selection = lst->selectedItems();
		if (selection.empty()) {
			QMessageBox::warning(nullptr, "Warning", "Selecteaza un obiect din lista");
			return;
		}

		string strada = lst->selectedItems().first()->text().split(" ").at(0).toStdString();
		int supraf = lst->selectedItems().first()->text().split(" ").at(1).toInt();
		int pret = lst->selectedItems().first()->text().split(" ").at(2).toInt();
		srv.deleteAp(strada, supraf, pret);
		loadData(srv.getAllAp());

		});

	QObject::connect(btnFiltrareSupraf, &QPushButton::clicked, [&]() {
		auto min = supraf1->text();
		auto max = supraf2->text();
		if (min.isEmpty() || max.isEmpty()) {
			QMessageBox::warning(nullptr, "Warning", "Adauga suprafata minima si maxima");
			return;
		}
		auto filtrate = srv.filtrare(min.toInt(), max.toInt());
		loadData(filtrate);
		});

	QObject::connect(btnFiltrarePret, &QPushButton::clicked, [&]() {
		auto min = supraf1->text();
		auto max = supraf2->text();
		if (min.isEmpty() || max.isEmpty()) {
			QMessageBox::warning(nullptr, "Warning", "Adauga pretul minim si maxim");
			return;
		}
		auto filtrate = srv.filtrarePret(min.toInt(), max.toInt());
		if (supraf1->text() != "" && supraf2->text() != "") {
			int min = supraf1->text().toInt();
			int max = supraf2->text().toInt();
			filtrate = srv.filtrare(min, max);
		}
		loadData(filtrate);
		});
}
