#ifndef JSONCONNECTION_H
#define JSONCONNECTION_H
#include <QString>
#include <QJsonObject>

#include "connection.h"
#include "tvshow.h"

class JsonConnection : public Connection
{
public:
    JsonConnection(QString pathToJson);

    QString getPathToJson();

    void getTvShow(QString name, TvShow &tvShow);

private:
    QString pathToJson;

    QJsonObject jsonObject;

    QJsonObject loadJson(QString pathToJson);
};

#endif // JSONCONNECTION_H
