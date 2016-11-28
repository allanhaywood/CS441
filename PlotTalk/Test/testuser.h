/* Header for the testuser class.
 *
 * @author Allan Haywood
 */
#ifndef TESTUSER_H
#define TESTUSER_H

#include <QObject>
#include "user.h"

class TestUser : public QObject
{
    Q_OBJECT
private slots:
    void TestUserDefaultConstructor1();
    void TestUserConstructor2();
    void TestUserConstructor3();
    void TestsForWatchedList();
};

#endif // TESTUSER_H
