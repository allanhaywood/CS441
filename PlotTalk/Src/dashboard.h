#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include<adminpage.h>
#include <about.h>

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0);
    ~Dashboard();

private slots:
    void on_myAccountButton_clicked();

    void on_homeButton_clicked();

    void on_popularButton_clicked();

    void on_watchedButton_clicked();

    void on_searchButton_clicked();

    void on_adminButton_clicked();

    void on_AboutButton_clicked();

private:
    Ui::Dashboard *ui;
    AdminPage* adminWindow = NULL;
    About* AboutPage = NULL;
};

#endif // DASHBOARD_H
