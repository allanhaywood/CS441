/* Implementation for the Database Manager class.
 * The default constructor will have a default connection it will use, currently json.
 *  this provides for a single location to be able to define which connection to use.
 *  @todo Potentially move this selection into either a config file, or runtime selection.
 *
 *  @todo Add observer, to allow users of databasemanager know when an update to data content
 *  is available.
 *
 *  @todo Add caching, so that calls to provide data will be answered with cached data.
 *  which will vastly speed up response time, and minimize hitting the database.
 *
 *  @todo Add mutex for data modification (ex. prevent reading/writing when updates are occuring.
 *
 *  @todo Add polling, so that datastore updates are materialized here, and alerted via observer.
 *
 *  @todo Make database manager a "listener" of any datastore class changes, so that it immediately,
 *  saves any changes into the datastore.
 *
 * @author Allan Haywood
 */
#include "databasemanager.h"
#include "jsonconnection.h"
#include "plottalkexceptions.h"
#include "user.h"
#include "common.h"

#include <QDebug>
#include <QList>

/**
 * @brief DatabaseManager::DatabaseManager Default constructor, currently defaults to using Json connection.
 */
DatabaseManager::DatabaseManager() : connection()
{
}

/**
 * @brief DatabaseManager::DatabaseManager Constructor that allows the json path to be provided.
 * @param jsonPath The path to the json file to use, can either be on file system, or in resources.
 */
DatabaseManager::DatabaseManager(QString jsonPath) : connection(jsonPath)
{
}


/**
 * @brief DatabaseManager::getTvShow Updates the provided TvShow reference to the requested tvshow.
 * @param name The name of the tvshow to fetch.
 * @return A reference to the TvShow object.
 *
 * @throws NotFound
 */
const TvShow DatabaseManager::inspectTvShow(QString name)
{

    // If the tvshow is already in the cache, use that copy instead.
    // Otherwise, get it from the currently active connection.
    if ( tvShowMap.contains(name) )
    {
        return tvShowMap[name];
    }
    else
    {
        tvShowMap[name] = connection.getTvShow(name);
    }

    return tvShowMap[name];
}

/**
 * @brief DatabaseManager::getTvShowById Retrieves a reference to a tvshow by Id instead of name.
 * @param tvShowId The tvshow id to find.
 * @return A reference to the tvshow.
 *
 * @throws NotFound
 */
const TvShow DatabaseManager::inspectTvShowById(int tvShowId)
{
    return inspectTvShow(connection.getTvShowNameById(tvShowId));
}

/**
 * @brief DatabaseManager::getUser Returns the specified user.
 * @param username The username of the user to return.
 * @return The user requested.
 *
 * @throws NotFound if user is not found.
 */
const User DatabaseManager::inspectUser(QString username)
{
    // If the user is already in the local cache, return from there.
    // If not, get user from connection.
    if ( userMap.contains(username) )
    {
        return userMap[username];
    }
    else
    {
        userMap[username] = connection.getUser(username);
    }

    return userMap[username];
}

/**
 * @brief DatabaseManager::getUserByEmail Gets the user by email address.
 * @param email The email to search for.
 * @return The user requested.
 *
 * @throws NotFound if user is not found.
 */
const User DatabaseManager::inspectUserByEmail(QString email)
{
    QString username = connection.getUserNameByEmail(email);

    return inspectUser(username);
}

/**
 * @brief DatabaseManager::addUser Adds the provided user.
 * @param user The user to add.
 *
 * @throws AlreadyExists if user already exists.
 */
void DatabaseManager::addUser(User user)
{
    // Will throw exception if user already exists.
    connection.addUser(user);

    // Will only get here if user does not already exist,
    // preventing accidental modification.
    userMap[user.username] = user;
}

/**
 * @brief DatabaseManager::removeUser Removes the specified user.
 * @param username The user to remove.
 */
void DatabaseManager::removeUser(QString username)
{
    connection.removeUser(username);
    userMap.remove(username);
}

/**
 * @brief DatabaseManager::updateUser Updates the provided user to match the provided user.
 * @param user The new state of the user to store.
 *
 * @throws NotFound if the specified user is not found.
 */
/*
void DatabaseManager::updateUser(User user)
{
    if (! connection.usernameExists(user.username))
    {
        throw NotFound("User name not found:" + user.username);
    }

    userHash[user.username].firstName = user.firstName;
    userHash[user.username].lastName = user.lastName;
    userHash[user.username].passwordHash = user.passwordHash;
    userHash[user.username].email = user.email;

    connection.removeUser(user.username);
    connection.addUser(user);
}
*/

/**
 * @brief DatabaseManager::usernameExists Checks if the specified user already exists.
 * @param username The username to check if it already exists.
 * @return True if the user exists, false, if it doesn't.
 */
bool DatabaseManager::usernameExists(QString username)
{
    return connection.usernameExists(username);
}

/**
 * @brief DatabaseManager::emailExists Checks if the specified email already exists.
 * @param email The email to check if it already exists.
 * @return True if the email exists, false if it doesn't.
 */
bool DatabaseManager::emailExists(QString email)
{
    return connection.emailExists(email);
}

/**
 * @brief DatabaseManager::getListOfAllTvShows Returns a list of all tvshows recorded at the current connection.
 * @return List of tvshow names.
 */
QList<QString> DatabaseManager::getListOfAllTvShows()
{
    QList<QString> list = connection.getListOfAllTvShows();
    qSort(list);
    return list;
}

/**
 * @brief DatabaseManager::getListOfAllUsers Returns a list of all users recorded at the current connection.
 * @return List of user objects.
 */
QList<QString> DatabaseManager::getListOfAllUsers()
{
    QList<QString> list = connection.getListOfAllUsers();
    qSort(list);
    return list;
}

/**
 * @brief DatabaseManager::getListOfCachedTvShows Returns a list of all locally cached tvshows.
 * @return List of tvshow names.
 */
QList<QString> DatabaseManager::getListOfCachedTvShows()
{
    QList<QString> list = tvShowMap.keys();
    qSort(list);
    return list;
}

/**
 * @brief DatabaseManager::getListOfCachedUsers Returns a list of all the locally cached users.
 * @return List of user names.
 */
QList<QString> DatabaseManager::getListOfCachedUsers()
{
    QList<QString> list = userMap.keys();
    qSort(list);
    return list;
}

/**
 * @brief DatabaseManager::getTvShowNameById Gets the tvshow name by its id.
 * @param showId The show id to lookup the name for.
 * @return The name of the tvshow.
 */
QString DatabaseManager::getTvShowNameById(int showId)
{
    qDebug() << "Looking for show id:" << showId;

    // Look in cache first.
    foreach (const TvShow &tvShow, tvShowMap.values())
    {
        if ( tvShow.showId == showId )
        {
            return tvShow.name;
        }
    }

    // If not found in the cache, check the database connection.
    return connection.getTvShowNameById(showId);
}

/**
 * @brief DatabaseManager::addEpisodeReview Adds the specified review to the specified episode.
 * @param episodeIdentifier The specific episode to add the review to.
 * @param review The review to add.
 *
 * Adds the review to the local cache, and the datastore.
 */
void DatabaseManager::addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review)
{
    // Get the tvshow name using the tvshow id.
    QString tvShowName = inspectTvShowById(episodeIdentifier.tvShowId).name;

    // Call addEpisodeReview on the tvshow itself to update the local copy.
    tvShowMap[tvShowName].addEpisodeReview(episodeIdentifier, review);

    // Call addEpisode review to update the datastore.
    connection.addEpisodeReview(episodeIdentifier, review);

    // Notify any listeners (ex. dashboard) that an update has occured.
    emit notify();
}

/**
 * @brief DatabaseManager::addEpisodeComment Adds the speciifed comment to the specified episode.
 * @param episodeIdentifier The specific episode to add the reivew to.
 * @param comment The comment to add.
 */
void DatabaseManager::addEpisodeComment(EpisodeIdentifier episodeIdentifier, Comment comment)
{
    // Get the tvshow name using the tvshow id.
    QString tvShowName = inspectTvShowById(episodeIdentifier.tvShowId).name;

    // Call addEpisodeComment on the tvshow itself to udpate the local copy.
    tvShowMap[tvShowName].addEpisodeComment(episodeIdentifier, comment);

    // Call addEpisode review to update the datastore.
    connection.addEpisodeComment(episodeIdentifier, comment);

    // Notify any listeners (ex. dashboard) that an udpate has occured.
    emit notify();
}

/**
 * @brief DatabaseManager::addWatchedEpisode Adds the specified episode to the specified users watched episodes list.
 * @param episodeIdentifier The episode to add to the users watched shows.
 * @param username The username to add the watched episode to.
 */
void DatabaseManager::addWatchedEpisode(EpisodeIdentifier episodeIdentifier, QString username)
{
    // Add a watched episode to the local copy of the specified user.
    userMap[username].addWatchedEpisode(episodeIdentifier);

    // Add the watched episode to the user in the datastore.
    connection.addWatchedEpisode(episodeIdentifier, username);
}

/**
 * @brief DatabaseManager::removeWatchedEpisode Removes the specified episode from the specified users watched episodes list.
 * @param episodeIdentifier The episode to remove from the users watched shows.
 * @param username The username to remove the watched episode from.
 */
void DatabaseManager::removeWatchedEpisode(EpisodeIdentifier episodeIdentifier, QString username)
{
    // Remove the watched episode from the local copy of the specified user.
    userMap[username].removeWatchedEpisode(episodeIdentifier);

    // Remove the watched episode from the user in the datastore.
    connection.removeWatchedEpisode(episodeIdentifier, username);
}

/**
 * @brief DatabaseManager::getListOfWatchedTvShowNamesForUser Returns a list of tvshow names for the tvshows the specified username has watched.
 * @param username The username to lookup.
 * @return List of tvshow names that have been watched by the specified user.
 */
QList<QString> DatabaseManager::getListOfWatchedTvShowNamesForUser(QString username)
{
    QList<QString> watchedTvShowNames;

    User user = inspectUser(username);

    // Get the list of watched tvshow names for the user.
    foreach(const EpisodeIdentifier &episodeIdentifier, user.inspectWatchedEpisodes())
    {
        // Don't allow duplicates.
        if (!watchedTvShowNames.contains(getTvShowNameById(episodeIdentifier.tvShowId)))
        {
            watchedTvShowNames.append(getTvShowNameById(episodeIdentifier.tvShowId));
        }
    }

    // Sort the result so it shows up in the dashboard alphabetically.
    qSort(watchedTvShowNames);

    return watchedTvShowNames;
}

/**
 * @brief DatabaseManager::emptyCache Used for testing only, to empty cache.
 */
void DatabaseManager::emptyCache()
{
    tvShowMap.clear();
    userMap.clear();
}

