/* JsonConnection class handles reading and writting data to a json formatted file.
 *
 * @author Allan Haywood
 */
#include "jsonconnection.h"
#include "plottalkexceptions.h"
#include "common.h"

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDebug>
#include <QDir>
#include <QVariantMap>

/**
 * @brief JsonConnection::JsonConnection construcs Json connection.
 *
 * Since no path is being provided, it will attempt to find a json file in system temp.
 * If there is no file there, it will copy test.json out of the resources. *
 */
JsonConnection::JsonConnection()
{
    // Create a test json file
    QString tempPath = QDir::tempPath();
    tempPath.append("/testJson.json");
    QString jsonPath = QDir::cleanPath(tempPath);

    // Check if a file already exists at that location.
    // If it doesn't, the one from the resources will be used.
    QDir dir(jsonPath);
    if(! dir.exists())
    {
        QFile::copy(":/json/Json/test.json", jsonPath);
        QFile::setPermissions(jsonPath, QFile::WriteOther);
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
 *
 * @todo: Change behavior for when a matching TvShow is not found, need to investigate best option.
 */
TvShow JsonConnection::getTvShow(QString name)
{
    int jsonId = 0;
    QString jsonName = "";
    QString jsonTmdbLink = "";
    QString jsonGraphicLink = "";
    QJsonArray jsonSeasons;

    QJsonArray tvShows = getTopLevelJsonArray(JSON_TVSHOW_ARRAY_NAME);

    // Loops through each element in the TvShow array to try and find a match on the name.
    QJsonObject tvShowJsonObject;
    bool found = false;
    foreach (const QJsonValue &value, tvShows)
    {
        // If there is a match on the tvname, extract all the elements needed to construct
        // the TvShow object.
        tvShowJsonObject = value.toObject();
        if(QString::compare(tvShowJsonObject["name"].toString(), name, Qt::CaseInsensitive)==0)
        {
            jsonId = tvShowJsonObject["showId"].toInt();
            jsonName = tvShowJsonObject["name"].toString();
            jsonTmdbLink = tvShowJsonObject["tmdbLink"].toString();
            jsonGraphicLink = tvShowJsonObject["graphicLink"].toString();
            jsonSeasons = tvShowJsonObject["seasons"].toArray();
            found = true;
            break;
        }
    }

    if (! found)
    {
        qDebug() << "No match found for:" << name;
        throw NotFound{};
    }

    qDebug() << "JsonSeasons:" << jsonSeasons;

    // Use the information found to construct and return a TvShow of the requested tvshow.
    return TvShow(jsonId, jsonName, jsonTmdbLink, jsonGraphicLink, getSeasons(jsonSeasons));
}

void JsonConnection::addTvShow(TvShow tvShow)
{
    // First check if the tvShow already exists.
    try
    {
        TvShow testExistTvShow = getTvShow(tvShow.name);
        throw AlreadyExists{};
    }
    catch (NotFound)
    {
        qDebug() << "Tvshow not found, we can continue.";
    }

    QJsonArray tvShows = getTopLevelJsonArray(JSON_TVSHOW_ARRAY_NAME);

    tvShows.append(tvShowToJsonObject(tvShow));

    json[JSON_TVSHOW_ARRAY_NAME] = tvShows;

    saveJson();
}

QJsonObject JsonConnection::tvShowToJsonObject(TvShow tvShow)
{
    QJsonObject jsonObject;

    jsonObject.insert("showId", QJsonValue(tvShow.showId));
    jsonObject.insert("name", QJsonValue(tvShow.name));
    jsonObject.insert("tmbdLink", QJsonValue(tvShow.tmdbLink));
    jsonObject.insert("graphicLink", QJsonValue(tvShow.graphicLink));
    jsonObject.insert("seasons", seasonsToJsonArray(tvShow.inspectSeasons()));

    return jsonObject;
}

QJsonArray JsonConnection::seasonsToJsonArray(QVector<Season> seasons)
{
    QJsonArray seasonsArray;

    foreach (const Season &season, seasons)
    {
        seasonsArray.append(seasonToJsonValue(season));
    }

    return seasonsArray;
}

QJsonValue JsonConnection::seasonToJsonValue(Season season)
{
    QJsonObject jsonObject;

    jsonObject.insert("seasonId", QJsonValue(season.seasonId));
    jsonObject.insert("seasonNumber", QJsonValue(season.seasonNumber));
    jsonObject.insert("name", QJsonValue(season.name));
    jsonObject.insert("episodes", episodesToJsonArray(season.inspectEpisodes()));

    return QJsonValue(jsonObject);
}

QJsonArray JsonConnection::episodesToJsonArray(QVector<Episode> episodes)
{
    QJsonArray episodesArray;

    foreach (const Episode &episode, episodes)
    {
        episodesArray.append(episodeToJsonValue(episode));
    }

    return episodesArray;
}

QJsonValue JsonConnection::episodeToJsonValue(Episode episode)
{
    QJsonObject jsonObject;

    jsonObject.insert("episodeId", QJsonValue(episode.episodeId));
    jsonObject.insert("episodeNumber", QJsonValue(episode.episodeNumber));
    jsonObject.insert("name", QJsonValue(episode.name));
    jsonObject.insert("summary", QJsonValue(episode.summary));
    jsonObject.insert("reviews", reviewsToJsonArray(episode.inspectReviews()));
    jsonObject.insert("comments", commentsToJsonArray(episode.getComments()));

    return QJsonValue(jsonObject);
}

QJsonArray JsonConnection::reviewsToJsonArray(QList<Review> reviews)
{
    QJsonArray reviewsArray;

    foreach (const Review &review, reviews)
    {
        reviewsArray.append(reviewToJsonValue(review));
    }

    return reviewsArray;
}

QJsonArray JsonConnection::commentsToJsonArray(QList<Comment> comments)
{
    QJsonArray commentsArray;

    foreach (const Comment &comment, comments)
    {
        commentsArray.append(commentToJsonValue(comment));
    }

    return commentsArray;
}

QJsonValue JsonConnection::reviewToJsonValue(Review review)
{
    QJsonObject jsonObject;

    jsonObject.insert("postUuid", QJsonValue(review.postUuid.toString()));
    jsonObject.insert("username", QJsonValue(review.username));
    jsonObject.insert("text", QJsonValue(review.text));
    jsonObject.insert("rating", QJsonValue(review.rating));
    jsonObject.insert("dateTimePosted", QJsonValue(review.dateTimePosted));

    return QJsonValue(jsonObject);
}

QJsonValue JsonConnection::commentToJsonValue(Comment comment)
{
    QJsonObject jsonObject;

    jsonObject.insert("postUuid", QJsonValue(comment.postUuid.toString()));
    jsonObject.insert("username", QJsonValue(comment.username));
    jsonObject.insert("text", QJsonValue(comment.text));
    jsonObject.insert("dateTimePosted", QJsonValue(comment.dateTimePosted));

    return QJsonValue(jsonObject);
}


/**
 * @brief JsonConnection::getSeasons Gets all the seasons for the specified tvShow
 * @param tvShowName The name of the tvshow.
 * @return A QVector of all the seasons.
 */
QMap<int, Season> JsonConnection::getSeasons(QJsonArray jsonSeasons)
{
    QMap<int, Season> seasons = QMap<int, Season>();

    Season tempSeason;
    foreach (const QJsonValue &value, jsonSeasons)
    {
        tempSeason = getSeason(value.toObject());
        seasons.insert(tempSeason.seasonId, tempSeason);
    }

    return seasons;
}

/**
 * @brief JsonConnection::getSeason Converts provided season json to a Season object.
 * @param jsonSeason The json that represents a season.
 * @return The season object that represents the json season provided.
 */
Season JsonConnection::getSeason(QJsonObject jsonSeason)
{
    qDebug() << "seasonId:" << jsonSeason["seasonId"].toInt();
    qDebug() << "seasonNumber:" << jsonSeason["seasonNumber"].toInt();
    qDebug() << "seasonName:" << jsonSeason["name"].toString();

    return Season(
                jsonSeason["seasonId"].toInt(),
                jsonSeason["seasonNumber"].toInt(),
                jsonSeason["name"].toString(),
                getEpisodes(jsonSeason["episodes"].toArray())
            );
}

/**
 * @brief JsonConnection::getEpisodes Converts the provided json episodes into a vector of episodes.
 * @param jsonEpisodes The json that represents the episodes to convert.
 * @return A vector of episodes.
 */
QMap<int, Episode> JsonConnection::getEpisodes(QJsonArray jsonEpisodes)
{
    QMap<int, Episode> episodes = QMap<int, Episode>();

    Episode tempEpisode;
    foreach (const QJsonValue &value, jsonEpisodes)
    {
        tempEpisode = getEpisode(value.toObject());
        episodes.insert(tempEpisode.episodeId, tempEpisode);
    }

    return episodes;
}

/**
 * @brief JsonConnection::getEpisode Converst the provided json episdoe into an episode object.
 * @param jsonEpisode The json representation of the episode.
 * @return The episode object that was represented by the json provided.
 */
Episode JsonConnection::getEpisode(QJsonObject jsonEpisode)
{
    qDebug() << "jsonEpisodeId:" << jsonEpisode["episodeId"].toInt();
    qDebug() << "jsonEpisodeNumber:" << jsonEpisode["episodeNumber"].toInt();
    qDebug() << "jsonEpisodeName:" << jsonEpisode["name"].toString();
    qDebug() << "jsonEpisodeSummary:" << jsonEpisode["summary"].toString();

    return Episode(
                jsonEpisode["episodeId"].toInt(),
                jsonEpisode["episodeNumber"].toInt(),
                jsonEpisode["name"].toString(),
                jsonEpisode["summary"].toString(),
                getReviews(jsonEpisode["reviews"]),
                getComments(jsonEpisode["comments"])
            );
}

QList<Comment> JsonConnection::getComments(QJsonValue jsonComments)
{
    QList<Comment> comments = QList<Comment>();

    Comment comment;
    QJsonObject jsonObject;
    foreach (const QJsonValue &jsonComment, jsonComments.toArray())
    {
        jsonObject = jsonComment.toObject();
        comment.postUuid = QUuid(jsonObject["postUuid"].toString());
        comment.username = jsonObject["username"].toString();
        comment.text = jsonObject["text"].toString();
        comment.dateTimePosted = jsonObject["dateTimePosted"].toString();

        comments.append(comment);
    }

    return comments;
}

QMap<QString, Review> JsonConnection::getReviews(QJsonValue jsonReviews)
{
    QMap<QString, Review> reviews = QMap<QString, Review>();

    Review review;
    QJsonObject jsonObject;
    foreach (const QJsonValue &jsonReview, jsonReviews.toArray())
    {
        jsonObject = jsonReview.toObject();
        review.postUuid = QUuid(jsonObject["postUuid"].toString());
        review.username = jsonObject["username"].toString();
        review.rating = jsonObject["rating"].toInt();
        review.text = jsonObject["text"].toString();
        review.dateTimePosted = jsonObject["dateTimePosted"].toString();

        reviews.insert(review.username, review);
    }

    return reviews;
}

/**
 * @brief JsonConnection::getUser Updates reference to the specified user.
 * @param username The username to retrieve.
 * @return The user that matches.
 *
 * * @throws NotFound if user is not found.
 */
User JsonConnection::getUser(QString username)
{
    QString jsonUsername;
    QString jsonFirstName;
    QString jsonLastName;
    QString jsonEmail;
    QString jsonPasswordHash;
    bool jsonIsAdmin;

    QJsonArray users = getTopLevelJsonArray(JSON_USER_ARRAY_NAME);

    qDebug() << "Users count:" << users.count();

    // Loops through each element in the users array to try and find a match on the name.
    QJsonObject obj;
    bool found = false;
    for (auto value : users)
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
            jsonIsAdmin = obj["_isAdmin"].toBool();
            found = true;
            break;
        }
    }

    if (! found)
    {
        qDebug() << "No match found for:" << username;
        throw NotFound{};
    }

    // Use the information found to construct a user of the requested User.
    return User(jsonUsername, jsonFirstName, jsonLastName, jsonEmail, jsonPasswordHash, jsonIsAdmin);
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

    // Loops through each element in the users array to try and find a match on the name.
    QJsonObject obj;
    bool found = false;
    foreach (const QJsonValue &value, users)
    {
        // If there is a match on the user name, extract all the elements needed to construct
        // the user object.
        obj = value.toObject();

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
 * @brief JsonConnection::getTvShowNameById Gets the tvshow name by Id.
 * @param id The Id to search for.
 * @return The tvshow name that matches the id
 *
 * @throws NotFound
 */
QString JsonConnection::getTvShowNameById(int id)
{
    QString jsonName;

    QJsonArray tvShows = getTopLevelJsonArray(JSON_TVSHOW_ARRAY_NAME);

    // Loops through each element in the tvshow array to try and find a match on the name.
    QJsonObject obj;
    bool found = false;
    foreach (const QJsonValue &tvShow, tvShows)
    {
        // If there is a match on the user name, extract all the elements needed to construct
        // the user object.
        obj = tvShow.toObject();
        if( obj["showId"].toInt() == id )
        {
            jsonName = obj["name"].toString();
            found = true;
            break;
        }
    }

    if (! found)
    {
        qDebug() << "No match found for:" << id;
        throw NotFound{};
    }

    return jsonName;
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
    try
    {
        User testExistUser = getUser(user.username);
        throw AlreadyExists{};
    }
    catch (NotFound)
    {
        qDebug() << "User not found, we can continue.";
    }

    QJsonArray users = getTopLevelJsonArray(JSON_USER_ARRAY_NAME);

    users.append(userToJsonObject(user));

    json[JSON_USER_ARRAY_NAME] = users;

    saveJson();
}

QJsonObject JsonConnection::userToJsonObject(User user)
{
    QJsonObject jsonObject = QJsonObject();

    jsonObject.insert("username", QJsonValue(user.username));
    jsonObject.insert("firstName", QJsonValue(user.firstName));
    jsonObject.insert("lastName", QJsonValue(user.lastName));
    jsonObject.insert("email", QJsonValue(user.email));
    jsonObject.insert("passwordHash", QJsonValue(user.passwordHash));
    jsonObject.insert("_isAdmin", QJsonValue(user.isAdmin()));

    return jsonObject;
}

/**
 * @brief JsonConnection::removeUser Removes the specified user.
 * @param username The username to remove.
 */
void JsonConnection::removeUser(QString username)
{
    // First check if user already exists.
    try
    {
        User testExistUser = getUser(username);
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

        // If a match is found, its index is now known and can be removed.
        if(QString::compare(obj["username"].toString(), username, Qt::CaseInsensitive)==0)
        {
            break;
        }

        count += 1;
    }

    users.removeAt(count);

    json[JSON_USER_ARRAY_NAME] = users;

    saveJson();
}

/**
 * @brief JsonConnection::usernameExists Checks if the specified username exists.
 * @param username The username to check.
 * @return True if the user exists, false, if it doesn't.
 */
bool JsonConnection::usernameExists(QString username)
{
    bool found = false;
    try
    {
        User user = getUser(username);
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

    // Loops through each element in the users array to try and find a match on email.
    QJsonObject obj;
    bool found = false;
    foreach (const QJsonValue &value, users)
    {
        obj = value.toObject();

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

QList<QString> JsonConnection::getListOfAllUsers()
{
    QJsonArray users = getTopLevelJsonArray(JSON_USER_ARRAY_NAME);

    QJsonObject obj;
    QList<QString> usernames;
    foreach (const QJsonValue &value, users)
    {
        obj = value.toObject();
        usernames.append(obj["username"].toString());
    }

    return usernames;
}

void JsonConnection::addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review)
{
    QJsonArray tvShows = getTopLevelJsonArray(JSON_TVSHOW_ARRAY_NAME);
    TvShow tvShow;

    QJsonObject obj;

    int index = 0;
    bool found = false;
    foreach (const QJsonValue &value, tvShows)
    {
        obj = value.toObject();
        if ( obj["showId"] == episodeIdentifier.tvShowId )
        {
            tvShow = getTvShow(obj["name"].toString());
            found = true;
            break;
        }

        ++index;
    }

    if ( ! found )
    {
        throw NotFound{};
    }

    tvShow.addEpisodeReview(episodeIdentifier, review);

    tvShows.replace(index, tvShowToJsonObject(tvShow));

    json[JSON_TVSHOW_ARRAY_NAME] = tvShows;

    saveJson();
}

void JsonConnection::addEpisodeComment(EpisodeIdentifier episodeIdentifier, Comment comment)
{
    QJsonArray tvShows = getTopLevelJsonArray(JSON_TVSHOW_ARRAY_NAME);
    TvShow tvShow;

    QJsonObject obj;

    int index = 0;
    bool found = false;
    foreach (const QJsonValue &value, tvShows)
    {
        obj = value.toObject();
        if ( obj["showId"] == episodeIdentifier.tvShowId )
        {
            tvShow = getTvShow(obj["name"].toString());
            found = true;
            break;
        }

        ++index;
    }

    if ( ! found )
    {
        throw NotFound{};
    }

    tvShow.addEpisodeComment(episodeIdentifier, comment);

    tvShows.replace(index, tvShowToJsonObject(tvShow));

    json[JSON_TVSHOW_ARRAY_NAME] = tvShows;

    saveJson();
}

/**
 * @brief JsonConnection::loadJson Reads the specified json from file.
  */
void JsonConnection::loadJson()
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
            throw InvalidJsonFormat{};
        }
    }

    if(jsonDocument.isNull())
    {
        qDebug() << "Invalid Json, halting.";
        throw InvalidJsonFormat{};
    }

    QJsonObject jsonObject = jsonDocument.object();

    json = jsonObject;
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
    return json[jsonArrayName].toArray();
}
