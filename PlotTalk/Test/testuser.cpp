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

    QList<EpisodeIdentifier> episodeGroup;
    episodeGroup.append(episode1);
    episodeGroup.append(episode2);
    episodeGroup.append(episode3);

    User user = User(username, firstName, lastName, email, passwordHash);
    QCOMPARE(user.hasTheUserWatchedAnything(), false);//the user has not watched any shows

    user.addWatchedEpisode(episode1);//adding an episode
    QCOMPARE(user.hasUserWatchedThisEpisode(episode1), true);
    QCOMPARE(user.hasTheUserWatchedAnything(), true);//now the user has watched a show

    user.addWatchedEpisode(episode2);//adding a second episode
    user.addWatchedEpisode(episode3);//adding a third episode

    QCOMPARE(user.hasUserWatchedThisEpisode(episode2), true);

    user.addWatchedEpisodeList(episodeGroup);//one or more episodes already exist

    QCOMPARE(user.hasUserWatchedThisEpisode(episode3), true);

    user.removeWatchedEpisode(episode1);//removing the first episode
    user.removeWatchedEpisode(episode1);//episode already removed

    QCOMPARE(user.hasTheUserWatchedAnything(), true);//the user has watched shows

    user.addWatchedEpisode(episode2);//episode already added

    user.removeWatchedEpisode(episode2);//remove second episode

    user.removeWatchedEpisode(episode3);//remove third episode
    user.removeWatchedEpisode(episode3);//episode already removed

    QCOMPARE(user.hasTheUserWatchedAnything(), false);//the user has watched no shows now

    user.addWatchedEpisodeList(episodeGroup);//adds a list of episode ids to the user
    user.addWatchedEpisodeList(episodeGroup);//list already addedadded episodes to list

    user.removeWatchedEpisode(episode1);
    QCOMPARE(user.hasTheUserWatchedAnything(), true); // There should still be episodes left.

    user.removeWatchedEpisode(episode2);
    QCOMPARE(user.hasTheUserWatchedAnything(), true); // There should still be episodes left.

    user.removeWatchedEpisode(episode3);//successfully remove all the episodes
    QCOMPARE(user.hasTheUserWatchedAnything(),false);//the user has watched no shows now

    user.removeWatchedEpisode(episode3);//cannot remove an episode that isn't in the user
    QCOMPARE(user.hasTheUserWatchedAnything(),false);//the user has watched no shows now
}
