/* Generic singleton as explained here:
 * https://www.devarticles.com/c/a/Cplusplus/C-plus-plus-In-Theory-The-Singleton-Pattern-Part-2/1/
 * To use a class as a singleton, do the following:
 *  In the class you want to turn into a singleton, add #include "singleton.h"
 * Then, to use the class:
 *  typedef Singleton<<Your Class>> WhateverYouWantToCallIt;
 *  ex. typedef Singleton<DatabaseManager> DatabaseManagerSingleton;
 *
 *  to call methods on the singleton:
 *  WhateverYouWantToCallIt::Instance().method(...);
 *  ex. DatabaseManagerSingleton::Instance().getTvShow(name, tvShow);
 *
 * @author Allan Haywood
 */

#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{
public:
static T& Instance()
{
    static T _instance;
    return _instance;
}

template <class C> static T& Instance(C val)
{
    static T _instance(val);
    return _instance;
}

/* Attempt at Variadic template, not compiling
template <class... Args>
static T& Instance(Args&&... args)
{
    static T _instance(Args&&... args);
    return _instance;
}
*/


private:
  Singleton();          // ctor hidden
  ~Singleton();          // dtor hidden
  Singleton(Singleton const&);    // copy ctor hidden
  Singleton& operator=(Singleton const&);  // assign op hidden
};

#endif // SINGLETON_H
