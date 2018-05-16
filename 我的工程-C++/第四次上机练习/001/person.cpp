#include<iostream>
#include"person.h"

void Thief::Steal(Walker& people)
{
    if(people.money>0)
    {
        money+=people.money;
        people.money=0;
    }
    else
        money+=0;
}

int Thief::GetMoney()
{
    return money;
}

int Walker::GetMoney()
{
    return money;
}

void Polices::Arrest(PoliceOffice&S,Thief& thief)
{
    money+=100;
    thief.money=0;
    S.reputation++;
}

int Polices::GetMoney()
{
    return money;
}

int PoliceOffice::GetRep()
{
    return reputation;
}
