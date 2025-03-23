#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tasks.h"

class tasks : public QMainWindow
{
    Q_OBJECT

public:
    tasks(QWidget *parent = nullptr);
    ~tasks();

private:
    Ui::tasksClass ui;
};
