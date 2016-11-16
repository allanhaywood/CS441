#include "dashboard.h"
#include "ui_dashboard.h"
#include "adminpage.h"
#include "about.h"
#include "plottalkexceptions.h"
#include "accountmanager.h"
#include "mainwindow.h"
#include <QLIST>
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


    //ui->splitter_popularPage->setSizes({500, 1}); // preset the splitter to make search side bigger initially
    //ui->splitter_SearchResultsPage->setSizes({500, 1});
    //ui->splitter_watchedMediaPage->setSizes({500, 1});




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
        if (QString::compare(show, ui->searchBar->text(), Qt::CaseInsensitive) == 0) {
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
    //when seasons and episodes are fully implemented, this will populate with the actual seasons and episodes
    //for now, the entries are hardcoded with example cases of Game of Thrones and Mr. Robot
    //using pointers to prevent objects from going out of scope
    //no need to delete tree items - parent tree destroys its children
    QTreeWidgetItem *season1 = new QTreeWidgetItem(treeWidget);
    QTreeWidgetItem *season2 = new QTreeWidgetItem(treeWidget);
    season1->setText(0, "Season 1");
    season2->setText(0, "Season 2");
    QTreeWidgetItem *episode1 = new QTreeWidgetItem(season1);
    QTreeWidgetItem *episode2 = new QTreeWidgetItem(season2);
    if (selectedShow.name == "Game of Thrones") {
        episode1->setText(0, "Winter Is Coming");
        episode2->setText(0, "The North Remembers");
    } else if (selectedShow.name == "Mr. Robot"){
        episode1->setText(0, "eps1.0_hellofriend.mov");
        episode2->setText(0, "eps2.0unm4sk-pt1.tc");
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
        Season season(parent->text(0).split(" ")[1].toInt()); //ensures that season has been selected too
        selectedSeason = season;
        Episode episode(0, "", item->text(0));
        selectedEpisode = episode;
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
    ui->showName->setText(selectedShow.name);
    QString seasonText = "Season ";
    seasonText.append(QString::number(selectedSeason.seasonNumber));
    ui->seasonName->setText(seasonText);
    //@TODO: summary text is lorem ipsum for now - actual summary will need to be pulled in from DB for this episode
    ui->episodeSummary->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut pulvinar sem quam, sed dictum odio finibus in. Maecenas consectetur sapien id fermentum euismod. Nunc vitae egestas turpis. Curabitur nunc erat, varius eget aliquet id, viverra eget metus. Integer ipsum purus, viverra ut egestas sit amet, dapibus eget leo. Aliquam vel euismod metus, eget efficitur mi. Fusce dignissim blandit neque, sed porttitor augue lacinia sed. Sed laoreet nunc non porttitor imperdiet.");
    ui->episodeName->setText(selectedEpisode.episodeTitle);
    //@TODO: only show spoiler alert if user hasn't watched episode
    //if episode is in user's watched list:
    //hide watched warning and checkbox
    //don't hide additional episode items (summary, comments, reviews)
    //else:
    ui->episodeSummary->setVisible(false);
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
        Season season(parent->text(0).split(" ")[1].toInt()); //ensures that season has been selected too
        selectedSeason = season;
        Episode episode(0, "", item->text(0));
        selectedEpisode = episode;
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
    QString newPassword="";

    if(ui->newPasswordBox->text()==ui->confirmPasswordBox->text())
    {
        newPassword = ui->newPasswordBox->text();
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

    if(theUser.email!=newEmail || theUser.firstName!= newFirstName || theUser.lastName!=newLastName || newPassword!="")
    {//add check for each field to determine when it is changed, set back if not.
        QString message;

        DatabaseManagerSingleton::Instance().removeUser(theUser.username);
        selectEnum Problems=userInfo->checkFieldsAndCreate(newFirstName,newLastName,theUser.username,newEmail,newPassword);

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
          }

         }
             QMessageBox emailExists;
             emailExists.setText(message);
             emailExists.exec();

             return;
         }
         else
         {

             //userInfo->createAccount(theUser.firstName, theUser.lastName, theUser.email, theUser.username, theUser.passwordHash);

             QMessageBox updated;
             updated.setText("Your account has been updated");
             updated.exec();
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
    ui->watchedConfirmButton->setVisible(false);
    ui->watchedWarning->setVisible(false);
    //@TODO add episode to watched list once it has been added to user class
}

void Dashboard::on_logoutButton_clicked()
{
     AccountManager *userInfo= AccountManager::getInstance();
     userInfo->ClearForLogout();//clears the user out of account manager
     this->close();
     MainWindow *openAgain=new MainWindow();
     openAgain->show();


}
