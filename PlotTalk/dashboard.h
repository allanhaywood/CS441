#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>

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

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
