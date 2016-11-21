/* Test the User class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include "testuser.h"
void TestUser::TestUserDefaultConstructor1()
{

    User user = User();
    QVERIFY(user.username.isEmpty());
    QVERIFY(user.firstName.isEmpty());
    QVERIFY(user.lastName.isEmpty());
    QVERIFY(user.email.isEmpty());
    QVERIFY(user.passwordHash.isEmpty());
    QVERIFY(false == user.isAdmin());
}

void TestUser::TestUserConstructor2()
{
    // Set up strings to compare against.
    QString username = "bsmith";
    QString firstName = "Bob";
    QString lastName = "Smith";
    QString email = "bsmith@gmail.com";
    QString passwordHash = "badpasswordhash";

    User user = User(username, firstName, lastName, email, passwordHash);
    QCOMPARE(username, user.username);
    QCOMPARE(firstName, user.firstName);
    QCOMPARE(lastName, user.lastName);
    QCOMPARE(email, user.email);
    QCOMPARE(passwordHash, user.passwordHash);
    QVERIFY(false == user.isAdmin());
}

void TestUser::TestUserConstructor3()
{
    // Set up strings to compare against.
    QString username = "bsmith";
    QString firstName = "Bob";
    QString lastName = "Smith";
    QString email = "bsmith@gmail.com";
    QString passwordHash = "badpasswordhash";

    User user = User(username, firstName, lastName, email, passwordHash, true);
    QCOMPARE(username, user.username);
    QCOMPARE(firstName, user.firstName);
    QCOMPARE(lastName, user.lastName);
    QCOMPARE(email, user.email);
    QCOMPARE(passwordHash, user.passwordHash);
    QVERIFY(true == user.isAdmin());
}

void TestUser::TestsForWatchedList()
{
    QString username = "bsmith";
    QString firstName = "Bob";
    QString lastName = "Smith";
    QString email = "bsmith@gmail.com";
    QString passwordHash = "badpasswordhash";

    EpisodeIdentifier episode1;
    episode1.episodeId=1;
    episode1.seasonId=2;
    episode1.tvShowId=3;

    EpisodeIdentifier episode2;
    episode2.episodeId=2;
    episode2.seasonId=3;
    episode2.tvShowId=4;

    EpisodeIdentifier episode3;
    episode3.episodeId=3;
    episode3.seasonId=4;
    episode3.tvShowId=2;
    int location;

    QList<EpisodeIdentifier> episodeGroup;
    episodeGroup.append(episode1);
    episodeGroup.append(episode2);
    episodeGroup.append(episode3);

    User user = User(username, firstName, lastName, email, passwordHash);
    QCOMPARE(user.HasTheUserWatchedAnything(), false);//the user has not watched any shows
    QCOMPARE(user.addWatchedEpisode(episode1), true);//adding an episode
    QCOMPARE(user.HasUserWatchedThisEpisode(episode1,location),true);
    QCOMPARE(location,0);
    QCOMPARE(user.HasTheUserWatchedAnything(), true);//now the user has watched a show
    QCOMPARE(user.addWatchedEpisode(episode2), true);//adding a second episode
    QCOMPARE(user.addWatchedEpisode(episode3), true);//adding a third episode
    QCOMPARE(user.HasUserWatchedThisEpisode(episode2,location),true);
    QCOMPARE(location,1);
    QCOMPARE(user.AddWatchedEpisodeList(episodeGroup),false);//one or more episodes already exist
    QCOMPARE(user.HasUserWatchedThisEpisode(episode3,location),true);
    QCOMPARE(location,2);
    QCOMPARE(user.removeWatchedEpisode(episode1), true);//removing the first episode
    QCOMPARE(user.removeWatchedEpisode(episode1), false);//episode already removed
    QCOMPARE(user.HasTheUserWatchedAnything(), true);//the user has watched shows
    QCOMPARE(user.addWatchedEpisode(episode2), false);//episode already added
    QCOMPARE(user.removeWatchedEpisode(episode2), true);//remove second episode
    QCOMPARE(user.removeWatchedEpisode(episode3), true);//remove third episode
    QCOMPARE(user.removeWatchedEpisode(episode3), false);//episode already removed
    QCOMPARE(user.HasTheUserWatchedAnything(),false);//the user has watched no shows now
    QCOMPARE(user.AddWatchedEpisodeList(episodeGroup), true);//adds a list of episode ids to the user
    QCOMPARE(user.AddWatchedEpisodeList(episodeGroup),false);//list already addedadded episodes to list
    QCOMPARE(user.removeWatchedEpisode(episode1), true);
    QCOMPARE(user.removeWatchedEpisode(episode2), true);
    QCOMPARE(user.removeWatchedEpisode(episode3), true);//successfully remove all the episodes
    QCOMPARE(user.removeWatchedEpisode(episode3), false);//cannot remove an episode that isn't in the user
}

