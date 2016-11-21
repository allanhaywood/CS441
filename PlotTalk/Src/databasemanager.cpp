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

#include <QMap>
#include <QDebug>

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
 */
TvShow &DatabaseManager::getTvShow(QString name)
{
    // @todo Determine how to decide to use either json or mysql connection at runtime,
    // or at the very least, a single location to choose which one.

    if ( tvShowHash.contains(name) )
    {
        return tvShowHash[name];
    }
    else
    {
        tvShowHash[name] = connection.getTvShow(name);
    }

    return tvShowHash[name];
}

/**
 * @brief DatabaseManager::getUser Returns the specified user.
 * @param username The username of the user to return.
 * @return The user requested.
 *
 * @throws NotFound if user is not found.
 */
User &DatabaseManager::getUser(QString username)
{
    // @todo Add caching so that it doesn't call getUser if it isn't needed.

    if ( userHash.contains(username) )
    {
        return userHash[username];
    }
    else
    {
        userHash[username] = connection.getUser(username);
    }

    return userHash[username];
}

/**
 * @brief DatabaseManager::getUserByEmail Gets the user by email address.
 * @param email The email to search for.
 * @return The user requested.
 *
 * @throws NotFound if user is not found.
 */
User &DatabaseManager::getUserByEmail(QString email)
{
    // @todo Add caching so that it doesn't call getUser if it isn't needed.
    QString username = connection.getUserNameByEmail(email);

    return getUser(username);
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
    userHash[user.username] = user;
}

/**
 * @brief DatabaseManager::removeUser Removes the specified user.
 * @param username The user to remove.
 */
void DatabaseManager::removeUser(QString username)
{
    connection.removeUser(username);
    userHash.remove(username);
}

/**
 * @brief DatabaseManager::updateUser Updates the provided user to match the provided user.
 * @param user The new state of the user to store.
 *
 * @throws NotFound if the specified user is not found.
 */
void DatabaseManager::updateUser(User user)
{
    if (! connection.usernameExists(user.username))
    {
        throw NotFound{};
    }

    userHash[user.username].firstName = user.firstName;
    userHash[user.username].lastName = user.lastName;
    userHash[user.username].passwordHash = user.passwordHash;
    userHash[user.username].email = user.email;

    connection.removeUser(user.username);
    connection.addUser(user);
}

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
    return connection.getListOfAllTvShows();
}

/**
 * @brief DatabaseManager::getListOfAllUsers Returns a list of all users recorded at the current connection.
 * @return List of user objects.
 */
QList<User> DatabaseManager::getAllUsers()
{
    return userHash.values();
}

/**
 * @brief DatabaseManager::getListOfCachedTvShows Returns a list of all locally cached tvshows.
 * @return List of tvshow names.
 */
QList<QString> DatabaseManager::getListOfCachedTvShows()
{
    return tvShowHash.keys();
}

QString DatabaseManager::getTvShowNameById(int tvShowId)
{
    foreach (TvShow tvShow, tvShowHash.values())
    {
        if (tvShow.showId == tvShowId)
        {
            return tvShow.name;
        }
    }

    throw NotFound{};
}

void DatabaseManager::addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review)
{
    QString tvShowName = getTvShowNameById(episodeIdentifier.episodeId);
    tvShowHash[tvShowName].addEpisodeReview(episodeIdentifier, review);
    connection.addEpisodeReview(episodeIdentifier, review);
}

void DatabaseManager::addEpisodeComment(EpisodeIdentifier episodeIdentifier, Comment comment)
{
    QString tvShowName = getTvShowNameById(episodeIdentifier.episodeId);
    tvShowHash[tvShowName].addEpisodeComment(episodeIdentifier, comment);
    connection.addEpisodeComment(episodeIdentifier, comment);
}

/**
 * @brief DatabaseManager::emptyCache Used for testing only, to empty cache.
 */
void DatabaseManager::emptyCache()
{
    tvShowHash.clear();
    userHash.clear();
}
