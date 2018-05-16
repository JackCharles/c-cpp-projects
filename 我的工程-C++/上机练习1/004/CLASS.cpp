1.

class Pen
{
	public:
		void DisplayInf()
		{
			cout << tepy << '\n' << price << '\n' << number << endl;
		}
	private:
		int price;
		int number;
		char tepy;
};

2.

class FileDirectory
{
	public:
		void Input()
		{
			cin >> fileName;
			cin >> fileCatalog;
		}
	private:
		char*fileName[];
		char*fileCatalog[];
};

3.

class PrintDevirce
{
	public:
		void DisplayInf()
		{
			cout << ...
		}
	private:
		char*owner[];
		char*tepy[];
		float price;
		float volume;
		float weight;
		bool useful;
};


4.

class Object
{
	public:
		float  Density(int r , int m)
		{
			float v = (4 / 3) * 3.14 * r * r * r;
			return m / v;
		}
	private:
		int r;
		int m;
		long distance;
}

