#include "dashboard.h"
#include "ui_dashboard.h"
#include "adminpage.h"
#include "about.h"
#include "plottalkexceptions.h"
#include "accountmanager.h"
#include <QList>
#include <QDebug>
#include <QColorDialog>
#include <QDateTime>
#include "mainwindow.h"
#include <QMessageBox>


Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(WELCOME); //set stacked widget to home screen at start
    //TODO: only show admin button if user account has admin rights
    ui->adminButton->setVisible(true);

    AccountManager *userInfo= AccountManager::getInstance();//gets the user information
    theUser=userInfo->getCurrentAccount();
    ui->welcomeText->setText("Welcome to PlotTalk "+theUser.firstName +"!");

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


    ui->usernameLabel->setText(theUser.username);
    ui->firstNameBox->setText(theUser.firstName);
    ui->lastNameBox->setText(theUser.lastName);
    ui->emailBox->setText(theUser.email);

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
    foreach(Season season, selectedShow.getSeasons()) {
        QTreeWidgetItem *seasonNode = new QTreeWidgetItem(treeWidget);
        seasonNode->setText(0, "Season " + QString::number(season.seasonNumber));
        foreach(Episode episode, season.getEpisodes()) {
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
    ui->mediaItemSplitter->setSizes({1, 300});

    // clear out comments and reviews
    ui->commentTable->clear();
    ui->commentBox->clear();
    ui->commentTable->setRowCount(0);
    ui->reviewTable->clear();
    ui->reviewCommentBox->clear();
    ui->reviewTable->setRowCount(0);
    ui->episodeRatingNum->setText(0); // @TODO: Replace this with episode's saved overall rating

    // ensure first comment/review tab viewed is comment tab
    ui->commentTabWidget->setCurrentIndex(0);

    // set up initial review tab settings
    ui->ratingMeter->setMinimum(0);
    ui->ratingMeter->setMaximum(100);
    ui->ratingMeter->setSliderPosition(50);

    // ensure only integers can be entered for rating score
    ui->ratingNumber->setValidator(new QIntValidator(0, 100, this));

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
    ui->episodeSummaryLabel->setVisible(false);
    ui->episodeSummary->setVisible(false);
    ui->commentTabWidget->setVisible(false);
    ui->episodeRatingNum->setVisible(false);
    ui->overallRatingLabel->setVisible(false);
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
 * @brief Dashboard::on_saveButton_clicked saves the users account info when Save button is clicked
 */
void Dashboard::on_saveButton_clicked()
{
    //similar validation steps as create account page
    //only populate username, email, and name fields. Do not populate password fields from DB.
    //if new password field isn't empty, show message if it doesn't match confirm password textbox
    //only update user password if new password field isn't empty and it matches confirm textbox
    QString newEmail=ui->emailBox->text();
    QString newFirstName=ui->firstNameBox->text();
    QString newLastName=ui->lastNameBox->text();
    QString newPassword;


    if(ui->newPasswordBox->text()==ui->confirmPasswordBox->text() && ui->confirmPasswordBox->text()!="")
    {
        newPassword = ui->newPasswordBox->text();
    }
    else if(ui->confirmPasswordBox->text()=="" && ui->newPasswordBox->text()=="")
    {
           newPassword=theUser.passwordHash;
    }
    else
    {
        QMessageBox noPassMatch;
        noPassMatch.setText("The two password fields must match\n(Leave blank to avoid changing)");
        noPassMatch.exec();

        ui->newPasswordBox->clear();
        ui->confirmPasswordBox->clear();
        return;
    }

    AccountManager *userInfo= AccountManager::getInstance();//gets the user information
{
    if(theUser.email!=newEmail || theUser.firstName!= newFirstName || theUser.lastName!=newLastName || newPassword!=theUser.passwordHash)
    {//add check for each field to determine when it is changed, set back if not.
        QString message;

        DatabaseManagerSingleton::Instance().removeUser(theUser.username);
        selectEnum Problems=userInfo->checkFieldsAndCreate(newFirstName,newLastName,theUser.username,newEmail,newPassword,false);

        switch (Problems)
        {
        case selectEnum::BAD_EMAIL:
          {
            message="The email you entered was incorrectly formatted";
            ui->emailBox->clear();
          }
            break;
        case selectEnum::DUPLICATE_EMAIL:
          {
            message="That e-mail is already present in our system";
            ui->emailBox->clear();
          }
            break;
        case selectEnum::VALUES_MISSING:
          {
            message="You must enter a first and last name";
          }
            break;
        case selectEnum::BAD_PASSWORD:
          {
            message="The password must have the following characteristics:\nIt must be more than 8 characters\nIt must contain both capital and lowercase letters\nIt must include at least one special symbol";
            ui->newPasswordBox->clear();
            ui->confirmPasswordBox->clear();
          }
            break;
        case selectEnum::ALLCLEAR:
          {
            message="Your account has been successfully updated!";
            ui->stackedWidget->setCurrentIndex(WELCOME);
            theUser = userInfo->getCurrentAccount();
            ui->welcomeText->setText("Welcome to PlotTalk "+theUser.firstName +"!");
          }

         }
             QMessageBox emailExists;
             emailExists.setText(message);
             emailExists.exec();

             return;
         }
         else
         {
            ui->stackedWidget->setCurrentIndex(WELCOME);
         }
    }
}

/**
 * @brief Dashboard::on_watchedButton_2_clicked triggered when user clicks "I've seen it!" button on media page
 * @post unhides additional media details and adds this episode to the user's watched list
 */
void Dashboard::on_watchedConfirmButton_clicked()
{
    ui->episodeSummary->setVisible(true);
    ui->episodeSummaryLabel->setVisible(true);
    ui->commentTabWidget->setVisible(true);
    ui->episodeRatingNum->setVisible(true);
    ui->overallRatingLabel->setVisible(true);
    ui->watchedConfirmButton->setVisible(false);
    ui->watchedWarning->setVisible(false);
    //@TODO add episode to watched list once it has been added to user class
}

/**
 * @brief Dashboard::on_logoutButton_clicked logs out the current user
 */
void Dashboard::on_logoutButton_clicked()
{
     AccountManager *userInfo= AccountManager::getInstance();
     userInfo->ClearForLogout();//clears the user out of account manager
     this->close();
     MainWindow *openAgain=new MainWindow();
     openAgain->show();


}

/**
 * @brief Dashboard::on_commentButton_clicked is triggered when the user clicks on the post reply button on comment tab.
 * @post Adds new comment entered in text box to the table widget.
 *
 */
// @TODO: Need to ensure comments added to an episode are saved in episode class using DBManager calls.
// @TODO: Need to utilize reaction/reply/review classes.
void Dashboard::on_commentButton_clicked()
{
    // initialize columns for username/ comment
    if (ui->commentTable->columnCount() == 0)
    {
        ui->commentTable->insertColumn(0); // username column
        ui->commentTable->insertColumn(1); // comment column
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
    // @TODO: Replace this explicit call to date to using date from reaction/review/reply class
    QString userAndDate = theUser.username + "\n" + QDateTime::currentDateTimeUtc().toString("MM/dd/yyyy h:m ap");
    ui->commentTable->setItem(curRow, 0, new QTableWidgetItem(userAndDate));
    ui->commentTable->setItem(curRow, 1, new QTableWidgetItem(ui->commentBox->toPlainText()));
    QTextEdit *commentText = new QTextEdit;
    commentText->setText(ui->commentTable->item(curRow, 1)->text());
    commentText->setReadOnly(true);
    ui->commentTable->setCellWidget(curRow, 1, commentText);
    ui->commentTable->item(curRow, 0)->setBackgroundColor(Qt::lightGray);

    // clear contents of comment box
    ui->commentBox->clear();
}

/**
 * @brief Dashboard::on_ratingMeter_valueChanged(int value) is triggered when user moves episode rating slider.
 * @param: value is the integer equivalent of where the slider was moved
 * @post Updates the text box to display the rating the user will give the episode
 */
void Dashboard::on_ratingMeter_valueChanged(int value)
{
    ui->ratingNumber->setText(QString::number(value));
}

/**
 * @brief Dashboard::on_reviewButton_clicked() is triggered when user clicks on post rating button.
 * @post Adds users rating and review to the table widget
 */
void Dashboard::on_reviewButton_clicked()
{
    // initialize columns for username/ comment / rating
    if (ui->reviewTable->columnCount() == 0)
    {
        ui->reviewTable->insertColumn(0); // username
        ui->reviewTable->insertColumn(1); // rating
        ui->reviewTable->insertColumn(2); // review
        ui->reviewTable->setColumnWidth(0, 120);
        ui->reviewTable->setColumnWidth(1, 30);
        ui->reviewTable->setColumnWidth(2, 305);
    }
    // hide labels on table
    ui->reviewTable->horizontalHeader()->setVisible(false);
    ui->reviewTable->verticalHeader()->setVisible(false);

    // ensure wordwrapping is enabled
    ui->reviewTable->setWordWrap(true);

    // add new row with new rating/review
    int curRow = ui->reviewTable->rowCount(); // current row of next review
    ui->reviewTable->insertRow(curRow);
    ui->reviewTable->setRowHeight(curRow, 50);
    // @TODO: Replace this explicit call to date to using date from reaction/review/reply class
    QString userAndDate = theUser.username + "\n" + QDateTime::currentDateTimeUtc().toString("MM/dd/yyyy h:m ap");
    ui->reviewTable->setItem(curRow, 0, new QTableWidgetItem(userAndDate));
    ui->reviewTable->setItem(curRow, 1, new QTableWidgetItem(ui->ratingNumber->text()));
    ui->reviewTable->setItem(curRow, 2, new QTableWidgetItem(ui->reviewCommentBox->toPlainText()));
    QTextEdit *reviewText = new QTextEdit;
    reviewText->setText(ui->reviewTable->item(curRow, 2)->text());
    reviewText->setReadOnly(true);
    ui->reviewTable->setCellWidget(curRow, 2, reviewText);
    ui->reviewTable->item(curRow, 0)->setBackgroundColor(Qt::lightGray);
    QColor lightBlue(194, 229, 255);
    ui->reviewTable->item(curRow, 1)->setBackgroundColor(lightBlue);

    // calculate new overall rating score
    int totalRatings = 0;
    for (int i = 0; i < ui->reviewTable->rowCount(); i++)
    {
        totalRatings += ui->reviewTable->item(i, 1)->text().toInt();
    }
    int newAverage = totalRatings / (curRow+1);
    ui->episodeRatingNum->setText(QString::number(newAverage));

    // clear contents of comment box
    ui->reviewCommentBox->clear();
    ui->ratingMeter->setSliderPosition(50);
    ui->ratingNumber->setText("50");
}

/**
 * @brief Dashboard::on_ratingNumber_textEdited(const QString &arg1) is triggered
 * when user edits the rating number in the line edit on review tab.
 * @param String argument that was entered in the line edit
 */
void Dashboard::on_ratingNumber_textEdited(const QString &arg1)
{
    int newRating = arg1.toInt();
    ui->ratingMeter->setValue(newRating);
}
