#include "dashboard.h"
#include "ui_dashboard.h"
#include "accountdetails.h"

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::on_MyAccountButton_clicked()
{
    AccountDetails *accntDetails = new AccountDetails();
    accntDetails->show();
}


