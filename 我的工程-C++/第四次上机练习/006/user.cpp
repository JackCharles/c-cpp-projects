//user.cpp
#include <iostream>
using namespace std;

#include "user.h"

User::User(int num):objShared(new Share(num))
{
    refCount = new int(1);
}

User::~User()
{
    releaseRef();
}


void User::addRef()
{
    ++(*refCount);
}

void User::releaseRef()
{
    if (--(*refCount) == 0)
    {
        delete refCount;
        delete objShared;
    }
}

//
User::User( const User& rhs )
{
    objShared = rhs.objShared;
    refCount  = rhs.refCount;
    addRef();
}


User& User::operator=( const User& rhs)
{
    if (this != &rhs)
    {
        releaseRef();

        objShared = rhs.objShared;
        refCount  = rhs.refCount;
        addRef();
    }
    return *this;
}

int User::getData() const
{
    return objShared->getData();
}

//按Copy On Write执行
void User::setData(int data)
{
    if(*refCount >= 2 )
    {
        releaseRef();
        objShared = new Share(data);
        refCount  = new int(1);
    }
    else
    {
        objShared->setData(data);
    }
}

void User::display(const char * objName) const
{
    cout<<"对象"<<objName<<"的属性为:"<<endl;
    cout<<"RefCount="<<*refCount<<endl;
    cout<<"共享对象的mData值 = "<< objShared->getData()<<endl<<endl;
}

