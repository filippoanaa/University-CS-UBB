#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simularestocks.h"

class simularestocks : public QMainWindow
{
	Q_OBJECT

public:
	simularestocks(QWidget* parent = nullptr);
	~simularestocks();

private:
	Ui::simularestocksClass ui;
};
