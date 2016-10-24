#ifndef ACCOUNTMANAGER_C
#define ACCOUNTMANAGER_C

#include "accountmanager.h"

AccountManager *AccountManager::instance=NULL;//sets initial instance to NULL

AccountManager* AccountManager::getInstance()//returns a new instance or the same instance as needed
{
    if (instance==NULL)
    {
        instance=new AccountManager();
    }

    return instance;
}


AccountManager::AccountManager()//constructor
{
    //nothing constructed except the singleton
}

AccountManager::~AccountManager()//destructor
{
    delete instance;//destroys the class
    instance=NULL;//removes dangling pointers
}

/*
QJsonDocument AccountManager::loadJson()
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());

}

void AccountManager::saveInfoToJson(QJsonDocument document)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

*/
bool AccountManager::createAccount(QString &first, QString &last, QString &email, QString &handle, QString &password)
{//places an account into the database, returns true if complete, false if email or handle are not unique

   Person hold;

   Person thisPerson;
   thisPerson.firstName=first;
   thisPerson.lastName=last;
   thisPerson.email=email;
   thisPerson.handle=handle;
   thisPerson.password=password;

    if(!findPersonByEmail(hold,email) && !findPersonByHandle(hold,handle))//very inefficient, may need to be fixed
        {//checks to make sure email and handle are both unique
            peopleList.append(thisPerson);
            thisGuy=thisPerson;
            return true;//returns true that the account was created
        }

    return false;//returns false, something went wrong
}

bool AccountManager::findPersonByHandle(Person &PassBack, QString &handleToCheck)
{//finds an account by handle, passes back true and a person if found false if not.

    if(peopleList.size()==0)
    {
        return false;//person is not in list
    }

    for (int i =0; i<peopleList.size();i++)
    {
        if(peopleList[i].handle==handleToCheck)
        {
            PassBack=peopleList[i];
            return true;//person is in list
        }
    }

    return false;//list is not empty but person is not in list
}

Person AccountManager::getCurrentAccount()
{//retuns the account information of the account held in the program
return thisGuy;//useful for getting info into various pages without searching the database
}

bool AccountManager::findPersonByEmail(Person &PassBack, QString &emailtoCheck)
{//finds a person by email, saves data to a person class and returns true if found, returns false if not found

    if(peopleList.size()==0)
    {
        return false;//person is not in list
    }

    for (int i =0; i<peopleList.size();i++)
    {
        if(peopleList[i].email==emailtoCheck)
        {
            PassBack=peopleList[i];
            return true;//person is in list
        }
    }

    return false;//list is not empty but person is not in list
}



#endif//accountManager
