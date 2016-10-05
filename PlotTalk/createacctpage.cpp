#include "createacctpage.h"
#include "ui_createacctpage.h"

CreateAcctPage::CreateAcctPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAcctPage)
{
    ui->setupUi(this);
}

CreateAcctPage::~CreateAcctPage()
{
    delete ui;
}
