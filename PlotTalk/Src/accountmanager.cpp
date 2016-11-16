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

selectEnum AccountManager::checkFieldsAndCreate(QString &fName, QString &lName, QString &handle, QString &email, QString &password)
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

    if((fName.size()<=1)||(lName.size()<=1)||(handle.size()<=1))
        return selectEnum::VALUES_MISSING;//need good names and handle
    if(validEmail->validate(email,num)!=2)
        return selectEnum::BAD_EMAIL;//email is bad format
    if(database.emailExists(email))
        return selectEnum::DUPLICATE_EMAIL;//email already exists
    if(database.usernameExists(handle))
        return selectEnum::USERNAME_TAKEN;//username is taken
    if(validPwd->validate(password,num)!=2)
        return selectEnum::BAD_PASSWORD;//password not correct format

    createAccount(fName,lName,email,handle,password);
    return selectEnum::ALLCLEAR;
}


/**
 * @brief
 * @param
 * @return
 */
bool AccountManager::checkEmailAndPassword(QString& email, QString& password, User &user)
{
    DatabaseManager database;
        if(database.emailExists(email))
        {
            User hold=database.getUserByEmail(email);

            if(hold.passwordHash==password)
            {
                user=hold;
                thisGuy = user;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
}



#endif//accountManager
