#ifndef DASHBOARD_H
#define DASHBOARD_H

#include<QMainWindow>
#include<adminpage.h>
#include<about.h>
#include<QTreeWidget>
#include<QListWidgetItem>
#include<QTreeWidgetItem>
#include<tvshow.h>
#include<episode.h>
#include<season.h>
#include<singleton.h>
#include<databasemanager.h>

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

    void on_leftList_itemClicked(QListWidgetItem *item);

    void on_rightTree_itemClicked(QTreeWidgetItem *item, int column);

    void on_mediaItemTree_itemClicked(QTreeWidgetItem *item, int column);

    void on_watchedConfirmButton_clicked();

    void on_saveButton_clicked();

private:
    void populateSeasonList(QTreeWidget *treeWidget);
    void populateMediaItemPage();

    Ui::Dashboard *ui;
    AdminPage* adminWindow = NULL;
    About* AboutPage = NULL;
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;
    enum Pages {WELCOME, NAVIGATION, ITEM, ACCOUNT}; //pages of the dashboard, ordered by their page number
    TvShow selectedShow;
    Season selectedSeason;
    Episode selectedEpisode;
};

#endif // DASHBOARD_H
