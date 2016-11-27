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
    QList<EpisodeIdentifier> watchedEpisodes;

    // TODO: Complete creating User object.
    User();
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash);
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, bool isAdmin);
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, QList<EpisodeIdentifier> watchedEpisodes);
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, QList<EpisodeIdentifier> watchedEpisodes, bool isAdmin);

    bool isAdmin();
    bool addWatchedEpisode(EpisodeIdentifier episode);
    bool removeWatchedEpisode(EpisodeIdentifier episode);
    bool hasTheUserWatchedAnything();
    bool hasUserWatchedThisEpisode(EpisodeIdentifier episode, int &location);
    bool addWatchedEpisodeList(QList<EpisodeIdentifier> episodeList);
private:
    bool _isAdmin;


};

#endif // USER_H
