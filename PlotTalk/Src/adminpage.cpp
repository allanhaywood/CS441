#include "adminpage.h"
#include "ui_adminpage.h"
#include <QMessageBox>

AdminPage::AdminPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
}

AdminPage::~AdminPage()
{
    delete ui;
}


void AdminPage::on_Users_clicked()
{

}

void AdminPage::on_media_clicked()
{

}

void AdminPage::on_edit_clicked()
{

}
