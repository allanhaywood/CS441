/* Header for the plottalkexceptions.
 * This header contains all of the exceptions used within PlotTalk code.
 *
 * @author Allan Haywood
 */
#ifndef PLOTTALKEXCEPTIONS_H
#define PLOTTALKEXCEPTIONS_H

#include <QException>

class InvalidEmail : public QException
{
public:
    void raise() const { throw *this; }
    InvalidEmail *clone() const { return new InvalidEmail(*this); }
};

class InvalidPassword : public QException
{
public:
    void raise() const { throw *this; }
    InvalidPassword *clone() const { return new InvalidPassword(*this); }
};

class NotFound : public QException
{
public:
    void raise() const { throw *this; }
    NotFound *clone() const { return new NotFound(*this); }
};

class NotImplemented : public QException
{
public:
    void raise() const { throw *this; }
    NotImplemented *clone() const { return new NotImplemented(*this); }
};
#endif // PLOTTALKEXCEPTIONS_H
