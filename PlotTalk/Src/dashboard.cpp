#include "dashboard.h"
#include "ui_dashboard.h"
#include "adminpage.h"
#include "about.h"
#include "plottalkexceptions.h"
#include "accountmanager.h"
#include <QList>
#include <QDebug>


Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(WELCOME); //set stacked widget to home screen at start
    //TODO: only show admin button if user account has admin rights
    ui->adminButton->setVisible(true);

    AccountManager *userInfo= AccountManager::getInstance();//gets the user information
    theUser = userInfo->getCurrentAccount();
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::hideAdminButton()
{
    ui->adminButton->hide();
}

void Dashboard::on_myAccountButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ACCOUNT);
}

void Dashboard::on_homeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(WELCOME);
}

/**
 * @brief Dashboard::on_popularButton_clicked changes to navigation page and populates list of popular shows
 */
void Dashboard::on_popularButton_clicked()
{
    ui->leftList->setDisabled(false);
    ui->leftList->clear();
    //once popular show functionality has been implemented, this will no longer list all shows
    QList<QString> shows = DatabaseManagerSingleton::Instance().getListOfAllTvShows();
    foreach (QString show, shows) {
        ui->leftList->addItem(show);
    }
    ui->stackedWidget->setCurrentIndex(NAVIGATION);
}

void Dashboard::on_watchedButton_clicked()
{
    ui->leftList->setDisabled(false);
    ui->stackedWidget->setCurrentIndex(NAVIGATION);
}

void Dashboard::on_searchButton_clicked()
{
    ui->leftList->clear();
    ui->rightTree->clear();
    QList<QString> shows = DatabaseManagerSingleton::Instance().getListOfAllTvShows();
    bool found = false;
    foreach(QString show, shows) {
        if (show.contains(ui->searchBar->text(), Qt::CaseInsensitive)) {
            found = true;
            ui->leftList->addItem(show);
            ui->leftList->setDisabled(false);
        }
    }
    if (!found) {
        ui->leftList->addItem("No results found");
        ui->leftList->setDisabled(true);
    }
    ui->stackedWidget->setCurrentIndex(NAVIGATION);
}

void Dashboard::on_adminButton_clicked()
{
    if (adminWindow == NULL) //ensure that only one admin window can be created
    {
        adminWindow = new AdminPage();
    }
    adminWindow->show();
    adminWindow->raise();
}

void Dashboard::on_AboutButton_clicked()
{
    if(AboutPage == NULL)
    {
        AboutPage= new About();
    }
    AboutPage->show();
    AboutPage->raise();
}

/**
 * @brief Dashboard::on_leftList_itemClicked is triggered when the user makes a list selection
 * @param item - QListWidgetItem the user has selected
 */
void Dashboard::on_leftList_itemClicked(QListWidgetItem *item)
{
    QString selected = item->text();
    selectedShow = DatabaseManagerSingleton::Instance().getTvShow(selected);
    populateSeasonList(ui->rightTree);
}

/**
 * @brief Dashboard::populateSeasonList populates the appropriate list with seasons and episodes
 * @param treeWidget - pointer to tree widget that will be mod
 * @pre expects selectedShow to be already set
 */
void Dashboard::populateSeasonList(QTreeWidget *treeWidget) {
    treeWidget->clear();
    //using pointers to prevent objects from going out of scope
    //no need to delete tree items - parent tree destroys its children
    foreach(Season season, selectedShow.inspectSeasons()) {
        QTreeWidgetItem *seasonNode = new QTreeWidgetItem(treeWidget);
        seasonNode->setText(0, "Season " + QString::number(season.seasonNumber));
        foreach(Episode episode, season.inspectEpisodes()) {
            QTreeWidgetItem *episodeNode = new QTreeWidgetItem(seasonNode);
            episodeNode->setText(0, episode.name);
        }
    }

}

/**
 * @brief Dashboard::on_rightTree_itemClicked is triggered when the user selects a tree item.
 * @param item - item user selected
 * @param column - column of selected item
 * @post sets selectedSeason and selectedEpisode (episode selection implies season has been set) and goes to media item page
 */
void Dashboard::on_rightTree_itemClicked(QTreeWidgetItem *item, int)
{
  //once seasons and episodes are fully implemented, season and episode objects will be populated with actual data
  if (item->childCount() == 0) { // the selection is a leaf (i.e. it's an episode)
        QTreeWidgetItem *parent = item->parent();
        selectedSeason = selectedShow.getSeason(parent->text(0).split(" ")[1].toInt());
        selectedEpisode = selectedSeason.getEpisode(item->text(0));
        //go to media item page
        populateSeasonList(ui->mediaItemTree);
        populateMediaItemPage();
        ui->rightTree->clear();
        ui->stackedWidget->setCurrentIndex(ITEM);
  }
}

/**
 * @brief Dashboard::populateMediaItemPage - populates fields on media item page
 * @pre expects selectedShow, selectedSeason, and selectedEpisode to be set
 */
void Dashboard::populateMediaItemPage() {
    // clear out comments
    ui->commentTable->clear();
    ui->commentBox->clear();
    ui->commentTable->setRowCount(0);

    ui->mediaItemSplitter->setSizes({1, 300});
    ui->showName->setText(selectedShow.name);
    QString seasonText = "Season ";
    seasonText.append(QString::number(selectedSeason.seasonNumber));
    ui->seasonName->setText(seasonText);
    ui->episodeSummary->setText(selectedEpisode.summary);
    ui->episodeName->setText(selectedEpisode.name);
    //@TODO: only show spoiler alert if user hasn't watched episode
    //if episode is in user's watched list:
    //hide watched warning and checkbox
    //don't hide additional episode items (summary, comments, reviews)
    //else:
    ui->episodeSummary->setVisible(false);
    ui->commentTabWidget->setVisible(false);
    ui->watchedWarning->setVisible(true);
    ui->watchedConfirmButton->setVisible(true);
}

/**
 * @brief Dashboard::on_mediaItemTree_itemClicked is triggered when the user selects a tree item.
 * @param item - item user selected
 * @param column - column of selected item
 * @post sets selectedSeason and selectedEpisode (episode selection implies season has been set) and updates media item page
 */

void Dashboard::on_mediaItemTree_itemClicked(QTreeWidgetItem *item, int)
{
  //once seasons and episodes are fully implemented, season and episode objects will be populated with actual data
  if (item->childCount() == 0) { // the selection is a leaf (i.e. it's an episode)
        QTreeWidgetItem *parent = item->parent();
        selectedSeason = selectedShow.getSeason(parent->text(0).split(" ")[1].toInt());
        selectedEpisode = selectedSeason.getEpisode(item->text(0));
        //go to media item page
        populateMediaItemPage();
  }
}

/**
 * @brief Dashboard::on_watchedButton_2_clicked triggered when user clicks "I've seen it!" button on media page
 * @post unhides additional media details and adds this episode to the user's watched list
 */
void Dashboard::on_watchedConfirmButton_clicked()
{
    ui->episodeSummary->setVisible(true);
    ui->commentTabWidget->setVisible(true);
    ui->watchedConfirmButton->setVisible(false);
    ui->watchedWarning->setVisible(false);
    //@TODO add episode to watched list once it has been added to user class
}

/**
 * @brief Dashboard::on_saveButton_clicked saves the users account info when Save button is clicked
 */
void Dashboard::on_saveButton_clicked()
{
    //similar validation steps as create account page
    //only populate username, email, and name fields. Do not populate password fields from DB.
    //if new password field isn't empty, show message if it doesn't match confirm password textbox
    //only update user password if new password field isn't empty and it matches confirm textbox
}

// @TODO: Need to add comments to episode be saved in episode class.
void Dashboard::on_commentButton_clicked()
{
    // initialize columns for username/ comment
    if (ui->commentTable->columnCount() == 0)
    {
        ui->commentTable->insertColumn(0);
        ui->commentTable->insertColumn(1);
        ui->commentTable->setColumnWidth(0, 125);
        ui->commentTable->setColumnWidth(1, 330);
    }
    // hide labels on table
    ui->commentTable->horizontalHeader()->setVisible(false);
    ui->commentTable->verticalHeader()->setVisible(false);

    // ensure wordwrapping is enabled
    ui->commentTable->setWordWrap(true);

    // add new row and new comment
    int curRow = ui->commentTable->rowCount(); // current row of next comment
    ui->commentTable->insertRow(curRow);
    ui->commentTable->setRowHeight(curRow, 50);
    ui->commentTable->setItem(curRow, 0, new QTableWidgetItem(theUser.username));
    ui->commentTable->setItem(curRow, 1, new QTableWidgetItem(ui->commentBox->toPlainText()));
    QTextEdit *commentText = new QTextEdit;
    commentText->setText(ui->commentTable->item(curRow, 1)->text());
    ui->commentTable->setCellWidget(curRow, 1, commentText);

    // clear contents of comment box
    ui->commentBox->clear();
}
