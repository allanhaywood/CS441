/* Header for the plottalkexceptions.
 * This header contains all of the exceptions used within PlotTalk code.
 *
 * @author Allan Haywood
 */
#ifndef PLOTTALKEXCEPTIONS_H
#define PLOTTALKEXCEPTIONS_H

#include <QException>

class AlreadyExists : public QException
{
public:
    void raise() const { throw *this; }
    AlreadyExists *clone() const { return new AlreadyExists(*this); }
};

class FileIOError : public QException
{
public:
    void raise() const { throw *this; }
    FileIOError *clone() const { return new FileIOError(*this); }
};

class InvalidEmail : public QException
{
public:
    void raise() const { throw *this; }
    InvalidEmail *clone() const { return new InvalidEmail(*this); }
};

class InvalidJsonFormat : public QException
{
public:
    void raise() const { throw *this; }
    InvalidJsonFormat *clone() const { return new InvalidJsonFormat(*this); }
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

class Unexpected : public QException
{
public:
    void raise() const { throw *this; }
    Unexpected *clone() const { return new Unexpected(*this); }
};
#endif // PLOTTALKEXCEPTIONS_H
