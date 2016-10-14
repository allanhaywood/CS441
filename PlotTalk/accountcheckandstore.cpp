#ifndef ACCOUNTCHECKANDSTORE_C
#define ACCOUNTCHECKANDSTORE_C

#include "AccountCheckAndStore.h"

AccountCheckAndStore *AccountCheckAndStore::AccountInstance=0;

AccountCheckAndStore::AccountCheckAndStore()
{
}

AccountCheckAndStore::~AccountCheckAndStore()
{

}

AccountCheckAndStore* AccountCheckAndStore::getInstance()
{
    if(AccountInstance==NULL)
    {
        AccountInstance=new AccountCheckAndStore();
    }

    return AccountInstance;
}

bool AccountCheckAndStore::checkEmail(QString &email)
{
  for(int i=0;i<ListOfPeople.size();i++)
  {
      if(ListOfPeople[i].email==email)
      {
          return true;
      }
  }
  return false;
}

bool AccountCheckAndStore::AddPerson(QString &first, QString &last, QString &email, QString &password)
{
    if(checkEmail(email))
    {
        return false;
    }
    person* ThisGuy=new person;
    ThisGuy->First=first;
    ThisGuy->Last=last;
    ThisGuy->email=email;
    ThisGuy->password=password;

    ListOfPeople.append(*ThisGuy);

    return true;
}

#endif // ACCOUNTCHECKANDSTORE_C
