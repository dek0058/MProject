#pragma once
#include "GlobalDefine.h"

#include <QtWidgets/QMainWindow>
#include "ui_MProjectServer.h"

class MProjectServer : public QMainWindow
{
    Q_OBJECT

public:
    MProjectServer(QWidget *parent = Q_NULLPTR);

    static QListWidget* List_Widget;

private:
    void OnInitialize();

    // Initailize
    void Initailize_Manager();
    void Initailize_UI();
    void Initailize_Bind();

private slots:
    void OnClick(bool checked);

private:
    Ui::MProjectServerClass ui;
};

