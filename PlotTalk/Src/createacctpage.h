#ifndef CREATEACCTPAGE_H
#define CREATEACCTPAGE_H

#include <QMessageBox>
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

private slots:
    void on_CreateAcctButton_clicked();

    void on_PasswordBox2_textChanged();//const QString &arg1

    void on_GoBack_clicked();

private:
    Ui::CreateAcctPage *ui;
};

#endif // CREATEACCTPAGE_H
