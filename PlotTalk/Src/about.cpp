#include "about.h"
#include "ui_about.h"
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_OkayButton_clicked()
{
    this->close();
}
