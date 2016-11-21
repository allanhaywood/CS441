/* Header for the User class.
 *
 * @author Allan Haywood
 */
#ifndef USER_H
#define USER_H

#include "common.h"
#include <QString>
#include <QList>

class User
{
public:

    QString username;
    QString firstName;
    QString lastName;
    QString email;
    QString passwordHash;
    QList<EpisodeIdentifier> userWatched;

    // TODO: Complete creating User object.
    User();
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash);
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, bool isAdmin);

    bool isAdmin();
    bool addWatchedEpisode(EpisodeIdentifier episode);
    bool removeWatchedEpisode(EpisodeIdentifier episode);
    bool HasTheUserWatchedAnything();
    bool HasUserWatchedThisEpisode(EpisodeIdentifier episode, int &location);

private:
    bool _isAdmin;


};

#endif // USER_H
