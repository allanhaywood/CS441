/* JsonConnection class handles reading and writting data to a json formatted file.
 *
 * @author Allan Haywood
 */
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDebug>

#include "jsonconnection.h"
#include "plottalkexceptions.h"

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

    QJsonArray tvshows = getTopLevelJsonArray("TvShow");

    // Loops through each element in the TvShow array to try and find a match on the name.
    QJsonObject obj;
    bool found = false;
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
            found = true;
            break;
        }
    }

    if (! found)
    {
        qDebug() << "No match found for:" << name;
        throw NotFound{};
    }

    // Use the information found to construct and return a TvShow of the requested tvshow.
    tvShow = TvShow(jsonName, jsonTmdbLink, jsonGraphicLink);
}

void JsonConnection::getUser(QString username, User &user)
{
    QString jsonUsername;
    QString jsonEmail;
    QString jsonPasswordhash;

    QJsonArray users = getTopLevelJsonArray("User");

    qDebug() << "Looking for username:" << username;

    qDebug() << "Users:" << users;

    // Loops through each element in the users array to try and find a match on the name.
    QJsonObject obj;
    bool found = false;
    foreach (const QJsonValue &value, users)
    {
        // If there is a match on the user name, extract all the elements needed to construct
        // the user object.
        obj = value.toObject();

        qDebug() << "User:" << obj;
        if(QString::compare(obj["username"].toString(), username, Qt::CaseInsensitive)==0)
        {
            jsonUsername = obj["username"].toString();
            jsonEmail = obj["email"].toString();
            jsonPasswordhash = obj["passwordhash"].toString();
            found = true;
            break;
        }
    }

    if (! found)
    {
        qDebug() << "No match found for:" << username;
        throw NotFound{};
    }

    // Use the information found to construct a user of the requested tvshow.
    user = User(jsonUsername, jsonEmail, jsonPasswordhash);
}

bool JsonConnection::usernameExists(QString username)
{
    User user = User();
    bool found = false;
    try
    {
        getUser(username, user);
        found = true;
    }
    catch (NotFound)
    {
        qDebug() << "User does not exist:" << username;
    }

    return found;
}

bool JsonConnection::emailExists(QString email)
{
    QJsonArray users = getTopLevelJsonArray("User");

    qDebug() << "Looking for email:" << email;

    qDebug() << "Users:" << users;

    // Loops through each element in the users array to try and find a match on email.
    QJsonObject obj;
    bool found = false;
    foreach (const QJsonValue &value, users)
    {
        obj = value.toObject();

        qDebug() << "User:" << obj;
        if(QString::compare(obj["email"].toString(), email, Qt::CaseInsensitive)==0)
        {
            found = true;
            break;
        }
    }

    return found;
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

QJsonArray JsonConnection::getTopLevelJsonArray(QString jsonArrayName)
{
    // Loads the json at the provided path.
    QJsonObject jsonObject = loadJson(pathToJson);

    // The json object can contain many arrays, TvShow, Users, Seasons, etc.
    // This gets the TvShow elements.
    return jsonObject[jsonArrayName].toArray();
}


