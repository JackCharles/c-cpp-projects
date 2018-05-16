#include<iostream>
using namespace std;

class Hero
{
public:
	Hero();
	void GetInfo() const;//输出当前状态
	void CarryTrea(int pos, int trea); //带宝物
	void AbnudTrea(int pos, int trea); //丢弃宝物
private:
	int trea_pos[5];//宝物位置
	int charm;//魅力
	int reputation;//声望
	int attack;//攻击力
	int defense;//防御力
	int mana;//法力值
};

Hero::Hero()//初始化
{
	for(int i = 0; i < 5; i++)
		trea_pos[i] = 0;
    charm=10;
    reputation=10;
    attack=10;
    defense=10;
    mana=10;
}

void Hero::GetInfo() const//输出当前状态
{
    cout<<"魅力值:     "<<charm<<endl;
    cout<<"声望值:     "<<reputation<<endl;
    cout<<"攻击力:     "<<attack<<endl;
    cout<<"防御力:     "<<defense<<endl;
    cout<<"法力值:     "<<mana<<endl;
    cout<<"宝物位置:   1   2   3   4   5"<<endl;
    cout<<"所带宝物:   "<<trea_pos[0]<<"   "<<trea_pos[1]<<"   ";
    cout<<trea_pos[2]<<"   "<<trea_pos[3]<<"   "<<trea_pos[4]<<endl;

}

void Hero::CarryTrea(int pos,int trea)//携带宝物
{
    if(trea_pos[pos-1]!=0)
        cout<<"你的英雄"<<pos<<"宝物位置已被占用!"<<endl;
    else
    {
        switch(trea)
        {
            case 1: charm+=2;       break;
            case 2: reputation+=3;  break;
            case 3: attack+=1;      break;
            case 4: defense+=2;     break;
            case 5: mana+=1;        break;
            case 6: attack+=4;      break;
            default:cout<<"你要携带的宝物不存在!"<<endl;
        }
        trea_pos[pos-1]=trea;
    }
}

void Hero::AbnudTrea(int pos,int trea)//丢弃宝物
{
    if(trea_pos[pos-1]==0)
        cout<<"你的英雄"<<pos<<"位置没有宝物!"<<endl;
    else
    {
        switch(trea)
        {
            case 1: charm-=2;       break;
            case 2: reputation-=3;  break;
            case 3: attack-=1;      break;
            case 4: defense-=2;     break;
            case 5: mana-=1;        break;
            case 6: attack-=4;      break;
            default:cout<<"你要丢弃的宝物不存在!"<<endl;
        }
        trea_pos[pos-1]=0;
    }
}


int main()
{
    Hero hero;
    hero.CarryTrea(3,6);
    hero.GetInfo();
    hero.AbnudTrea(2,4);

    return 0;
}
