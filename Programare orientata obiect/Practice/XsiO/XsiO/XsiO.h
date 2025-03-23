#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XsiO.h"

class XsiO : public QMainWindow
{
    Q_OBJECT

public:
    XsiO(QWidget *parent = nullptr);
    ~XsiO();

private:
    Ui::XsiOClass ui;
};
