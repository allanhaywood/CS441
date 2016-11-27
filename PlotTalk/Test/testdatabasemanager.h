/* Header for tests for the database manager.
 *
 * @author Allan Haywood
 */
#ifndef TESTDATABASEMANAGER_H
#define TESTDATABASEMANAGER_H

#include <QObject>
#include "databasemanager.h"

class TestDatabaseManager : public QObject
{
    Q_OBJECT
private slots:
    void TestGetTvShowDefaultConstructor();
    void TestGetTvShowJsonPathConstructor();
    void NegTestGetTvShowJsonPathConstructor();
    void TestGetUser();
    void TestGetUserByEmail();
    void TestAddUser();
    void NegTestAddUser();
    void TestUserExists();
    void NegTestUserExists();
    void TestEmailExists();
    void NegTestEmailExists();
    //void TestUpdateUser();
    //void NegUpdateUser();
    void TestGetListOfAllTvShows();
    void TestGetListOfCachedTvShows();
    //void NegTestModifyTvShow();
    void TestGetAllUsers();
    void TestGetAllCachedUsers();
    void TestGetTvShowById();
    void TestAddEpisodeReview();
    void TestAddEpisodeComment();
    void TestAddAndRemoveWatchedEpisode();
    void TestWatchedTvShowList();

private:
    bool deleteTempJson();
};

#endif // TESTDATABASEMANAGER_H
