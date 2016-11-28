/* Header for the User class.
 *
 * @author Allan Haywood
 */
#ifndef USER_H
#define USER_H

#include "common.h"
#include <QString>
#include <QList>
#include <QMap>

class User
{
public:

    QString username;
    QString firstName;
    QString lastName;
    QString email;
    QString passwordHash;

    // TODO: Complete creating User object.
    User();
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash);
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, bool isAdmin);
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, QList<EpisodeIdentifier> watchedEpisodes);
    User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, QList<EpisodeIdentifier> watchedEpisodes, bool isAdmin);

    bool isAdmin();

    void addWatchedEpisode(EpisodeIdentifier episode);
    void removeWatchedEpisode(EpisodeIdentifier episode);
    bool hasUserWatchedThisEpisode(EpisodeIdentifier episode);
    void addWatchedEpisodeList(QList<EpisodeIdentifier> episodeList);
    void removeWatchedEpisodeList(QList<EpisodeIdentifier> episodeList);

    bool hasTheUserWatchedAnything();
    QList<EpisodeIdentifier> inspectWatchedEpisodes();
private:
    QMap<QString, EpisodeIdentifier> watchedEpisodes;
    bool _isAdmin;


};

#endif // USER_H
