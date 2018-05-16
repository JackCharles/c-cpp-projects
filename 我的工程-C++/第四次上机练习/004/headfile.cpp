#include<iostream>
#include"headfile.h"
using namespace std;

Hero::Hero(int hp,int pw):hitpoint_BackUp(hp),power_BackUp(pw)//构造函数
{
    hitpoint=hp;
    power=pw;
}

void Hero::GetHorse(Horse&horse)//分配坐骑
{
    p=&horse;
}

void Hero::LoseHorse()//失去坐骑
{
    p=NULL;
}

void Hero::Fight(Horse&horse)//战斗
{
    while(1)
    {
        if((p->damage*(p->speed+power)-(horse.defense*horse.speed))<1)
            horse.hitpoint-=(1+power*20);
        else
            horse.hitpoint-=((p->damage*(p->speed+power)-(horse.defense*horse.speed))+(power*20));
        if(horse.hitpoint<=0)
        {
            cout<<"You have won the game!"<<endl;
            hitpoint_BackUp+=10;
            break;
        }
        if((horse.damage*horse.speed-p->defense*p->speed)<1)
        {
            hitpoint-=1;
            p->hitpoint-=1;
        }
        else
        {
            hitpoint-=(horse.damage*horse.speed-p->defense*p->speed);
            p->hitpoint-=(horse.damage*horse.speed-p->defense*p->speed);
        }
        if((hitpoint<=0) && (p->hitpoint>0))
        {
            cout<<"The hero died,and you have lost!"<<endl;
            if(power>1)
                power--;
            break;
        }
        else if(p->hitpoint<=0)
        {
            cout<<"Your horse died,and you have lost!"<<endl;
            LoseHorse();
            break;
        }
    }
}

void Hero::Recover()//英雄恢复
{
    hitpoint=hitpoint_BackUp;
    power=power_BackUp;
}

Horse::Horse(int hp,int da,int de,int sp)://马初始化
hitpoint_BackUp(hp),damage_BackUp(da),defense_BackUp(de),speed_BackUp(sp)
{
    hitpoint=hp;
    damage=da;
    defense=de;
    speed=sp;
}

void Horse::recover()//马恢复
{
    hitpoint=hitpoint_BackUp;
    damage=damage_BackUp;
    defense=defense_BackUp;
    speed=speed_BackUp;
}
