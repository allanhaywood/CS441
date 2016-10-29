/* Header for tests for the json connection.
 *
 * @author Allan Haywood
 */
#ifndef TESTJSONCONNECTION_H
#define TESTJSONCONNECTION_H

#include <QObject>
#include "jsonconnection.h"

class TestJsonConnection : public QObject
{
    Q_OBJECT
private slots:
    void TestGetTvShow();
};

#endif // TESTJSONCONNECTION_H
