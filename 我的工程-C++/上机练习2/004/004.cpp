#include<iostream>
using namespace std;

class Hero
{
public:
	Hero();
	void GetInfo() const;//�����ǰ״̬
	void CarryTrea(int pos, int trea); //������
	void AbnudTrea(int pos, int trea); //��������
private:
	int trea_pos[5];//����λ��
	int charm;//����
	int reputation;//����
	int attack;//������
	int defense;//������
	int mana;//����ֵ
};

Hero::Hero()//��ʼ��
{
	for(int i = 0; i < 5; i++)
		trea_pos[i] = 0;
    charm=10;
    reputation=10;
    attack=10;
    defense=10;
    mana=10;
}

void Hero::GetInfo() const//�����ǰ״̬
{
    cout<<"����ֵ:     "<<charm<<endl;
    cout<<"����ֵ:     "<<reputation<<endl;
    cout<<"������:     "<<attack<<endl;
    cout<<"������:     "<<defense<<endl;
    cout<<"����ֵ:     "<<mana<<endl;
    cout<<"����λ��:   1   2   3   4   5"<<endl;
    cout<<"��������:   "<<trea_pos[0]<<"   "<<trea_pos[1]<<"   ";
    cout<<trea_pos[2]<<"   "<<trea_pos[3]<<"   "<<trea_pos[4]<<endl;

}

void Hero::CarryTrea(int pos,int trea)//Я������
{
    if(trea_pos[pos-1]!=0)
        cout<<"���Ӣ��"<<pos<<"����λ���ѱ�ռ��!"<<endl;
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
            default:cout<<"��ҪЯ���ı��ﲻ����!"<<endl;
        }
        trea_pos[pos-1]=trea;
    }
}

void Hero::AbnudTrea(int pos,int trea)//��������
{
    if(trea_pos[pos-1]==0)
        cout<<"���Ӣ��"<<pos<<"λ��û�б���!"<<endl;
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
            default:cout<<"��Ҫ�����ı��ﲻ����!"<<endl;
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
