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
    JsonConnection(QString pathToJson);

    QString getPathToJson();

    void getTvShow(QString name, TvShow &tvShow);

    void getUser(QString username, User &user);

    bool usernameExists(QString username);

    bool emailExists(QString email);

private:
    QString pathToJson;

    QJsonObject jsonObject;

    QJsonObject loadJson(QString pathToJson);

    QJsonArray getTopLevelJsonArray(QString jsonArrayName);
};

#endif // JSONCONNECTION_H
