/* Implementation of the user class.
 *
 * @author Allan Haywood
 */
#include "user.h"
#include "common.h"

#include<QList>

User::User()
{
    username = "";
    firstName = "";
    lastName = "";
    email = "";
    passwordHash = "";
    _isAdmin = false;
    watchedEpisodes = QMap<QString, EpisodeIdentifier>();
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    _isAdmin = false;
    watchedEpisodes = QMap<QString, EpisodeIdentifier>();
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, QList<EpisodeIdentifier> watchedEpisodes)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordHash;
    addWatchedEpisodeList(watchedEpisodes);

    _isAdmin = false;
}


User::User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, bool isAdmin)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordHash;
    watchedEpisodes = QMap<QString, EpisodeIdentifier>();

    _isAdmin = isAdmin;
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash, QList<EpisodeIdentifier> watchedEpisodes, bool isAdmin)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    addWatchedEpisodeList(watchedEpisodes);

    _isAdmin = isAdmin;
}

bool User::isAdmin()
{
    return _isAdmin;
}

/**
 * @brief User::addWatchedEpisode Adds a watched episode, no error if it was already marked as watched.
 * @param episode The episode identifier for the watched episode.
 */
void User::addWatchedEpisode(EpisodeIdentifier episode)//adds an episode to the users watched list
{
    watchedEpisodes.insert(episode.getKey(), episode);
}

/**
 * @brief User::removeWatchedEpisode Removes watched episode, no error if episode was not marked as watched.
 * @param episode The episode to remove from watched episodes.
 */
void User::removeWatchedEpisode(EpisodeIdentifier episode)//removes an episode from the users watched list
{
    watchedEpisodes.remove(episode.getKey());
}

/**
 * @brief User::hasUserWatchedThisEpisode Determines if the user has watched the specified episode.
 * @param episode The episode to check if they have watched.
 * @return True if the episode was watched by this user, false if not.
 */
bool User::hasUserWatchedThisEpisode(EpisodeIdentifier episode)
{
    return watchedEpisodes.contains(episode.getKey());
}

/**
 * @brief User::hasTheUserWatchedAnything Checks if the user has watched any episodes.
 * @return True, if the user has watched at least one thing, false if not.
 */
bool User::hasTheUserWatchedAnything()
{
    if(watchedEpisodes.size() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * @brief User::addWatchedEpisodeList Adds the provided episode list to the watched episodes. No error if already marked as watched.
 * @param episodeList The list of episodes to mark as watched.
 */
void User::addWatchedEpisodeList(QList<EpisodeIdentifier> episodeList)
{
    foreach(const EpisodeIdentifier &episode, episodeList)
    {
        watchedEpisodes.insert(episode.getKey(), episode);
    }
}

/**
 * @brief User::removeWatchedEpisodeList Removes all episodes in the provided list. No error if episode is not marked as watched.
 * @param episodeList The list of episodes to remove.
 */
void User::removeWatchedEpisodeList(QList<EpisodeIdentifier> episodeList)
{
    foreach(const EpisodeIdentifier &episode, episodeList)
    {
        watchedEpisodes.remove(episode.getKey());
    }
}

/**
 * @brief User::inspectWatchedEpisodes Returns a copy of the watched episodes for this uer.
 * @return A QList of the episode identifiers that this user has watched.
 */
QList<EpisodeIdentifier> User::inspectWatchedEpisodes()
{
    return watchedEpisodes.values();
}
