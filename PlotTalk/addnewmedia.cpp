#include "addnewmedia.h"
#include "ui_addnewmedia.h"

AddNewMedia::AddNewMedia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddNewMedia)
{
    ui->setupUi(this);
}

AddNewMedia::~AddNewMedia()
{
    delete ui;
}
