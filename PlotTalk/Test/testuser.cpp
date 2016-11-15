/* Test the User class.
 *
 * @author Allan Haywood
 */
#include <QtTest/QtTest>
#include "testuser.h"

void TestUser::TestUserDefaultConstructor1()
{
    User user = User();
    QVERIFY(user.username.isEmpty());
    QVERIFY(user.firstName.isEmpty());
    QVERIFY(user.lastName.isEmpty());
    QVERIFY(user.email.isEmpty());
    QVERIFY(user.passwordHash.isEmpty());
    QVERIFY(false == user.isAdmin());
}

void TestUser::TestUserConstructor2()
{
    // Set up strings to compare against.
    QString username = "bsmith";
    QString firstName = "Bob";
    QString lastName = "Smith";
    QString email = "bsmith@gmail.com";
    QString passwordHash = "badpasswordhash";

    User user = User(username, firstName, lastName, email, passwordHash);
    QCOMPARE(username, user.username);
    QCOMPARE(firstName, user.firstName);
    QCOMPARE(lastName, user.lastName);
    QCOMPARE(email, user.email);
    QCOMPARE(passwordHash, user.passwordHash);
    QVERIFY(false == user.isAdmin());
}

void TestUser::TestUserConstructor3()
{
    // Set up strings to compare against.
    QString username = "bsmith";
    QString firstName = "Bob";
    QString lastName = "Smith";
    QString email = "bsmith@gmail.com";
    QString passwordHash = "badpasswordhash";

    User user = User(username, firstName, lastName, email, passwordHash, true);
    QCOMPARE(username, user.username);
    QCOMPARE(firstName, user.firstName);
    QCOMPARE(lastName, user.lastName);
    QCOMPARE(email, user.email);
    QCOMPARE(passwordHash, user.passwordHash);
    QVERIFY(true == user.isAdmin());
}
