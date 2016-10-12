#include "accountcheckandstore.h"
#include <QList>

AccountCheckAndStore::AccountCheckAndStore()
{
private:
    struct person
    {
        string First;
        string Last;
        string email;
        string password;
    };

    QList ListOfPeople;

    static AccountCheckAndStore* instance;

AccountCheckAndStore::AccountCheckAndStore()
{
    ListOfPeople=new QList<person>();
}

AccountCheckAndStore::~AccountCheckAndStore()
{

}

public:

static AccountCheckAndStore::getInstance()
{
    if(instance==NULL)
    {
        instance=new AccountCheckAndStore();
    }

    return instance;
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
    ThisGuy=new person;
    ThisGuy.first=first;
    ThisGuy.last=last;
    ThisGuy.email=email;
    ThisGuy.password=password;

    ListOfPeople.append(ThisGuy);

    return true;
}

}
