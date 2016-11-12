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
    QString name = "Game of Thrones";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    TvShow tvShow = jsonConnection.getTvShow(name);

    QString expectedTmdbLink = "https://www.themoviedb.org/tv/1399-game-of-thrones";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/jIhL6mlT7AblhbHJgEoiBIOUVl1.jpg";

    QCOMPARE(tvShow.showId, 1399);
    QCOMPARE(tvShow.name, name);
    QCOMPARE(tvShow.tmdbLink, expectedTmdbLink);
    QCOMPARE(tvShow.graphicLink, expectedGraphicLink);

    QVector<Season> seasons = tvShow.inspectSeasons();

    QString empty = "";

    QVERIFY(seasons.count() == 1);
    QCOMPARE(seasons[0].seasonId, 3627);
    QCOMPARE(seasons[0].seasonNumber, 0);
    QCOMPARE(seasons[0].name, empty);

    QVector<Episode> episodes = seasons[0].inspectEpisodes();

    QString expectedEpisodeName = "Inside Game Of Thrones";

    QVERIFY(episodes.count() == 1);
    QCOMPARE(episodes[0].episodeId, 63087);
    QCOMPARE(episodes[0].episodeNumber, 0);
    QCOMPARE(episodes[0].name, expectedEpisodeName);
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

    User user = jsonConnection.getUser(username);

    QCOMPARE(user.username, username);
    QCOMPARE(user.firstName, expectedFirstName);
    QCOMPARE(user.lastName, expectedLastName);
    QCOMPARE(user.email.toLower(), expectedEmail.toLower());
    QCOMPARE(user.passwordHash, expectedPasswordHash);
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
    QString expectedEmail = "nuser@gmail.com";
    QString expectedPasswordHash = "newuser123";

    // Get json from resources, but it isn't writeable so save to a different location.
    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    // Create a test json file
    QString currentPath = QDir::currentPath();
    currentPath.append("/testJson.json");
    QString jsonPath = QDir::cleanPath(currentPath);

    jsonConnection.setPathToJson(jsonPath);

    User user = User();

    user.username = username;
    user.email = expectedEmail;
    user.passwordHash = expectedPasswordHash;

    jsonConnection.addUser(user);

    user = jsonConnection.getUser(username);

    QCOMPARE(user.username.toLower(), username.toLower());
    QCOMPARE(user.email.toLower(), expectedEmail.toLower());
    QCOMPARE(user.passwordHash, expectedPasswordHash);
}

void TestJsonConnection::NegTestAddUser()
{
    // Set up strings to compare against.
    QString username = "bsmith";

    JsonConnection jsonConnection = JsonConnection(":/json/Json/test.json");

    User user = jsonConnection.getUser(username);

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

    qDebug() << "Json object:" << jsonObjectBefore;

    // Create a test json file
    QString currentPath = QDir::currentPath();
    currentPath.append("/testJson.json");
    QString jsonPath = QDir::cleanPath(currentPath);

    qDebug() << "Json save path:" << jsonPath;

    jsonConnection.setPathToJson(jsonPath);

    jsonConnection.saveJson();

    jsonConnection.loadJson();

    QJsonObject jsonObjectAfter = jsonConnection.json;

    qDebug() << "Json object:" << jsonObjectAfter;

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
