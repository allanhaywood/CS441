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


bool AccountManager::createAccount(QString &first, QString &last, QString &Email, QString &handle, QString &password)
{//places an account into the database, returns true if complete, false if email or handle are not unique


   Person thisPerson;
   thisPerson.firstName=first;
   thisPerson.lastName=last;
   thisPerson.email=Email;
   thisPerson.handle=handle;
   thisPerson.password=password;

    if(!findPersonByEmail(Email) && !findPersonByHandle(handle))//very inefficient, may need to be fixed
        {//checks to make sure email and handle are both unique
            peopleList.append(thisPerson);
            thisGuy=thisPerson;
            return true;//returns true that the account was created
        }

    return false;//returns false, something went wrong
}

bool AccountManager::findPersonByHandle(QString &handleToCheck)
{//finds an account by handle, passes back true and a person if found false if not.

    if(peopleList.size()==0)
    {
        return false;//person is not in list
    }

    for (int i =0; i<peopleList.size();i++)
    {
        if(peopleList[i].handle==handleToCheck)
        {
            return true;//person is in list
        }
    }

    return false;//list is not empty but person is not in list
}

Person AccountManager::getCurrentAccount()
{//retuns the account information of the account held in the program
return thisGuy;//useful for getting info into various pages without searching the database
}

bool AccountManager::findPersonByEmail(QString &emailtoCheck)
{//finds a person by email, saves data to a person class and returns true if found, returns false if not found

    if(peopleList.size()==0)
    {
        return false;//person is not in list
    }

    for (int i =0; i<peopleList.size();i++)
    {
        if(peopleList[i].email==emailtoCheck)
        {
            return true;//person is in list
        }
    }

    return false;//list is not empty but person is not in list
}

int AccountManager::checkFields(QString &fName, QString &lName, QString &handle, QString &email, QString &password)
{
    QRegularExpression checkEmail("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}");
    QRegularExpression checkPassword("(?=^.{8,30}$)(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&amp;*()_+}{&quot;&quot;:;'?/&gt;.&lt;,]).*$");//patterntitle retrived from http://regexlib.com/Search.aspx?k=password&c=-1&m=5&ps=20

    QValidator *validEmail=new QRegularExpressionValidator(checkEmail, 0);
    QValidator *validPwd = new QRegularExpressionValidator(checkPassword,0);

/*

Password filter that matches the NSA Password filter DLL ENPASFILT.DLL. At least 1 small-case letter At least 1 Capital letter At least 1 digit At least 1 special character Length should be between 8-30 characters. Spaces allowed The sequence of the characters is not important.

*/
    int num=0;
    if(validEmail->validate(email,num)==2)//valid email
    {
        if(validPwd->validate(password,num)==2)//valid password
        {
            if(!findPersonByEmail(email))//email is unique
            {
                if(!findPersonByHandle(handle))//handle is unique
                {
                    if((fName.size()>0)&&(lName.size()>0))//person has a name
                    {
                        createAccount(fName,lName,email,handle,password);
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

   return 7;

}



#endif//accountManager
