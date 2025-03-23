#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_melodii1.h"

class melodii1 : public QMainWindow
{
    Q_OBJECT

public:
    melodii1(QWidget *parent = nullptr);
    ~melodii1();

private:
    Ui::melodii1Class ui;
};
