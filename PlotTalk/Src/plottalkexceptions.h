#ifndef PLOTTALKEXCEPTIONS_H
#define PLOTTALKEXCEPTIONS_H

#include <QException>

class NotFound : public QException
{
public:
    void raise() const { throw *this; }
    NotFound *clone() const { return new NotFound(*this); }
};

class InvalidPassword : public QException
{
public:
    void raise() const { throw *this; }
    InvalidPassword *clone() const { return new InvalidPassword(*this); }
};

class InvalidEmail : public QException
{
public:
    void raise() const { throw *this; }
    InvalidEmail *clone() const { return new InvalidEmail(*this); }
};

#endif // PLOTTALKEXCEPTIONS_H
