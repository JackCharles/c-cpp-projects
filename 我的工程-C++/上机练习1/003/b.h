#ifndef B_H
#define B_H

/*class B
{
	public:
		void Func();
	private:
		A   aA;
};
void B::Func()
{
	cout << "This is member function Func()" << endl;
}
*/

class B
{
	public:
		B(A& aA)
		{
			pA = &aA;
		}
		void Func()
		{
			cout << "This is member function Func()" << endl;
		}
		void NewFunc()
		{
			pA->OtherFunc();
		}

	private:
		A  *  pA;
};
#endif
