#include "dashboard.h"
#include "ui_dashboard.h"
#include "adminpage.h"
#include "accountdetails.h"
#include "about.h"


Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); //set stacked widget to home screen at start
    //TODO: only show admin button if user account has admin rights
    ui->adminButton->setVisible(true);
    ui->splitter_popularPage->setSizes({500, 1}); // preset the splitter to make search side bigger initially
    ui->splitter_SearchResultsPage->setSizes({500, 1});
    ui->splitter_watchedMediaPage->setSizes({500, 1});
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::hideAdminButton()
{
    ui->adminButton->hide();
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

void Dashboard::on_AboutButton_clicked()
{
    if(AboutPage == NULL)
    {
        AboutPage= new About();
    }
    AboutPage->show();
    AboutPage->raise();
}
