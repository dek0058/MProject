#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MProjectServer.h"

class MProjectServer : public QMainWindow
{
    Q_OBJECT

public:
    MProjectServer(QWidget *parent = Q_NULLPTR);

private:
    Ui::MProjectServerClass ui;
};
