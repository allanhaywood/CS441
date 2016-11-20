/* Header for the database manager class.
 *
 * @author Allan Haywood
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QMap>
#include <QList>

#include "user.h"
#include "singleton.h"
#include "jsonconnection.h"

class DatabaseManager
{
public:
    DatabaseManager();
    DatabaseManager(QString jsonPath);

    // IConnection equivalents, method names are the same, but no need to provide a reference,
    // in addition, instead of return void, it returns a reference of the object.
    TvShow& getTvShow(QString name);

    // @throws NotFound when user does not exist.
    User& getUser(QString username);

    // @throws NotFound when user does not exist.
    User& getUserByEmail(QString email);

    void addUser(User user);

    void removeUser(QString username);

    // @throws NotFound when user does not exist.
    void updateUser(User user);

    bool usernameExists(QString username);

    bool emailExists(QString email);

    QList<QString> getListOfAllTvShows();

    QList<QString> getListOfCachedTvShows();

    QString getTvShowNameById(int tvShowId);

    void addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review);
    void addEpisodeComment(EpisodeIdentifier episodeIdentifier, Comment comment);

    //@todo Add get list of watched tvshows, once watched functionality is added.

    // Used for testing only.
    void emptyCache();

    QList<User> getAllUsers();

private:
    QMap<QString, TvShow> tvShowMap;
    QMap<QString, User> userMap;

    DatabaseManager(DatabaseManager const&);    // copy constructor hidden
    //DatabaseManager& operator=(DatabaseManager const&);  // assign op hidden

    JsonConnection connection;
};

#endif // DATABASEMANAGER_H
