/* Header for the database manager class.
 *
 * @author Allan Haywood
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "singleton.h"
#include "jsonconnection.h"

#include <QObject>
#include <QMap>
#include <QList>


class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    DatabaseManager();
    DatabaseManager(QString jsonPath);

    // IConnection equivalents, method names are the same, but no need to provide a reference,
    // in addition, instead of return void, it returns a reference of the object.
    const TvShow inspectTvShow(QString name);

    // @throws NotFound
    const TvShow inspectTvShowById(int tvShowId);

    // @throws NotFound when user does not exist.
    const User inspectUser(QString username);

    // @throws NotFound when user does not exist.
    const User inspectUserByEmail(QString email);

    void addUser(User user);

    void removeUser(QString username);

    // @throws NotFound when user does not exist.
    //void updateUser(User user);

    bool usernameExists(QString username);

    bool emailExists(QString email);

    QList<QString> getListOfAllTvShows();

    QList<QString> getListOfAllUsers();

    QList<QString> getListOfCachedTvShows();

    QList<QString> getListOfCachedUsers();

    // @throws NotFound
    QString getTvShowNameById(int showId);

    // @throws NotFound
    void addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review);

    // @throws NotFound
    void addEpisodeComment(EpisodeIdentifier episodeIdentifier, Comment comment);

    //@todo Add get list of watched tvshows, once watched functionality is added.

    // Used for testing only.
    void emptyCache();

signals:
    void notify();

private:
    QMap<QString, TvShow> tvShowMap;
    QMap<QString, User> userMap;

    DatabaseManager(DatabaseManager const&);    // copy constructor hidden
    //DatabaseManager& operator=(DatabaseManager const&);  // assign op hidden

    JsonConnection connection;
};

#endif // DATABASEMANAGER_H
