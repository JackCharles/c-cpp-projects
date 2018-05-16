#ifndef PERSON_H
#define PERSON_H

class Walker;
class Thief;
class PoliceOffice;


class Polices///����
{
public:
    Polices(int mon):money(mon){}
    void Arrest(PoliceOffice&,Thief& );
    int GetMoney();
    ~Polices(){}
private:
    int money;
};

class Thief///С͵
{
public:
    friend void Polices::Arrest(PoliceOffice&,Thief&);
    Thief(int mon):money(mon){}
    void Steal(Walker& );
    int GetMoney();
    ~Thief(){}
private:
    int money;
};

class Walker///����
{
public:
    friend void Thief::Steal(Walker&);
    Walker(int mon):money(mon){}
    int GetMoney();
    ~Walker(){}
private:
    int money;
};



class PoliceOffice///�����
{
public:
    PoliceOffice(int rep):reputation(rep){}
    friend void Polices::Arrest(PoliceOffice&,Thief&);
    int GetRep();
    ~PoliceOffice(){}
private:
    int reputation;
};


#endif
