#ifndef ACCOUNTMANAGER_C
#define ACCOUNTMANAGER_C

#include "accountmanager.h"

AccountManager *AccountManager::instance=0;

AccountManager* AccountManager::getInstance()
{
    if (instance!=NULL)
    {
        instance=new AccountManager();
    }

    return instance;
}


AccountManager::AccountManager()
{
    QString filename="Data.txt";//constructs a file name Data.txt
    file (filename);//opens that file and sets it to file in the header for use in other fucntions
}

AccountManager::~AccountManager()
{
    file.close();//closes the file before destroying the class
    delete instance;//destroys the class
    instance=NULL;//removes dangling pointers
}




bool AccountManager::createAccount(QString &first, QString &last, QString &email, QString &handle, QString &password)
{

    if(checkEmail(email))//checks to see if the email already exists in the file
    {
        if(file.open(QIODevice::ReadWrite))//checks to see if the file exists
        {
            QTextStream stream(&file);//sets up the stream
            stream << email << " " << first << " " << last << " " <<handle << " "<< password << endl;
           //prints -email, firstname, lastname, handle, password- into file
        }
    }
}

bool AccountManager::loadDetails(QString &handle)
{
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line=in.readLine();
        while(line)
        {

        }
    }
}

bool AccountManager::checkEmail(QString &email)
{

}

bool AccountManager::checkHandle(QString &handle)
{

}

Person AccountManager::getCurrentAccount()
{
return ThisGuy;
}

Person AccountManager::findPersonByEmail(QString &email)
{

}

Person AccountManager::findPersonByHandle(QString &handle)
{

}

#endif//accountManager
