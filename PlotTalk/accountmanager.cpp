#include "accountmanager.h"
#include "accountcheckandstore.h"

class AccountManagerData : public QSharedData
{


private:

static AccountManager* instance;
AccountCheckAndStore::getInstance();


AccountManager::AccountManager() : data(new AccountManagerData)
{

}

AccountManager::AccountManager(const AccountManager &rhs) : data(rhs.data)
{

}

AccountManager &AccountManager::operator=(const AccountManager &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

AccountManager::~AccountManager()
{
    delete instance;
    instance=NULL;
}

public:

static AccountManager::getInstance()
{
    if (instance!=NULL)
    {
        instance=new AccountManager();
    }

    return instance;
}

bool AccountManager::createAccount(QString &first, QString &last, QString &email, QString &password)
{
  if(AccountCheckAndStore::AddPerson(first,last,email,password))
      return true;
  else
      return false;
}

};
