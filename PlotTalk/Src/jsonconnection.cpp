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
#include <QDir>

#include "jsonconnection.h"
#include "plottalkexceptions.h"

/**
 * @brief JsonConnection::JsonConnection construcs Json connection.
 *
 * Since no path is being provided, it will attempt to find a json file at the default location,
 * QDir::currentPath/testJson.json
 * If there is no file there, it will copy test.json out of the resources. *
 */
JsonConnection::JsonConnection()
{
    // Create a test json file
    QString currentPath = QDir::currentPath();
    currentPath.append("/testJson.json");
    QString jsonPath = QDir::cleanPath(currentPath);

    // Check if a file already exists at that location.
    // If it doesn't, the one from the resources will be used.
    QDir dir(jsonPath);
    if(! dir.exists())
    {
        QFile::copy(":/json/Json/test.json", jsonPath);
    }

    this->pathToJson = jsonPath;
    loadJson();
}

/**
 * @brief JsonConnection::JsonConnection construcs Json connection for the file at the given path.
 * @param pathToJson This can be either a file in the filesystem, or in resources.
 */
JsonConnection::JsonConnection(QString pathToJson)
{
    this->pathToJson = pathToJson;
    loadJson();
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
 * @brief JsonConnection::setPathToJson Sets the current path to the json file.
 * @param newPathToJson The new path of the json file to use.
 */
void JsonConnection::setPathToJson(QString newPathToJson)
{
    // @todo Add path validation.
    pathToJson = newPathToJson;
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

    QJsonArray tvshows = getTopLevelJsonArray(JSON_TVSHOW_ARRAY_NAME);

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

/*
void JsonConnection::addTvShow(TvShow tvShow)
{
    // Loads the json at the provided path.
    QJsonObject jsonObject = loadJson(pathToJson);



    jsonObject.
}*/

/**
 * @brief JsonConnection::getUser Updates reference to the specified user.
 * @param username The username to retrieve.
 * @param user The user object to update.
 *
 * @throws NotFound if user is not found.
 */
void JsonConnection::getUser(QString username, User &user)
{
    QString jsonUsername;
    QString jsonFirstName;
    QString jsonLastName;
    QString jsonEmail;
    QString jsonPasswordHash;

    QJsonArray users = getTopLevelJsonArray(JSON_USER_ARRAY_NAME);

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
            jsonFirstName = obj["firstName"].toString();
            jsonLastName = obj["lastName"].toString();
            jsonEmail = obj["email"].toString();
            jsonPasswordHash = obj["passwordHash"].toString();
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
    user = User(jsonUsername, jsonFirstName, jsonLastName, jsonEmail, jsonPasswordHash);
}

/**
 * @brief JsonConnection::getUserNameByEmail Gets the username for the specified email.
 * @param email The email to search for.
 * @return The username that matches the email.
 *
 * @throws NotFound
 */
QString JsonConnection::getUserNameByEmail(QString email)
{
    QString jsonUsername;

    QJsonArray users = getTopLevelJsonArray(JSON_USER_ARRAY_NAME);

    qDebug() << "Looking for user email:" << email;

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
        if(QString::compare(obj["email"].toString(), email, Qt::CaseInsensitive)==0)
        {
            jsonUsername = obj["username"].toString();
            found = true;
            break;
        }
    }

    if (! found)
    {
        qDebug() << "No match found for:" << email;
        throw NotFound{};
    }

    return jsonUsername;
}

/**
 * @brief JsonConnection::addUser Adds the specified user.
 * @param user The user object to add.
 *
 * @throws AlreadyExists if the user already exists.
 */
void JsonConnection::addUser(User user)
{
    // First check if user already exists.
    qDebug() << "json before:" << json;

    User testExistUser = User();
    try
    {
        getUser(user.username, testExistUser);
        throw AlreadyExists{};
    }
    catch (NotFound)
    {
        qDebug() << "User not found, we can continue.";
    }

    QJsonArray users = getTopLevelJsonArray(JSON_USER_ARRAY_NAME);
    QJsonObject jsonObject = QJsonObject();

    jsonObject.insert("username", QJsonValue(user.username));
    jsonObject.insert("firstName", QJsonValue(user.firstName));
    jsonObject.insert("lastName", QJsonValue(user.lastName));
    jsonObject.insert("email", QJsonValue(user.email));
    jsonObject.insert("passwordHash", QJsonValue(user.passwordHash));

    qDebug() << "jsonObject after insert:" << jsonObject;

    users.append(jsonObject);

    json[JSON_USER_ARRAY_NAME] = users;

    qDebug() << "json after:" << json;

    saveJson();
}

/**
 * @brief JsonConnection::removeUser Removes the specified user.
 * @param username The username to remove.
 */
void JsonConnection::removeUser(QString username)
{
    // First check if user already exists.
    qDebug() << "json before:" << json;

    User testExistUser = User();
    try
    {
        getUser(username, testExistUser);
    }
    catch (NotFound)
    {
        qDebug() << "User not found, nothing to remove, we can return.";
        return;
    }

    QJsonArray users = getTopLevelJsonArray(JSON_USER_ARRAY_NAME);

    // Loops through each element in the users array to try and find a match on the name.
    QJsonObject obj;
    int count = 0;
    foreach (const QJsonValue &value, users)
    {
        // If there is a match on the user name, extract all the elements needed to construct
        // the user object.
        obj = value.toObject();

        qDebug() << "User:" << obj;

        // If a match is found, its index is now known and can be removed.
        if(QString::compare(obj["username"].toString(), username, Qt::CaseInsensitive)==0)
        {
            break;
        }

        count += 1;
    }

    qDebug() << "Users before remove:" << users;

    users.removeAt(count);

    qDebug() << "Users after remove:" << users;

    json[JSON_USER_ARRAY_NAME] = users;

    qDebug() << "json after:" << json;

    saveJson();
}

/**
 * @brief JsonConnection::usernameExists Checks if the specified username exists.
 * @param username The username to check.
 * @return True if the user exists, false, if it doesn't.
 */
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

/**
 * @brief JsonConnection::emailExists Checks if the specified email exists.
 * @param email The email to check.
 * @return True if the email exists, False if it doesn't.
 */
bool JsonConnection::emailExists(QString email)
{
    QJsonArray users = getTopLevelJsonArray(JSON_USER_ARRAY_NAME);

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
 * @brief JsonConnection::getListOfAllTvShows Gets a list of all tvshows stored in the json file.
 * @return A QList of all tvshow names.
 */
QList<QString> JsonConnection::getListOfAllTvShows()
{
    QJsonArray tvshows = getTopLevelJsonArray(JSON_TVSHOW_ARRAY_NAME);

    QJsonObject obj;
    QList<QString> tvShows;
    foreach (const QJsonValue &value, tvshows)
    {
        obj = value.toObject();
        tvShows.append(obj["name"].toString());
    }

    return tvShows;
}

/**
 * @brief JsonConnection::loadJson Reads the specified json from file and returns a QJsonObject.
 * @param pathToJson The path to the Json file, it can be either in resources, or on the filesystem.
 */
void JsonConnection::loadJson()
{
    QFile file;
    QJsonDocument jsonDocument;
    file.setFileName(pathToJson);

    qDebug() << "Loading json file:" << pathToJson;

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
            throw InvalidJsonFormat();
        }
    }

    if(jsonDocument.isNull())
    {
        qDebug() << "Invalid Json, halting.";
        throw InvalidJsonFormat{};
    }

    QJsonObject jsonObject = jsonDocument.object();

    this->json = jsonObject;
}

/**
 * @brief JsonConnection::saveJson Saves the current state to the json file.
 *
 * @throws InvalideJsonFormat if the json cannot be parsed.
 */
void JsonConnection::saveJson()
{
    QFile file;

    QJsonDocument jsonDocument = QJsonDocument(json);

    if(jsonDocument.isNull())
    {
        qDebug() << "Invalid Json, halting.";
        throw InvalidJsonFormat{};
    }

    qDebug() << "Json Document:" << jsonDocument;

    qDebug() << "Saving json file:" << pathToJson;

    file.setFileName(pathToJson);

    // Attempt to open the file, if it can be opened, attempt to parse it into a QJsonDocument.
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file for readwrite";
        qDebug() << file.errorString();
        throw FileIOError{};
    }
    else
    {
        file.write(jsonDocument.toJson());
        file.flush();
        file.close();
    }
}

/**
 * @brief JsonConnection::getTopLevelJsonArray Gets the specified top level array.
 * @param jsonArrayName The json array to return.
 * @return The json array.
 */
QJsonArray JsonConnection::getTopLevelJsonArray(QString jsonArrayName)
{
    // The json object can contain many arrays, TvShow, Users, Seasons, etc.
    // This gets the TvShow elements.
    return json[jsonArrayName].toArray();
}


