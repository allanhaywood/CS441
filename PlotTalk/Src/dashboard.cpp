#include "dashboard.h"
#include "ui_dashboard.h"
#include "adminpage.h"
#include "accountdetails.h"


Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //set stacked widget to home screen at start
    //TODO: only show admin button if user account has admin rights
    ui->adminButton->setVisible(true);

}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::on_myAccountButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    AccountDetails *accntDetails = new AccountDetails();
	accntDetails->show();
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

void Dashboard::on_adminButton_clicked()
{
    if (adminWindow == NULL) //ensure that only one admin window can be created
    {
        adminWindow = new AdminPage();
    }
    adminWindow->show();
    adminWindow->raise();
}
