#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simulareapartamente.h"

class simulareapartamente : public QMainWindow
{
    Q_OBJECT

public:
    simulareapartamente(QWidget *parent = nullptr);
    ~simulareapartamente();

private:
    Ui::simulareapartamenteClass ui;
};
