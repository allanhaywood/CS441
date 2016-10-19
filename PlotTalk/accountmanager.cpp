#ifndef ACCOUNTMANAGER_C
#define ACCOUNTMANAGER_C

#include "accountmanager.h"

AccountManager *AccountManager::instance=NULL;//sets initial instance to 0

AccountManager* AccountManager::getInstance()//returns a new instance or the same instance as needed
{
    if (instance==NULL)
    {
        instance=new AccountManager();
    }

    return instance;
}


AccountManager::AccountManager()//constructor
{//nothing constructed except the singleton
}

AccountManager::~AccountManager()//destructor
{
    delete instance;//destroys the class
    instance=NULL;//removes dangling pointers
}




bool AccountManager::createAccount(QString &first, QString &last, QString &email, QString &handle, QString &password)
{//places an account into the database, returns true if complete, false if email or handle are not unique

    Person hold;
    if(findPersonByEmail(hold,email) && findPersonByHandle(hold,handle))//very inefficient, may need to be fixed
    {//checks to make sure email and handle are both unique

        QFile file(fileName);//opens a file

        if(file.open(QIODevice::Append))//checks to see if the file exists and opens it for appending
        {
            QTextStream stream(&file);//sets up the stream

            stream << email << " " << first << " " << last << " " <<handle << " "<< password << endl;
           //prints -email, firstname, lastname, handle, password- into file
            file.close();//closes the file as it has been writen to now
            return true;//returns true that the account was created
        }
        file.close();//closes the file without writing, something went wrong
    }

    return false;//returns false, something went wrong
}

bool AccountManager::findPersonByHandle(Person &PassBack, QString &handleToCheck)
{//finds an account by handle, passes back true and a person if found false if not.
QString first;
QString last;
QString email;
QString handle;
QString password;//places for the variables as retrieved by the next section

    QFile file(fileName);
    QTextStream in(&file);//opens a file and calls it "in"
    while(!in.atEnd())//if it's at the end stops
    {
    in>>email;
    in>>first;
    in>>last;
    in>>handle;
    in>>password;//stores the variables from the file into strings

        if (handle==handleToCheck)//once stored, checks the handle to see if it's a match
        {
            PassBack.firstName=first;
            PassBack.lastName=last;
            PassBack.email=email;
            PassBack.handle=handle;
            PassBack.password=handle;//if correct puts the info into the PassBack person for passage back

            ThisGuy=PassBack;//Stores the passback variable into ThisGuy as it will be the new account.
            file.close();
            return true;
        }
    }
    file.close();
    return false;//if the previous does not return true than the handles was not found
}

Person AccountManager::getCurrentAccount()
{//retuns the account information of the account held in the program
return ThisGuy;//useful for getting info into various pages without searching the database
}

bool AccountManager::findPersonByEmail(Person &PassBack, QString &emailtoCheck)
{//finds a person by email, saves data to a person class and returns true if found, returns false if not found
    QString first;
    QString last;
    QString email;
    QString handle;
    QString password;//variables to hold data for the next section

    QFile file(fileName);
    QTextStream in(&file);//opens the file and calls it in
    while(!in.atEnd())
    {
        in>>email;
        in>>first;
        in>>last;
        in>>handle;
        in>>password;//pulls the data from the file

        if (email==emailtoCheck)//checks the email against the file
        {
           PassBack.firstName=first;
           PassBack.lastName=last;
           PassBack.email=email;
           PassBack.handle=handle;
           PassBack.password=handle;//if it's a match gathers the information into passback to reutrn to the client

           ThisGuy=PassBack;//stores the new user as the current in the program

           file.close();
           return true;
        }
    }

    file.close();
    return false;//returns false if email is not found
}



#endif//accountManager
