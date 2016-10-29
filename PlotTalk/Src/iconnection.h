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

class IConnection
{
public:
    /**
     * @exception NotFound If specified tvshow is not found.
     */
    virtual void getTvShow(QString name, TvShow &tvShow) = 0;
private:
};

#endif // ICONNECTION_H
