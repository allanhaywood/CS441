#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person
{
public:
    QString firstName;
    QString lastName;
    QString email;
    QString handle;
    QString password;
    bool isAdmin = false; // Temporary until I get Josh's changes.

    Person();
};

#endif // PERSON_H
