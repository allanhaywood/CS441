#ifndef ACCOUNTDETAILS_H
#define ACCOUNTDETAILS_H

#include <QDialog>

namespace Ui {
class AccountDetails;
}

class AccountDetails : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDetails(QWidget *parent = 0);
    ~AccountDetails();

private:
    Ui::AccountDetails *ui;
};

#endif // ACCOUNTDETAILS_H
