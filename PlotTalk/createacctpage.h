#ifndef CREATEACCTPAGE_H
#define CREATEACCTPAGE_H

#include <QDialog>

namespace Ui {
class CreateAcctPage;
}

class CreateAcctPage : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAcctPage(QWidget *parent = 0);
    ~CreateAcctPage();

private:
    Ui::CreateAcctPage *ui;
};

#endif // CREATEACCTPAGE_H
