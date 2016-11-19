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

private:
    Ui::AdminPage *ui;
    enum AdminPages {USERS, SHOWS, NEXT, ANOTHER};
};

#endif // ADMINPAGE_H
