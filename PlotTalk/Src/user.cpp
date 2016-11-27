/* Implementation of the user class.
 *
 * @author Allan Haywood
 */
#include "user.h"
#include "common.h"

#include<QList>

User::User()
{
    username = "";
    firstName = "";
    lastName = "";
    email = "";
    passwordHash = "";
    _isAdmin = false;
    watchedEpisodes = QList<EpisodeIdentifier>();
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    _isAdmin = false;
    watchedEpisodes = QList<EpisodeIdentifier>();
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, QList<EpisodeIdentifier> watchedEpisodes)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordHash;
    addWatchedEpisodeList(watchedEpisodes);

    _isAdmin = false;
}


User::User(QString username, QString firstName, QString lastName, QString email, QString passwordHash, bool isAdmin)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordHash;
    watchedEpisodes = QList<EpisodeIdentifier>();

    _isAdmin = isAdmin;
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash, QList<EpisodeIdentifier> watchedEpisodes, bool isAdmin)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    addWatchedEpisodeList(watchedEpisodes);

    _isAdmin = isAdmin;
}

bool User::isAdmin()
{
    return _isAdmin;
}

bool User::addWatchedEpisode(EpisodeIdentifier episode)//adds an episode to the users watched list
{
    int dummy;
    if(hasUserWatchedThisEpisode(episode, dummy))
    {
        return false;
    }
    else
    {
        watchedEpisodes.append(episode);
        return true;
    }

}

bool User::removeWatchedEpisode(EpisodeIdentifier episode)//removes an episode from the users watched list
{
    if(hasTheUserWatchedAnything())
    {
        int location;

        if(hasUserWatchedThisEpisode(episode,location))
        {
            watchedEpisodes.removeAt(location);
            return true;
        }
        else
        {
            return false;
        }
    }
        return false;
}

bool User::hasUserWatchedThisEpisode(EpisodeIdentifier episode, int &location)//private, checks to see if an episode is in the users watched list
{
    if(hasTheUserWatchedAnything())
    {
        int i;
        for(i=0; i < watchedEpisodes.size(); i++)
        {
            if(watchedEpisodes[i].episodeId == episode.episodeId &&
               watchedEpisodes[i].seasonId == episode.seasonId &&
               watchedEpisodes[i].tvShowId == episode.tvShowId)
            {
                location=i;
                return true;
            }
        }
    }
    return false;
}

bool User::hasTheUserWatchedAnything()
{
    if(watchedEpisodes.size()==0)
        return false;
    else
        return true;
}


bool User::addWatchedEpisodeList(QList<EpisodeIdentifier> episodeList)
{
  if(episodeList.size()!=0)
    {
        int dummy=0;
        for (int i=0; i<episodeList.size(); i++)
        {
          if(hasUserWatchedThisEpisode(episodeList[i], dummy))
          {
              return false;
          }
        }
        for (int i=0; i<episodeList.size(); i++)
        {
          if(!addWatchedEpisode(episodeList[i]))
          {
              return false;
          }
        }
        return true;
    }
    else
        return false;
}
