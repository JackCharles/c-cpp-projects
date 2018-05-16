#include<iostream>
using namespace std;


class Bottle
{
	public:
		Bottle(){
			bo10=10;
			bo7=0;
			bo3=0;
		}
		int bo10;
		int bo7;
		int bo3;

		void Pour10_to_7();
		void Pour7_to_3();
		void Pour3_to_10();
};

void Bottle::Pour10_to_7()
{
	if(bo10 > (7 - bo7))
	{
		bo10 = bo10 - (7 - bo7);
		bo7 = 7;
	}
	else
	{
		bo7 = bo7 + bo10;
		bo10 = 0;
	}
}

void Bottle::Pour7_to_3()
{
	if(bo7 > (3 - bo3))
	{
		bo7 = bo7 - (3 - bo3);
		bo3 = 3;
	}
	else
	{
		bo3 = bo3 + bo7;
		bo7 = 0;
	}
}

void Bottle::Pour3_to_10()
{
	if(bo3 > (10 - bo10))
	{
		bo3 = bo3 - (10 - bo10);
		bo10 = 10;
	}
	else
	{
		bo10 = bo10 + bo3;
		bo3 = 0;
	}
}

int main()
{
	Bottle oil;
	oil.Pour10_to_7();
	oil.Pour7_to_3();
	oil.Pour3_to_10();
	oil.Pour7_to_3();
	oil.Pour3_to_10();
	oil.Pour7_to_3();
	oil.Pour10_to_7();
	oil.Pour7_to_3();
	oil.Pour3_to_10();

	cout << "10斤的瓶中有" << oil.bo10 << "斤" << endl;
	cout << "7斤的瓶中有" << oil.bo7 << "斤" << endl;
	cout << "3斤的瓶中有" << oil.bo3 << "斤" << endl;
	return 0;
}
