#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //set stacked widget to home screen at start
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::on_myAccountButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Dashboard::on_homeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Dashboard::on_popularButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Dashboard::on_watchedButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void Dashboard::on_searchButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
