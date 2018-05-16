#ifndef HEADFILE_H_INCLUDED
#define HEADFILE_H_INCLUDED
class Horse;

class Hero
{
public:
    Hero(int hp,int pw);
    void GetHorse(Horse&);
    void LoseHorse();
    void Fight(Horse&);
    void Recover();
    ~Hero(){}
private:
    int hitpoint;
    int hitpoint_BackUp;
    int power;
    int power_BackUp;
    Horse *p=NULL;
};

class Horse
{
public:
    Horse(int hp,int da,int de,int sp);
    friend void Hero::Fight(Horse&);
    void recover();
    ~Horse(){}
private:
    int hitpoint;
    const int hitpoint_BackUp;
    int damage;
    const int damage_BackUp;
    int defense;
    const int defense_BackUp;
    int speed;
    const int speed_BackUp;
};
#endif // HEADFILE_H_INCLUDED
