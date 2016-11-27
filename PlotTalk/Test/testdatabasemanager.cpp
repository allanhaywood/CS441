/* Tests the Database Manager class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include "plottalkexceptions.h"
#include "testdatabasemanager.h"
#include "common.h"

/**
 * @brief TestDatabaseManager::TestGetTvShowDefaultConstructor Uses the default constructor for the DBManager and looks up
 * a TvShow.
 */
void TestDatabaseManager::TestGetTvShowDefaultConstructor()
{
    // Set up strings to compare against.
    QString name = "Mr. Robot";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/62560-mr-robot";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/esN3gWb1P091xExLddD2nh4zmi3.jpg";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    TvShow tvShow = DatabaseManagerSingleton::Instance().inspectTvShow(name);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());

    QVector<Season> seasons = tvShow.inspectSeasons();

    QCOMPARE(seasons.count(), 3);

    Season season = tvShow.inspectSeason(0);
    QString expectedSeasonName = "season_0.0";
    QCOMPARE(season.name, expectedSeasonName);
    QCOMPARE(season.seasonId, 77843);
    QCOMPARE(season.seasonNumber, 0);

    QVector<Episode> episodes = season.inspectEpisodes();
    QCOMPARE(episodes.count(), 3);

    Episode episode = season.inspectEpisode(2);

    QString expectedEpisodeName = "Hacking Robot 101";
    QString expectedEpisodeSummary = "In the premiere of the \"Mr. Robot\" after show, the series' cast and creator discuss the Season 2 premiere and field fan questions.";

    QCOMPARE(episode.episodeId, 1203464);
    QCOMPARE(episode.episodeNumber, 2);
    QCOMPARE(episode.name, expectedEpisodeName);
    QCOMPARE(episode.summary, expectedEpisodeSummary);
}

/**
 * @brief TestDatabaseManager::TestGetTvShowJsonPathConstructor Uses the json path constructor, and looks up a Tvshow.
 */
void TestDatabaseManager::TestGetTvShowJsonPathConstructor()
{
    // Set up strings to compare against.
    QString name = "Breaking Bad";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/1396-breaking-bad";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/1yevjox3rjo2jbkrrihimj7uos9.jpg";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    TvShow tvShow = DatabaseManagerSingleton::Instance(":/json/Json/test2.json").inspectTvShow(name);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());
}

/**
 * @brief TestDatabaseManager::NegTestGetTvShowJsonPathConstructor Looks up a TvShow that doesn't exist in the json file.
 * Checks that that proper exception is thrown.
 */
void TestDatabaseManager::NegTestGetTvShowJsonPathConstructor()
{
    // Set up strings to compare against.
    QString name = "Doesn't exist";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QVERIFY_EXCEPTION_THROWN
    (
        TvShow tvShow = DatabaseManagerSingleton::Instance(":/json/Json/test2.json").inspectTvShow(name),
        NotFound
    );
}

void TestDatabaseManager::TestGetUser()
{
    // Set up strings to compare against.
    QString username = "bsmith";
    QString expectedFirstName = "Bob";
    QString expectedLastName = "Smith";
    QString expectedEmail = "bsmith@gmail.com";
    QString expectedPasswordhash = "badpasswordhash";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    User user = DatabaseManagerSingleton::Instance(":/json/Json/test.json").inspectUser(username);

    QCOMPARE(user.username, username);
    QCOMPARE(user.firstName, expectedFirstName);
    QCOMPARE(user.lastName, expectedLastName);
    QCOMPARE(user.email, expectedEmail);
    QCOMPARE(user.passwordHash, expectedPasswordhash);
}

void TestDatabaseManager::TestGetUserByEmail()
{
    // Set up strings to compare against.
    QString expectedUsername = "bsmith";
    QString expectedFirstName = "Bob";
    QString expectedLastName = "Smith";
    QString email = "bsmith@gmail.com";
    QString expectedPasswordhash = "badpasswordhash";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    User user = DatabaseManagerSingleton::Instance(":/json/Json/test.json").inspectUserByEmail(email);

    QCOMPARE(user.username, expectedUsername);
    QCOMPARE(user.firstName, expectedFirstName);
    QCOMPARE(user.lastName, expectedLastName);
    QCOMPARE(user.email, email);
    QCOMPARE(user.passwordHash, expectedPasswordhash);
}

void TestDatabaseManager::TestAddUser()
{
    // Set up strings to compare against.
    QString username = "nuser";
    QString expectedFirstName = "New";
    QString expectedLastName = "User";
    QString expectedEmail = "nuser@gmail.com";
    QString expectedPasswordHash = "newuser123";

    QList<EpisodeIdentifier> expectedWatchedEpisodes = QList<EpisodeIdentifier>();

    expectedWatchedEpisodes.append(EpisodeIdentifier::fromKey("1:2:3"));
    expectedWatchedEpisodes.append(EpisodeIdentifier::fromKey("4:5:6"));

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    qDebug() << "Removing user before attempting to add.";
    DatabaseManagerSingleton::Instance().removeUser(username);

    User userBefore = User(username, expectedFirstName, expectedLastName, expectedEmail, expectedPasswordHash, expectedWatchedEpisodes);
    DatabaseManagerSingleton::Instance().addUser(userBefore);

    User userAfter = DatabaseManagerSingleton::Instance().inspectUser(username);

    QCOMPARE(userAfter.username, username);
    QCOMPARE(userAfter.firstName, expectedFirstName);
    QCOMPARE(userAfter.lastName, expectedLastName);
    QCOMPARE(userAfter.email, expectedEmail);
    QCOMPARE(userAfter.passwordHash, expectedPasswordHash);
    QCOMPARE(userAfter.isAdmin(), false);

    QList<EpisodeIdentifier> userAfterWatchedEpisodes = userAfter.inspectWatchedEpisodes();

    // Make sure both lists are the same length.
    QCOMPARE(userAfterWatchedEpisodes.size(), expectedWatchedEpisodes.size());

    qSort(expectedWatchedEpisodes);
    qSort(userAfterWatchedEpisodes);

    for (int i = 0; i < expectedWatchedEpisodes.size(); i++)
    {
        QCOMPARE(userAfterWatchedEpisodes[i].getKey(), expectedWatchedEpisodes[i].getKey());
    }

    qDebug() << "Removing user after test.";
    DatabaseManagerSingleton::Instance().removeUser(username);
}

void TestDatabaseManager::NegTestAddUser()
{
    // Set up strings to compare against.
    QString username = "nuser";
    QString firstName = "New";
    QString lastName = "User";
    QString expectedEmail = "nuser@gmail.com";
    QString expectedPasswordHash = "newuser123";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    User user = User(username, firstName, lastName, expectedEmail, expectedPasswordHash);

    qDebug() << "Removing user before attempting to add.";
    DatabaseManagerSingleton::Instance().removeUser(username);

    qDebug() << "Adding user:" << username;
    DatabaseManagerSingleton::Instance().addUser(user);

    qDebug() << "Adding user again:" << username;
    QVERIFY_EXCEPTION_THROWN
    (
        DatabaseManagerSingleton::Instance().addUser(user),
        AlreadyExists
    );

    qDebug() << "Removing user after test.";
    DatabaseManagerSingleton::Instance().removeUser(username);
}

void TestDatabaseManager::TestUserExists()
{
    QString username = "bsmith";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Validate that true is returned.
    QVERIFY(DatabaseManagerSingleton::Instance(":/json/Json/test.json").usernameExists(username));
}

void TestDatabaseManager::NegTestUserExists()
{
    QString username = "zsmith";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Validate that false is returned.
    QVERIFY(! DatabaseManagerSingleton::Instance(":/json/Json/test.json").usernameExists(username));
}

void TestDatabaseManager::TestEmailExists()
{
    QString email = "bsmith@gmail.com";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Validate that true is returned.
    QVERIFY(DatabaseManagerSingleton::Instance(":/json/Json/test.json").emailExists(email));
}

void TestDatabaseManager::NegTestEmailExists()
{
    QString email = "zsmith@gmail.com";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Validate that false is returned.
    QVERIFY(! DatabaseManagerSingleton::Instance(":/json/Json/test.json").emailExists(email));
}

/*
void TestDatabaseManager::TestUpdateUser()
{
    // Set up strings to compare against.
    QString username = "tsmith";
    QString expectedFirstName = "Temp";
    QString expectedLastName = "Smith";
    QString expectedEmail = "tsmith@gmail.com";
    QString expectedPasswordHash = "badpasswordhash3";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Make sure temp user doesn't yet exist.
    DatabaseManagerSingleton::Instance().removeUser(username);

    // Add temp user to test with.
    User user = User(username, expectedFirstName, expectedLastName, expectedEmail, expectedPasswordHash);
    DatabaseManagerSingleton::Instance().addUser(user);

    // Validate state of user.
    User user2 = DatabaseManagerSingleton::Instance().inspectUser(username);

    QCOMPARE(user2.username, username);
    QCOMPARE(user2.firstName, expectedFirstName);
    QCOMPARE(user2.lastName, expectedLastName);
    QCOMPARE(user2.email, expectedEmail);
    QCOMPARE(user2.passwordHash, expectedPasswordHash);

    // Modify user before updating it.
    QString newFirstName = "Temp2";
    QString newLastName = "Smith2";
    QString newEmail = "tsmith2@gmail.com";
    QString newPasswordHash = "badpasswordhash4";

    User user3 = User(username, newFirstName, newLastName, newEmail, newPasswordHash);

    DatabaseManagerSingleton::Instance().updateUser(user3);

    User user4 = DatabaseManagerSingleton::Instance().inspectUser(username);

    QCOMPARE(user4.username, username);
    QCOMPARE(user4.firstName, newFirstName);
    QCOMPARE(user4.lastName, newLastName);
    QCOMPARE(user4.email, newEmail);
    QCOMPARE(user4.passwordHash, newPasswordHash);

    // Remove temp user when done.
    DatabaseManagerSingleton::Instance().removeUser(username);
}
*/

/*
void TestDatabaseManager::NegUpdateUser()
{
    // Set up strings to compare against.
    QString username = "barrysmith";
    QString expectedFirstName = "Barry";
    QString expectedLastName = "Smithers";
    QString expectedEmail = "bsmithers@gmail.com";
    QString expectedPasswordHash = "badpasswordhash3";

    User user = User(username, expectedFirstName, expectedLastName, expectedEmail, expectedPasswordHash);

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QVERIFY_EXCEPTION_THROWN
    (
        DatabaseManagerSingleton::Instance().updateUser(user),
        NotFound
    );
}
*/

void TestDatabaseManager::TestGetListOfAllTvShows()
{
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QList<QString> allTvShows = DatabaseManagerSingleton::Instance(":/json/Json/test.json").getListOfAllTvShows();

    QString tvShow0 = "Breaking Bad";
    QString tvShow1 = "Game of Thrones";

    QCOMPARE(allTvShows[0],tvShow0);
    QCOMPARE(allTvShows[1],tvShow1);
}

void TestDatabaseManager::TestGetListOfCachedTvShows()
{
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    DatabaseManagerSingleton::Instance(":/json/Json/test.json").emptyCache();

    TvShow tvShow = DatabaseManagerSingleton::Instance(":/json/Json/test.json").inspectTvShow("Mr. Robot");

    QList<QString> cachedTvShows = DatabaseManagerSingleton::Instance(":/json/Json/test.json").getListOfCachedTvShows();

    QString tvShow0 = "Mr. Robot";

    // Validate there is only one entry.
    QCOMPARE(cachedTvShows.length(),1);

    QCOMPARE(cachedTvShows[0],tvShow0);
}

void TestDatabaseManager::TestGetAllUsers()
{
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QList<QString> allUsers = DatabaseManagerSingleton::Instance(":/json/Json/test.json").getListOfAllUsers();

    User user;
    foreach (const QString &username, allUsers)
    {
        user = DatabaseManagerSingleton::Instance().inspectUser(username);
        qDebug() << "Expected:" << username;
        qDebug() << "Actual:" << user.username;
        QCOMPARE(user.username, username);
    }

    QCOMPARE(allUsers.count(), 10);

    // @todo, add more validation.
}

void TestDatabaseManager::TestGetAllCachedUsers()
{
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QList<QString> allUsers = DatabaseManagerSingleton::Instance(":/json/Json/test.json").getListOfCachedUsers();

    QCOMPARE(allUsers.count(), 0);

    User testUser = DatabaseManagerSingleton::Instance(":/json/Json/test.json").inspectUser("admin");

    allUsers = DatabaseManagerSingleton::Instance(":/json/Json/test.json").getListOfCachedUsers();

    // Cached users should now be one, now that one has been retrieved.
    QCOMPARE(allUsers.count(), 1);

    // @todo, add more validation.
}

void TestDatabaseManager::TestGetTvShowById()
{
    // Set up strings to compare against.
    QString name = "Breaking Bad";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    TvShow tvShow = DatabaseManagerSingleton::Instance(":/json/Json/test2.json").inspectTvShowById(1396);

    QCOMPARE(tvShow.name, name);
}

void TestDatabaseManager::TestAddEpisodeReview()
{
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QString userName = "testUser";
    QString text = "This episode was amazing";
    int rating = 98;
    Review review = Review(userName, text, rating);
    QString Uuid = review.postUuid.toString();

    EpisodeIdentifier episodeIdentifider;
    episodeIdentifider.tvShowId = 1399;
    episodeIdentifider.seasonId = 3627;
    episodeIdentifider.episodeId = 63087;

    DatabaseManagerSingleton::Instance().addEpisodeReview(episodeIdentifider, review);

    QString name = "Game of Thrones";
    TvShow tvShow = DatabaseManagerSingleton::Instance().inspectTvShow(name);

    QList<Review> reviews = tvShow.inspectSeason(0).inspectEpisode(1).inspectReviews();

    bool found = false;
    foreach (const Review &thisReview, reviews)
    {
        if ( QString::compare(thisReview.username, userName) == 0 )
        {
            found = true;
            QCOMPARE(thisReview.text, text);
            QCOMPARE(thisReview.rating, rating);
        }
    }

    QCOMPARE(found, true);
}

void TestDatabaseManager::TestAddEpisodeComment()
{
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QString userName = "testUser";
    QString text = "This episode was pretty cool";
    Comment comment = Comment(userName, text);
    QString Uuid = comment.postUuid.toString();

    EpisodeIdentifier episodeIdentifider;
    episodeIdentifider.tvShowId = 1399;
    episodeIdentifider.seasonId = 3627;
    episodeIdentifider.episodeId = 63087;

    DatabaseManagerSingleton::Instance().addEpisodeComment(episodeIdentifider, comment);

    QString name = "Game of Thrones";
    TvShow tvShow = DatabaseManagerSingleton::Instance().inspectTvShow(name);

    QList<Comment> comments = tvShow.inspectSeason(0).inspectEpisode(1).inspectComments();

    bool found = false;
    foreach (const Comment &thisComment, comments)
    {
        if ( QString::compare(thisComment.postUuid.toString(), Uuid) == 0 )
        {
            found = true;
            QCOMPARE(thisComment.username, userName);
            QCOMPARE(thisComment.text, text);
        }
    }

    QCOMPARE(found, true);
}

bool TestDatabaseManager::deleteTempJson()
{
    // Delete temporary json file for testing.
    QString tempPath = QDir::tempPath();
    tempPath.append("/testJson.json");
    QString jsonPath = QDir::cleanPath(tempPath);

    // Check if a file already exists at that location.
    // If it doesn't, the one from the resources will be used.
    QDir dir(jsonPath);
    if(dir.exists())
    {
        QFile::setPermissions(jsonPath, QFile::WriteOther);
        return dir.remove(jsonPath);
    }

    return true;
}
