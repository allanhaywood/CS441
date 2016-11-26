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

}

AccountManager::~AccountManager()//destructor
{
    delete instance;//destroys the class
    instance=NULL;//removes dangling pointers
}

/**
 * @brief places an account into the database
 * @param accepts user information in QString format in the order: first,last,Email,userName,password
 * @return true always as it will always call the database manager and insert the info
 */

bool AccountManager::createAccount(QString first, QString last, QString Email, QString handle, QString password)
{\
return createAccount(first, last, Email, handle, password, false);
}

bool AccountManager::createAccount(QString first, QString last, QString Email, QString handle, QString password, bool isAdmin)
{
        User thisUser = User(handle, first, last, Email, password, isAdmin);//add Password Hash when possibl
        DatabaseManagerSingleton::Instance().addUser(thisUser);
        referenceTodatabaseUser = DatabaseManagerSingleton::Instance().inspectUser(handle);
        return true;//reminant of previous code
}

bool AccountManager::createAccount(User user)
{
    DatabaseManagerSingleton::Instance().addUser(user);
    referenceTodatabaseUser = DatabaseManagerSingleton::Instance().inspectUser(user.email);
    return true;
}


/**
 * @brief gets the current account that is stored as a private object in the persistant account manager
 * @param none
 * @return a user object
 */

User &AccountManager::getCurrentAccount()
{//retuns the account information of the account held in the program
    return referenceTodatabaseUser;//useful for getting info into various pages without searching the database
}

/**
 * @brief checks that user information is not previously in the database or unacceptable
 * @param Takes user information in string form (first name, last name, username, email, password)
 * @return an enum value that tells the client the user has been added or what error the data contains
 */

selectEnum AccountManager::checkFieldsAndCreate(QString fName, QString lName, QString handle, QString email, QString password, bool isAdmin)
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
    typedef Singleton<DatabaseManager> DatabaseManagerSingleton;

    if((fName.size()<=1)||(lName.size()<=1)||(handle.size()<=1))
        delete validEmail;
        delete validPwd;
        return selectEnum::VALUES_MISSING;//need good names and handle
    if(validEmail->validate(email,num)!=2)
        delete validEmail;
        delete validPwd;
        return selectEnum::BAD_EMAIL;//email is bad format
    if(DatabaseManagerSingleton::Instance().emailExists(email))
        delete validEmail;
        delete validPwd;
        return selectEnum::DUPLICATE_EMAIL;//email already exists
    if(DatabaseManagerSingleton::Instance().usernameExists(handle))
        delete validEmail;
        delete validPwd;
        return selectEnum::USERNAME_TAKEN;//username is taken
    if(validPwd->validate(password,num)!=2)
        delete validEmail;
        delete validPwd;
        return selectEnum::BAD_PASSWORD;//password not correct format

    createAccount(fName,lName,email,handle,password,isAdmin);
    delete validEmail;
    delete validPwd;
    return selectEnum::ALLCLEAR;
}


/**
 * @brief Used by login, this checks to ensure email and password are correct and matching in the system
 * @param takes an email string, a password string, and a user object.
 * @return true and fills passses back the found user by reference if user exists, false and no passback if not found.
 */
bool AccountManager::checkEmailAndPassword(QString email, QString password, User user)
{
    if(DatabaseManagerSingleton::Instance().emailExists(email))
        {
            User hold=DatabaseManagerSingleton::Instance().inspectUserByEmail(email);

            if(hold.passwordHash==password)
            {
                user=hold;

                referenceTodatabaseUser = user;

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

bool AccountManager::EmailExists(QString email)//checks to see if an email exists for dashboard
{
    return DatabaseManagerSingleton::Instance().emailExists(email);
}

void AccountManager::ClearForLogout()
{
    User BlankMan;
    referenceTodatabaseUser=BlankMan;
}



#endif//accountManager
