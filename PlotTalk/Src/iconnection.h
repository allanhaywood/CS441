/* The definition for the connection interface.
 * All method signatures needed for accessing the datastore need to be defined here.
 * This is a pure virtual class, no implementation.
 *
 * @author Allan Haywood
 *
 */

#ifndef ICONNECTION_H
#define ICONNECTION_H
#include <QList>

#include "tvshow.h"
#include "user.h"

class IConnection
{
public:
    /**
     * @exception NotFound If specified tvshow is not found.
     */
    virtual void getTvShow(QString name, TvShow &tvShow) = 0;

    /**
     * @exception AlreadyExists If specified tvshow is already added.
     */
    //virtual void addTvShow(TvShow tvShow) = 0;

    //virtual void saveTvShow(TvShow tvShow) = 0;

    /**
     * @exception NotFound If specified user is not found.
     */
    virtual void getUser(QString username, User &user) = 0;

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
private:
};

#endif // ICONNECTION_H
