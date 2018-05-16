#include<iostream>
using namespace std;


class Demo
{
public:
    static Demo*GetInstance()
    {
        static Demo *pDemo=NULL;
        if(pDemo==NULL)
            pDemo=new Demo;
        return pDemo;
    }
	/*Demo()
	{
		mNum = 0;

	}*/
	void  AddValue(int value)
	{
		mNum += value;
	}
	void  ShowValue(int value) const
	{
		cout << "Value=" << value << endl;
	}
private:
    Demo(){}
    Demo(const Demo&);
    Demo&operator=(const Demo&);
	int   mNum;
};
