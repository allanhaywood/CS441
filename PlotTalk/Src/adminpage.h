#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>

namespace Ui {
class AdminPage;
}

class AdminPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = 0);
    ~AdminPage();

private slots:

    void on_Users_clicked();

    void on_media_clicked();

    void on_edit_clicked();

    void on_GoBack_clicked();

    void on_addUser_clicked();

    void on_CreateUser_clicked();

    void on_goBack2_clicked();

    void on_delUser_clicked();

private:
    Ui::AdminPage *ui;
    const int TABSBEFOREUSERNAME=3;
    enum AdminPages {VIEWUSERS, ADDUSER, NEXT, ANOTHER};
};

#endif // ADMINPAGE_H
