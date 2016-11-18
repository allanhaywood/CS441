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
    void TestGetUserDefaultConstructor();
    void TestGetUserByEmail();
    void TestAddUser();
    void NegTestAddUser();
    void TestUserExists();
    void NegTestUserExists();
    void TestEmailExists();
    void NegTestEmailExists();
    void TestUpdateUser();
    void NegUpdateUser();
    void TestGetListOfAllTvShows();
    void TestGetListOfCachedTvShows();
    void TestModifyTvShow();
};

#endif // TESTDATABASEMANAGER_H
