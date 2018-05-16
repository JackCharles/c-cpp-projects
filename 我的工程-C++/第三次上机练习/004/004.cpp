#include<iostream>
using namespace std;

class A
{
public:
	A(int n): data(n) {}
	int Data() const
	{
		return data;
	}
private:
	int data;
};

void g(int n)
{
    A**p=new A*[n];
    for(int i=0;i<n;i++){
        p[i]=new A(i+1);
        cout<<p[i]->Data()<<endl;
    }
    for(int i=0;i<n;i++)
        delete[] p[i];
    delete[] p;
}

int main(int argc,char*argv[])
{
    g(5);
    return 0;
}
