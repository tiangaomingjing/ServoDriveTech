#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabletest.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbTestManager = new DBManager("E:/Working/New/build/debug/resource/database/Version/", "root", "");

    connect(ui->logButton, SIGNAL(clicked()), this, SLOT(onActionLogButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbTestManager;
}

void MainWindow::onActionLogButtonClicked() {
    QString role = getUserRole();
    QString psw = ui->lineEdit->text();
    if (dbTestManager->checkRole(role, psw)) {
        tableTest *tableDialog = new tableTest(this, role, dbTestManager);
        tableDialog->exec();
        delete tableDialog;
    }
}

QString MainWindow::getUserRole() {
    if (ui->PButton->isChecked()) {
        return "P";
    } else if (ui->FButton->isChecked()) {
        return "F";
    } else if (ui->VButton->isChecked()) {
        return "V";
    } else {
        return "C";
    }
}
