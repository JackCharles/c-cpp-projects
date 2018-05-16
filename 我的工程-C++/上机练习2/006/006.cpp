#include<iostream>
using namespace std;


class Monster
{
public:
	Monster(int s, int h, int da, int de):
		speed(s), hitpoint(h), damage(da), defense(de) {}
	void Fight(Monster&A, Monster&B);

private:
	int Check(Monster&, Monster&);
	int speed;
	int hitpoint;
	int damage;
	int defense;
};

int Monster::Check(Monster&A, Monster&B)
{
	if(A.speed > B.speed)
		return 1;
	else if(A.speed < B.speed)
		return 2;
	else if(A.speed == B.speed)
	{
		if(A.hitpoint > B.hitpoint)
			return 1;
		else if(A.hitpoint < B.hitpoint)
			return 2;
		else if(A.hitpoint == B.hitpoint)
		{
			if(A.damage > B.damage)
				return 1;
			else if(A.damage < B.damage)
				return 2;
			else
			{
				if(A.defense > B.defense)
					return 1;
				else if(A.defense < B.defense)
					return 2;
				else
					return 3;
			}
		}
	}
}
void Monster::Fight(Monster&A, Monster&B)
{
	int i = Check(A, B); //1代表A先，2代表B先,3代表一样
	if(i == 1||i==3)
		while(1)
		{
			B.hitpoint = B.hitpoint - (2 * (A.damage) - B.defense);
			if(B.hitpoint <= 0)
			{
				cout << "The monster A win" << endl;
				break;
			}
			A.hitpoint = A.hitpoint - (2 * (B.damage) - A.defense);
			if(A.hitpoint <= 0)
			{
				cout << "The monster B win" << endl;
				break;
			}
		}
    else if(i==2)
        while(1)
		{
			A.hitpoint = A.hitpoint - (2 * (B.damage) - A.defense);
			if(A.hitpoint <= 0)
			{
				cout << "The monster B win" << endl;
				break;
			}
			B.hitpoint = A.hitpoint - (2 * (A.damage) - B.defense);
			if(B.hitpoint <= 0)
			{
				cout << "The monster A win" << endl;
				break;
			}
		}
}


int main()
{
	Monster A(130, 120, 40, 50), B(110, 90, 45, 30);
	A.Fight(A, B);
	return 0;
}
