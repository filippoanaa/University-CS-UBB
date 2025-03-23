#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simulareDeviceuri.h"

class simulareDeviceuri : public QMainWindow
{
    Q_OBJECT

public:
    simulareDeviceuri(QWidget *parent = nullptr);
    ~simulareDeviceuri();

private:
    Ui::simulareDeviceuriClass ui;
};
