/* Header for the jsonconnection class.
 *
 * @author Allan Haywood
 */

#ifndef JSONCONNECTION_H
#define JSONCONNECTION_H
#include "iconnection.h"
#include "tvshow.h"
#include "user.h"

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>

class JsonConnection : public IConnection
{
public:
    QJsonObject json;

    JsonConnection();

    JsonConnection(QString pathToJson);

    QString getPathToJson();

    void setPathToJson(QString newPathToJson);

    // @throws NotFound when TvShow is not found.
    TvShow getTvShow(QString name);

    void addTvShow(TvShow tvShow);

    // @throws NotFound when user is not found.
    User getUser(QString username);

    // @throws NotFound when user is not found.
    QString getUserNameByEmail(QString email);

    void addUser(User user);

    void removeUser(QString username);

    bool usernameExists(QString username);

    bool emailExists(QString email);

    QList<QString> getListOfAllTvShows();

    void addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review);
    void addEpisodeComment(EpisodeIdentifier episodeIdentifier, Comment comment);

    // Normally the loadJson and saveJson wouldn't be public, but they have been made public,
    // for easy access by QTest. TODO: Investigate alternative access. ex. Via Friendly classes.
    void loadJson();

    void saveJson();

private:
    const QString JSON_USER_ARRAY_NAME = "User";
    const QString JSON_TVSHOW_ARRAY_NAME = "TvShow";

    QString pathToJson;

    QJsonArray getTopLevelJsonArray(QString jsonArrayName);
    QMap<int, Season> getSeasons(QJsonArray jsonSeasons);
    Season getSeason(QJsonObject jsonSeason);
    QMap<int, Episode> getEpisodes(QJsonArray jsonEpisodes);
    Episode getEpisode(QJsonObject jsonEpisode);
    QMap<QString, Review> getReviews(QJsonValue jsonReviews);
    QList<Comment> getComments(QJsonValue jsonComments);

    QJsonObject tvShowToJsonObject(TvShow tvShow);

    QJsonArray seasonsToJsonArray(QVector<Season> seasons);
    QJsonValue seasonToJsonValue(Season season);

    QJsonArray episodesToJsonArray(QVector<Episode> episodes);
    QJsonValue episodeToJsonValue(Episode episode);

    QJsonArray reviewsToJsonArray(QList<Review> reviews);
    QJsonValue reviewToJsonValue(Review review);

    QJsonArray commentsToJsonArray(QList<Comment> comments);
    QJsonValue commentToJsonValue(Comment comment);

    QJsonObject userToJsonObject(User user);
};

#endif // JSONCONNECTION_H
