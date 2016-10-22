#ifndef ADDNEWMEDIA_H
#define ADDNEWMEDIA_H

#include <QWidget>

namespace Ui {
class AddNewMedia;
}

class AddNewMedia : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewMedia(QWidget *parent = 0);
    ~AddNewMedia();

private:
    Ui::AddNewMedia *ui;
};

#endif // ADDNEWMEDIA_H
