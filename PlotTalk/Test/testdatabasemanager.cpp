/* Tests the Database Manager class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include "plottalkexceptions.h"
#include "testdatabasemanager.h"

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

    TvShow& tvShow = DatabaseManagerSingleton::Instance().getTvShow(name);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());

    QVector<Season> seasons = tvShow.inspectSeasons();

    QCOMPARE(seasons.count(), 1);

    Season season = seasons[0];

    QString expectedSeasonName = "season_0.0";

    QCOMPARE(season.name, expectedSeasonName);
    QCOMPARE(season.seasonId, 66343);
    QCOMPARE(season.seasonNumber, 0);

    QVector<Episode> episodes = season.inspectEpisodes();

    QCOMPARE(episodes.count(), 2);

    Episode episode = episodes[1];

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

    TvShow& tvShow = DatabaseManagerSingleton::Instance(":/json/Json/test2.json").getTvShow(name);

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
        TvShow tvShow = DatabaseManagerSingleton::Instance(":/json/Json/test2.json").getTvShow(name),
        NotFound
    );
}

void TestDatabaseManager::TestGetUserDefaultConstructor()
{
    // Set up strings to compare against.
    QString username = "bsmith";
    QString expectedFirstName = "Bob";
    QString expectedLastName = "Smith";
    QString expectedEmail = "bsmith@gmail.com";
    QString expectedPasswordhash = "badpasswordhash";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    User& user = DatabaseManagerSingleton::Instance().getUser(username);

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

    User &user = DatabaseManagerSingleton::Instance().getUserByEmail(email);

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

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    User userBefore = User(username, expectedFirstName, expectedLastName, expectedEmail, expectedPasswordHash);
    DatabaseManagerSingleton::Instance().addUser(userBefore);

    User userAfter = DatabaseManagerSingleton::Instance().getUser(username);

    QCOMPARE(userAfter.username, username);
    QCOMPARE(userAfter.firstName, expectedFirstName);
    QCOMPARE(userAfter.lastName, expectedLastName);
    QCOMPARE(userAfter.email, expectedEmail);
    QCOMPARE(userAfter.passwordHash, expectedPasswordHash);
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
}

void TestDatabaseManager::TestUserExists()
{
    QString username = "bsmith";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Validate that true is returned.
    QVERIFY(DatabaseManagerSingleton::Instance().usernameExists(username));
}

void TestDatabaseManager::NegTestUserExists()
{
    QString username = "zsmith";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Validate that false is returned.
    QVERIFY(! DatabaseManagerSingleton::Instance().usernameExists(username));
}

void TestDatabaseManager::TestEmailExists()
{
    QString email = "bsmith@gmail.com";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Validate that true is returned.
    QVERIFY(DatabaseManagerSingleton::Instance().emailExists(email));
}

void TestDatabaseManager::NegTestEmailExists()
{
    QString email = "zsmith@gmail.com";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    // Validate that false is returned.
    QVERIFY(! DatabaseManagerSingleton::Instance().emailExists(email));
}

void TestDatabaseManager::TestUpdateUser()
{
    // Set up strings to compare against.
    QString username = "bsmith";
    QString expectedFirstName = "Barry";
    QString expectedLastName = "Smithers";
    QString expectedEmail = "bsmithers@gmail.com";
    QString expectedPasswordHash = "badpasswordhash3";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    User user = DatabaseManagerSingleton::Instance().getUser("bsmith");

    user.firstName = expectedFirstName;
    user.lastName = expectedLastName;
    user.email = expectedEmail;
    user.passwordHash = expectedPasswordHash;

    DatabaseManagerSingleton::Instance().updateUser(user);

    QCOMPARE(user.username, username);
    QCOMPARE(user.firstName, expectedFirstName);
    QCOMPARE(user.lastName, expectedLastName);
    QCOMPARE(user.email, expectedEmail);
    QCOMPARE(user.passwordHash, expectedPasswordHash);

    User user2 = DatabaseManagerSingleton::Instance().getUser("bsmith");

    QCOMPARE(user2.username, username);
    QCOMPARE(user2.firstName, expectedFirstName);
    QCOMPARE(user2.lastName, expectedLastName);
    QCOMPARE(user2.email, expectedEmail);
    QCOMPARE(user2.passwordHash, expectedPasswordHash);
}

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

void TestDatabaseManager::TestGetListOfAllTvShows()
{
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    QList<QString> allTvShows = DatabaseManagerSingleton::Instance().getListOfAllTvShows();

    QString tvShow0 = "Game of Thrones";
    QString tvShow1 = "Mr. Robot";

    QCOMPARE(allTvShows[0],tvShow0);
    QCOMPARE(allTvShows[1],tvShow1);
}

void TestDatabaseManager::TestGetListOfCachedTvShows()
{
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    DatabaseManagerSingleton::Instance().emptyCache();

    TvShow tvShow = DatabaseManagerSingleton::Instance().getTvShow("Mr. Robot");

    QList<QString> cachedTvShows = DatabaseManagerSingleton::Instance().getListOfCachedTvShows();

    QString tvShow0 = "Mr. Robot";

    // Validate there is only one entry.
    QCOMPARE(cachedTvShows.length(),1);

    QCOMPARE(cachedTvShows[0],tvShow0);
}

void TestDatabaseManager::TestModifyTvShow()
{
    // Set up strings to compare against.
    QString name = "Mr. Robot";
    QString expectedTmdbLink = "https://www.themoviedb.org/tv/62560-mr-robot";
    QString expectedGraphicLink = "https://image.tmdb.org/t/p/w600_and_h900_bestv2/esN3gWb1P091xExLddD2nh4zmi3.jpg";

    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    TvShow &tvShow = DatabaseManagerSingleton::Instance().getTvShow(name);

    QCOMPARE(tvShow.name.toLower(), name.toLower());
    QCOMPARE(tvShow.tmdbLink.toLower(), expectedTmdbLink.toLower());
    QCOMPARE(tvShow.graphicLink.toLower(), expectedGraphicLink.toLower());

    QMap<int, Season> &seasons = tvShow.getSeasons();

    QCOMPARE(seasons.count(), 1);

    Season &season = seasons[66343];

    QString expectedSeasonName = "season_0.0";

    QCOMPARE(season.name, expectedSeasonName);
    QCOMPARE(season.seasonId, 66343);
    QCOMPARE(season.seasonNumber, 0);

    QMap<int, Episode> &episodes = season.getEpisodes();

    QCOMPARE(episodes.count(), 2);

    Episode &episode = episodes[1203464];

    QString expectedEpisodeName = "Hacking Robot 101";
    QString expectedEpisodeSummary = "In the premiere of the \"Mr. Robot\" after show, the series' cast and creator discuss the Season 2 premiere and field fan questions.";

    QCOMPARE(episode.episodeId, 1203464);
    QCOMPARE(episode.episodeNumber, 2);
    QCOMPARE(episode.name, expectedEpisodeName);
    QCOMPARE(episode.summary, expectedEpisodeSummary);

    // Modify top level tvshow, and verify change.
    QString updatedTvShowName = "Updated TV name";
    tvShow.name = updatedTvShowName;

    // Modify, and get from cache to see if it udpated.
    QString updatedEpisodeName = "Updated Ep name";
    tvShow.getSeasons()[66343].getEpisodes()[1203464].name = updatedEpisodeName;

    QCOMPARE(tvShow.getSeasons()[66343].getEpisodes()[1203464].name, updatedEpisodeName);

    TvShow &tvShow2 = DatabaseManagerSingleton::Instance().getTvShow(name);
    QCOMPARE(tvShow2.name, updatedTvShowName);
    QCOMPARE(tvShow.getSeasons()[66343].getEpisodes()[1203464].name, updatedEpisodeName);

    QMap<int, Season> &seasons2 = tvShow2.getSeasons();

    Season &season2 = seasons2[0];

    QMap<int, Episode> &episodes2 = season2.getEpisodes();

    Episode &episode2 = episodes2[0];

    QString updatedEpisode2Name = "Updated Ep2 name";

    episode2.name = updatedEpisode2Name;

    TvShow &tvShow3 = DatabaseManagerSingleton::Instance().getTvShow(name);
    QCOMPARE(tvShow3.getSeasons()[0].getEpisodes()[0].name, updatedEpisode2Name);
}
