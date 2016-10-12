#include "accountmanager.h"

class AccountManagerData : public QSharedData
{
public:

};

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

}
