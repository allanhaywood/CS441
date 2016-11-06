#ifndef ACCOUNTMANAGER_C
#define ACCOUNTMANAGER_C

#include "accountmanager.h"


#include <QRegExp>
#include <QRegularExpressionValidator>

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

/**
 * @brief
 * @param
 * @return
 */

bool AccountManager::createAccount(QString &first, QString &last, QString &Email, QString &handle, QString &password)
{//places an account into the database, returns true if complete, false if email or handle are not unique

   User thisPerson(handle, first, last,Email,password);//add Password Hash when possible

   DatabaseManager database;
    if(!database.usernameExists(handle) && !database.emailExists(Email))//very inefficient, may need to be fixed
        {//checks to make sure email and handle are both unique
            database.addUser(thisPerson);
            thisGuy=thisPerson;
            return true;//returns true that the account was created
        }

    return false;//returns false, something went wrong
}

/**
 * @brief
 * @param
 * @return
 */

User AccountManager::getCurrentAccount()
{//retuns the account information of the account held in the program
return thisGuy;//useful for getting info into various pages without searching the database
}

/**
 * @brief
 * @param
 * @return
 */

int AccountManager::checkFields(QString &fName, QString &lName, QString &handle, QString &email, QString &password)
{
    QRegularExpression checkEmail("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}");
    QRegularExpression checkPassword("(?=^.{8,30}$)(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&amp;*()_+}{&quot;&quot;:;'?/&gt;.&lt;,]).*$");//patterntitle retrived from http://regexlib.com/Search.aspx?k=password&c=-1&m=5&ps=20

    QValidator *validEmail=new QRegularExpressionValidator(checkEmail, 0);
    QValidator *validPwd = new QRegularExpressionValidator(checkPassword,0);

/*

Password filter that matches the NSA Password filter DLL ENPASFILT.DLL. At least 1 small-case
letter At least 1 Capital letter At least 1 digit At least 1 special character Length should
be between 8-30 characters. Spaces allowed The sequence of the characters is not important.

*/
    int num=0;
    DatabaseManager database;
    if(validEmail->validate(email,num)==2)//valid email
    {
        if(validPwd->validate(password,num)==2)//valid password
        {
            if(!database.emailExists(email))//email is unique
            {
                if(!database.usernameExists(handle))//handle is unique
                {
                    if((fName.size()>0)&&(lName.size()>0))//person has a name
                    {
                        User newAccount(handle,fName,lName,email,password);
                        database.addUser(newAccount);
                        return 1;//all is go and account is created
                    }
                    else
                    {
                        return 6;//name is not acceptable
                    }
                }
                else
                {
                    return 3;//handle is already used
                }
            }
            else
            {
                return 4;//email is already used
            }
        }
        else
        {
            return 5;//password format is bad
        }
    }
    else
    {
        return 2;//email format is bad
    }

   return 7;//default, but shouldn't be called
}

bool AccountManager::checkEmailAndPassword(QString& email, QString& password, User &user)
{
    DatabaseManager database;
        if(database.emailExists(email))
        {
            User hold= new User();
            user=hold;
           // database.getUser()
            //check password associated with email and return true if it is correct
            return true;
        }
        else
        {
            return false;
        }
}



#endif//accountManager
