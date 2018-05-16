#ifndef PERSON_H
#define PERSON_H

class Walker;
class Thief;
class PoliceOffice;


class Polices///警察
{
public:
    Polices(int mon):money(mon){}
    void Arrest(PoliceOffice&,Thief& );
    int GetMoney();
    ~Polices(){}
private:
    int money;
};

class Thief///小偷
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

class Walker///行人
{
public:
    friend void Thief::Steal(Walker&);
    Walker(int mon):money(mon){}
    int GetMoney();
    ~Walker(){}
private:
    int money;
};



class PoliceOffice///警察局
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
