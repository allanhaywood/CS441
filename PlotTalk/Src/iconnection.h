/* The definition for the connection interface.
 * All method signatures needed for accessing the datastore need to be defined here.
 * This is a pure virtual class, no implementation.
 *
 * @author Allan Haywood
 *
 */

#ifndef ICONNECTION_H
#define ICONNECTION_H
#include "tvshow.h"
#include "user.h"
#include "common.h"

#include <QList>


class IConnection
{
public:
    /**
     * @exception NotFound If specified tvshow is not found.
     */
    virtual TvShow getTvShow(QString name) = 0;

    /**
     * @exception AlreadyExists If specified tvshow is already added.
     */
    //virtual void addTvShow(TvShow tvShow) = 0;

    //virtual void saveTvShow(TvShow tvShow) = 0;

    /**
     * @exception NotFound If specified user is not found.
     */
    virtual User getUser(QString username) = 0;

    /**
     * @exception NotFound If specified user is not found.
     */
    virtual QString getUserNameByEmail(QString email) = 0;

    /**
     * @exception AlreadyExists if specified user is already added.
     */
    virtual void addUser(User user) = 0;

    // Does not throw exception if use is not found.
    virtual void removeUser(QString username) = 0;

    //virtual void saveUser(User user) = 0;

    virtual bool usernameExists(QString username) = 0;

    virtual bool emailExists(QString email) = 0;

    virtual QList<QString> getListOfAllTvShows() = 0;

    virtual void addEpisodeReview(EpisodeIdentifier episodeIdentifier, Review review) = 0;

    virtual void addEpisodeComment(EpisodeIdentifier episodeIdentifier, Review review) = 0;
};

#endif // ICONNECTION_H
