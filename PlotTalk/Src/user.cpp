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
    userWatched = QList<EpisodeIdentifier>();
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    _isAdmin = false;
    userWatched = QList<EpisodeIdentifier>();
}


User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash, bool isAdmin)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    _isAdmin = isAdmin;
    userWatched = QList<EpisodeIdentifier>();
}

User::User(QString username, QString firstName, QString lastName, QString email, QString passwordhash, bool isAdmin, QList<EpisodeIdentifier> episodeList)
{
    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->passwordHash = passwordhash;
    _isAdmin = isAdmin;

    addWatchedEpisodeList(episodeList);

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
        userWatched.append(episode);
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
            userWatched.removeAt(location);
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
        for(i=0; i < userWatched.size(); i++)
        {
            if(userWatched[i].episodeId == episode.episodeId &&
               userWatched[i].seasonId == episode.seasonId &&
               userWatched[i].tvShowId == episode.tvShowId)
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
    if(userWatched.size()==0)
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
