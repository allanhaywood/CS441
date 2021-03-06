/* Header for tests for the json connection.
 *
 * @author Allan Haywood
 */
#ifndef TESTJSONCONNECTION_H
#define TESTJSONCONNECTION_H

#include <QObject>
#include "jsonconnection.h"

class TestJsonConnection : public QObject
{
    Q_OBJECT
private slots:
    void TestGetTvShow1();
    void TestGetTvShow2();
    void TestGetUser();
    void TestGetAdminUser();
    void TestGetUserNameByEmail();
    void TestAddUser();
    void TestAddAdminUser();
    void NegTestAddUser();
    void TestUserExists();
    void NegTestUserExists();
    void TestEmailExists();
    void NegTestEmailExists();
    void TestSaveJson();
    void TestGetListOfAllTvShows();
    void TestUserWatchedEpisodes();
    //void TestAddEpisodeReview();
};

#endif // TESTJSONCONNECTION_H
