#include<ui.h>
#include <QDebug>
void GUI::initGui()
{
	setLayout(mainLy);

	mainLy->addWidget(lst);

	QFormLayout* formLy = new QFormLayout;
	formLy->addRow("Tip", detaliiTip);
	formLy->addRow("An", detaliiAn);
	mainLy->addLayout(formLy);

	mainLy->addWidget(btnModel);
	mainLy->addWidget(btnAn);
	mainLy->addWidget(btnNesortat);

}

void GUI::loadData(std::vector<Device> devices)
{
	lst->clear();
	for (const auto& dev : devices) {
		QListWidgetItem* it = new QListWidgetItem;
		it->setData(Qt::UserRole, QVariant::fromValue(dev));
		it->setText(QString::fromStdString(dev.getModel() + " " + dev.getCuloare() + " " + std::to_string(dev.getPret())));
		lst->addItem(it);
		if (dev.getCuloare() == "rosu")
			it->setBackground(Qt::red);
		if (dev.getCuloare() == "albastru")
			it->setBackground(Qt::blue);
		if (dev.getCuloare() == "alb")
			it->setBackground(Qt::white);
		if (dev.getCuloare() == "verde")
			it->setBackground(Qt::green);

	}

}

void GUI::connect()
{
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [this]() {
		if (lst->selectedItems().size() == 0)
			return;
		Device dev = lst->selectedItems()[0]->data(Qt::UserRole).value<Device>();
		detaliiTip->setText(QString::fromStdString(dev.getTip()));
		detaliiAn->setText(QString::fromStdString(std::to_string(dev.getAn())));
		});

	QObject::connect(btnModel, &QPushButton::clicked, [&]() {
		auto all = srv.sorteazaModel();
		loadData(all);
		});
	QObject::connect(btnAn, &QPushButton::clicked, [&]() {
		auto all = srv.sorteazaAn();
		loadData(all);
		});
	QObject::connect(btnNesortat, &QPushButton::clicked, [&]() {
		auto all = srv.getAllDevices();
		loadData(all);
		});

}

