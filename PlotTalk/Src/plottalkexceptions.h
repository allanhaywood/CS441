/* Header for the plottalkexceptions.
 * This header contains all of the exceptions used within PlotTalk code.
 *
 * @author Allan Haywood
 */
#ifndef PLOTTALKEXCEPTIONS_H
#define PLOTTALKEXCEPTIONS_H

#include <QException>
#include<QString>

class PlotTalkException : public QException {
public:
    QString message;
    PlotTalkException(QString inMessage) {message = inMessage;}
};

class AlreadyExists : public PlotTalkException
{
public:
    using PlotTalkException::PlotTalkException;
    void raise() const { throw *this; }
    AlreadyExists *clone() const { return new AlreadyExists(*this); }
};

class FileIOError : public PlotTalkException
{
public:
    using PlotTalkException::PlotTalkException;
    void raise() const { throw *this; }
    FileIOError *clone() const { return new FileIOError(*this); }
};

class InvalidEmail : public PlotTalkException
{
public:
    using PlotTalkException::PlotTalkException;
    void raise() const { throw *this; }
    InvalidEmail *clone() const { return new InvalidEmail(*this); }
};

class InvalidJsonFormat : public PlotTalkException
{
public:
    using PlotTalkException::PlotTalkException;
    void raise() const { throw *this; }
    InvalidJsonFormat *clone() const { return new InvalidJsonFormat(*this); }
};

class InvalidPassword : public PlotTalkException
{
public:
    using PlotTalkException::PlotTalkException;
    void raise() const { throw *this; }
    InvalidPassword *clone() const { return new InvalidPassword(*this); }
};

class NotFound : public PlotTalkException
{
public:
    using PlotTalkException::PlotTalkException;
    void raise() const { throw *this; }
    NotFound *clone() const { return new NotFound(*this); }
};

class NotImplemented : public PlotTalkException
{
public:
    using PlotTalkException::PlotTalkException;
    void raise() const { throw *this; }
    NotImplemented *clone() const { return new NotImplemented(*this); }
};

class Unexpected : public PlotTalkException
{
public:
    using PlotTalkException::PlotTalkException;
    void raise() const { throw *this; }
    Unexpected *clone() const { return new Unexpected(*this); }
};
#endif // PLOTTALKEXCEPTIONS_H
