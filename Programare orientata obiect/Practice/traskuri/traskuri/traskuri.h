#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_traskuri.h"

class traskuri : public QMainWindow
{
    Q_OBJECT

public:
    traskuri(QWidget *parent = nullptr);
    ~traskuri();

private:
    Ui::traskuriClass ui;
};
