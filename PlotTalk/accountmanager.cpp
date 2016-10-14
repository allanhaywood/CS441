#ifndef ACCOUNTMANAGER_C
#define ACCOUNTMANAGER_C

#include "accountmanager.h"
#include "accountcheckandstore.h"

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
}

AccountManager::~AccountManager()
{
    delete instance;
    instance=NULL;
}

#endif//accountManager


bool AccountManager::createAccount(QString &first, QString &last, QString &email, QString &password)
{
    AccountCheckAndStore *intoDatabase =AccountCheckAndStore::getInstance();

    if(intoDatabase->AddPerson(first,last,email,password))
  {
      return true;
  }
  else
  {
      return false;
  }
}


