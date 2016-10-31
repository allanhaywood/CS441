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

#include <QMap>
#include <QDebug>

/**
 * @brief DatabaseManager::DatabaseManager Default constructor, currently defaults to using Json connection.
 */
DatabaseManager::DatabaseManager() : connection(":/json/Json/test.json")
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

    // @todo Add caching so that it doesn't call getTvShow if it isn't needed.
    connection.getTvShow(name, tvShowMap[name]);

    return tvShowMap[name];
}

User &DatabaseManager::getUser(QString username)
{
    // @todo Add caching so that it doesn't call getUser if it isn't needed.
    connection.getUser(username, userMap[username]);

    return userMap[username];
}

bool DatabaseManager::usernameExists(QString username)
{
    return connection.usernameExists(username);
}

bool DatabaseManager::emailExists(QString email)
{
    return connection.emailExists(email);
}
