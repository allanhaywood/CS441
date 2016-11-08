/* Tests the Json Connection class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include <QDir>
#include "plottalkexceptions.h"
#include "testjsonconnection.h"

void TestJsonConnection::TestGetTvShow()
{
    // Set up strings to compare against.
    QString name = "Game Of Thrones";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/1399-game-of-thrones";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/jihl6mlt7ablhbhjgeoibiouvl1.jpg";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    TvShow tvShow = TvShow();
    jsonConnection.getTvShow(name, tvShow);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}

void TestJsonConnection::TestGetUser()
{
    // Set up strings to compare against.
    QString username = "bsmith";
    QString expectedFirstName = "Bob";
    QString expectedLastName = "Smith";
    QString expectedEmail = "bsmith@gmail.com";
    QString expectedPasswordHash = "badpasswordhash";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    User user = User();
    jsonConnection.getUser(username, user);

    QCOMPARE(user.username, username);
    QCOMPARE(user.firstName, expectedFirstName);
    QCOMPARE(user.lastName, expectedLastName);
    QCOMPARE(user.email.toLower(), expectedEmail.toLower());
    QCOMPARE(user.passwordHash, expectedPasswordHash);
}

void TestJsonConnection::TestGetAdminUser()
{
    // Set up strings to compare against.
    QString username = "admin";
    QString expectedFirstName = "admin";
    QString expectedLastName = "admin";
    QString expectedEmail = "admin@gmail.com";
    QString expectedPasswordHash = "plottalkadmin";
    bool expectedIsAdmin = true;

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    User user = User();
    jsonConnection.getUser(username, user);

    QCOMPARE(user.username, username);
    QCOMPARE(user.firstName, expectedFirstName);
    QCOMPARE(user.lastName, expectedLastName);
    QCOMPARE(user.email.toLower(), expectedEmail.toLower());
    QCOMPARE(user.passwordHash, expectedPasswordHash);
    QCOMPARE(user.isAdmin(), expectedIsAdmin);
}

void TestJsonConnection::TestGetUserNameByEmail()
{
    // Set up strings to compare against.
    QString expectedUsername = "bsmith";
    QString email = "bsmith@gmail.com";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    QCOMPARE(jsonConnection.getUserNameByEmail(email), expectedUsername);
}

void TestJsonConnection::TestAddUser()
{
    // Set up strings to compare against.
    QString username = "nuser";
    QString firstName = "New";
    QString lastName = "User";
    QString email = "nuser@gmail.com";
    QString passwordHash = "newuser123";

    // Get json from resources, but it isn't writeable so save to a different location.
    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    // Create a test json file
    QString currentPath = QDir::currentPath();
    currentPath.append("/testJson.json");
    QString jsonPath = QDir::cleanPath(currentPath);

    jsonConnection.setPathToJson(jsonPath);

    User user = User(username, firstName, lastName, email, passwordHash);

    jsonConnection.addUser(user);

    user = User();
    jsonConnection.getUser(username, user);

    QCOMPARE(user.username, username);
    QCOMPARE(user.firstName, firstName);
    QCOMPARE(user.lastName, lastName);
    QCOMPARE(user.email, email);
    QCOMPARE(user.passwordHash, passwordHash);
    QCOMPARE(user.isAdmin(), false);
}

void TestJsonConnection::TestAddAdminUser()
{
    // Set up strings to compare against.
    QString username = "nuser";
    QString firstName = "New";
    QString lastName = "User";
    QString email = "nuser@gmail.com";
    QString passwordHash = "newuser123";

    // Get json from resources, but it isn't writeable so save to a different location.
    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    // Create a test json file
    QString currentPath = QDir::currentPath();
    currentPath.append("/testJson.json");
    QString jsonPath = QDir::cleanPath(currentPath);

    jsonConnection.setPathToJson(jsonPath);

    User user = User(username, firstName, lastName, email, passwordHash, true);

    jsonConnection.addUser(user);

    user = User();
    jsonConnection.getUser(username, user);

    QCOMPARE(user.username, username);
    QCOMPARE(user.firstName, firstName);
    QCOMPARE(user.lastName, lastName);
    QCOMPARE(user.email, email);
    QCOMPARE(user.passwordHash, passwordHash);
    QCOMPARE(user.isAdmin(), true);
}

void TestJsonConnection::NegTestAddUser()
{
    // Set up strings to compare against.
    QString username = "bsmith";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    User user = User();
    jsonConnection.getUser(username, user);

    QVERIFY_EXCEPTION_THROWN
            (
                jsonConnection.addUser(user),
                AlreadyExists
            );
}

void TestJsonConnection::TestUserExists()
{
    QString username = "bsmith";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    // Validate that true is returned.
    QVERIFY(jsonConnection.usernameExists(username));
}

void TestJsonConnection::NegTestUserExists()
{
    QString username = "zsmith";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    // Validate that false is returned.
    QVERIFY(! jsonConnection.usernameExists(username));
}

void TestJsonConnection::TestEmailExists()
{
    QString email = "bsmith@gmail.com";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    // Validate that true is returned.
    QVERIFY(jsonConnection.emailExists(email));
}

void TestJsonConnection::NegTestEmailExists()
{
    QString email = "zsmith@gmail.com";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    // Validate that false is returned.
    QVERIFY(! jsonConnection.emailExists(email));
}

void TestJsonConnection::TestSaveJson()
{
    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    QJsonObject jsonObjectBefore = jsonConnection.json;

    // Create a test json file
    QString currentPath = QDir::currentPath();
    currentPath.append("/testJson.json");
    QString jsonPath = QDir::cleanPath(currentPath);

    jsonConnection.setPathToJson(jsonPath);

    jsonConnection.saveJson();

    jsonConnection.loadJson();

    QJsonObject jsonObjectAfter = jsonConnection.json;

    // Verify newly loaded json object is not empty.
    QVERIFY(! jsonObjectAfter.isEmpty());
}

void TestJsonConnection::TestGetListOfAllTvShows()
{
    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    QList<QString> allTvShows = jsonConnection.getListOfAllTvShows();

    QString tvShow0 = "Game of Thrones";
    QString tvShow1 = "Mr. Robot";

    QCOMPARE(allTvShows[0],tvShow0);
    QCOMPARE(allTvShows[1],tvShow1);
}
