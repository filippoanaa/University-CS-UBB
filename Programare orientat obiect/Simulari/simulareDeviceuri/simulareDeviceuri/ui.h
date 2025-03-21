
#include<service.h>
#include<QListWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QlineEdit>
#include <QFormLayout>
#include<QLabel>
#include<QPushButton>
class GUI :public QWidget {
private:
	Service& srv;
	void initGui();
	void loadData(std::vector<Device> devices);
	void connect();
	void coloreaza(const Device& dev);
public:
	GUI(Service& srv) :srv{ srv } {
		initGui();
		loadData(srv.getAllDevices());
		connect();

	};
	QVBoxLayout* mainLy = new QVBoxLayout;
	QListWidget* lst = new QListWidget;

	QLineEdit* detaliiTip = new QLineEdit;
	QLineEdit* detaliiAn = new QLineEdit;

	QPushButton* btnModel = new QPushButton{ "Sorteaza dupa model" };
	QPushButton* btnAn = new QPushButton{ "Sorteaza dupa an" };
	QPushButton* btnNesortat = new QPushButton{ "Nesortat" };

};