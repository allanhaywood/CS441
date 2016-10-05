#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createacctpage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CreateAcctButton_clicked()
{
    CreateAcctPage *creatingAcct =new CreateAcctPage();
    creatingAcct->show();
}
