#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simularePC.h"

class simularePC : public QMainWindow
{
    Q_OBJECT

public:
    simularePC(QWidget *parent = nullptr);
    ~simularePC();

private:
    Ui::simularePCClass ui;
};
