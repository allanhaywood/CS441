/* Header for the jsonconnection class.
 *
 * @author Allan Haywood
 */

#ifndef JSONCONNECTION_H
#define JSONCONNECTION_H
#include <QString>
#include <QJsonObject>

#include "iconnection.h"
#include "tvshow.h"
#include "user.h"

class JsonConnection : public IConnection
{
public:
    QJsonObject json;

    JsonConnection();

    JsonConnection(QString pathToJson);

    QString getPathToJson();

    void setPathToJson(QString newPathToJson);

    void getTvShow(QString name, TvShow &tvShow);

    //void addTvShow(TvShow tvShow);

    void getUser(QString username, User &user);

    void addUser(User user);

    void removeUser(QString username);

    bool usernameExists(QString username);

    bool emailExists(QString email);

    // Normally the loadJson and saveJson wouldn't be public, but they have been made public,
    // for easy access by QTest. TODO: Investigate alternative access. ex. Via Friendly classes.
    void loadJson();

    void saveJson();

private:
    const QString JSON_USER_ARRAY_NAME = "User";
    const QString JSON_TVSHOW_ARRAY_NAME = "TvShow";

    QString pathToJson;

    QJsonArray getTopLevelJsonArray(QString jsonArrayName);

    // IConnection interface

};

#endif // JSONCONNECTION_H
