#ifndef JSONCONNECTION_H
#define JSONCONNECTION_H
#include <QString>
#include <QJsonObject>

#include "tvshow.h"

class JsonConnection
{
public:
    JsonConnection(QString pathToJson);

    QString getPathToJson();

    TvShow getTvShow(QString name);

private:
    QString pathToJson;

    QJsonObject jsonObject;

    QJsonObject loadJson(QString pathToJson);
};

#endif // JSONCONNECTION_H
