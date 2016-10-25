/**
 * JsonConnection class handles reading and writting data to a json formatted file.
 */
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDebug>
#include <QVariantMap>

#include "jsonconnection.h"

/**
 * @brief JsonConnection::JsonConnection construcs Json connection for the file at the given path.
 * @param pathToJson This can be either a file in the filesystem, or in resources.
 */
JsonConnection::JsonConnection(QString pathToJson)
{
    this->pathToJson = pathToJson;
}

/**
 * @brief JsonConnection::getPathToJson returns the path of the current json file being used.
 * @return QString representing the location of the json file being used.
 */
QString JsonConnection::getPathToJson()
{
    return this->pathToJson;
}

/**
 * @brief JsonConnection::getTvShow Returns the tvshow with the provided name.
 * @param The name of the tvshow to retrieve.
 * @return The Tvshow, if no match is found an empty TvShow is returned.
 * TODO: Change behavior for when a matching TvShow is not found, need to investigate best option.
 */
void JsonConnection::getTvShow(QString name, TvShow &tvShow)
{
    QString jsonName = "";
    QString jsonTmdbLink = "";
    QString jsonGraphicLink = "";

    // Loads the json at the provided path.
    QJsonObject jsonObject = loadJson(pathToJson);

    // The json object can contain many arrays, TvShow, Users, Seasons, etc.
    // This gets the TvShow elements.
    QJsonArray tvshows = jsonObject["TvShow"].toArray();

    // Loops through each element in the TvShow array to try and find a match on the name.
    QJsonObject obj;
    foreach (const QJsonValue &value, tvshows)
    {
        // If there is a match on the tvname, extract all the elements needed to construct
        // the TvShow object.
        obj = value.toObject();
        if(QString::compare(obj["name"].toString(), name, Qt::CaseInsensitive)==0)
        {
            jsonName = obj["name"].toString();
            jsonTmdbLink = obj["tmdbLink"].toString();
            jsonGraphicLink = obj["graphicLink"].toString();
            break;
        }
    }

    // Use the information found to construct and return a TvShow of the requested tvshow.
    tvShow = TvShow(jsonName, jsonTmdbLink, jsonGraphicLink);
}

/**
 * @brief JsonConnection::loadJson Reads the specified json from file and returns a QJsonObject.
 * @param pathToJson The path to the Json file, it can be either in resources, or on the filesystem.
 * @return The QJsonObject as represented in the Json formated file.
 */
QJsonObject JsonConnection::loadJson(QString pathToJson)
{
    QFile file;
    QJsonDocument jsonDocument;
    file.setFileName(pathToJson);

    // Attempt to open the file, if it can be opened, attempt to parse it into a QJsonDocument.
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file for read";
        qDebug() << file.errorString();
    }
    else
    {
        QJsonParseError jerror;
        jsonDocument = QJsonDocument::fromJson(file.readAll(),&jerror);
        file.close();

        if(jerror.error != QJsonParseError::NoError)
        {
            qDebug() << "Error parsing json!";
        }
    }

    QJsonObject jsonObject = jsonDocument.object();

    return jsonObject;
}
