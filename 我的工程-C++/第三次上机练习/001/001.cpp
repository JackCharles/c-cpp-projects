#include<iostream>
#include<cstring>
using namespace std;
/*以下都省略当前对象的this指针，并在必要时返回this指针（当前对象）*/

class MyString
{
public:
	MyString(const char* pData = NULL);	    // 普通构造函数
	MyString(const MyString &);	        	    // 拷贝构造函数
	~ MyString();                               // 析构函数
	MyString& operator =(const MyString &);	// 赋值函数
	MyString& operator += (const MyString &);
	operator char* () const;        // 自动转换函数
	void Show()
	{
		cout << mpData << endl;
	}
private:
	char *mpData;		// 用于保存字符串
};


const MyString  operator+(const MyString &, const MyString &); //字符串连接
ostream& operator<<(ostream& os, const MyString& str); 		///定向输出 ???


MyString::MyString(const char* pData)
{
	if(pData == NULL)
	{
		mpData = new char[1];
		mpData[0] = '\0';
	}
	else
	{
		mpData = new char[strlen(pData) + 1]; //+1表示结尾的'\0'
		strcpy(mpData, pData);
	}
}

MyString::MyString(const MyString& str)///MyString A(B);
{
	mpData = new char[strlen(str.mpData) + 1];
	strcpy(this->mpData, str.mpData);
}

MyString::~MyString()
{
	delete[](mpData);
}

MyString& MyString::operator =(const MyString&str)//运算符重载A=B A=(operator=(B));
{
	if(this == &str) //比较两个对象是否一样（比较地址是否一致）
		return *this;//返回赋值后的对象
	else
	{
		delete[](mpData);
		this->mpData = new char[strlen(str.mpData) + 1];
		strcpy(mpData, str.mpData);
		return *this;
	}
}

MyString& MyString::operator +=(const MyString &str)
{
	if(str.mpData == NULL)
		return *this;
	else
	{
		char*temp = mpData; //暂时将当前对象中字符串保存起来；
		mpData = new char[strlen(temp) + strlen(str.mpData) + 1];
		strcpy(mpData, temp);
		delete temp;
		strcat(mpData,str.mpData);//把str.Data所指字符串添加到mpData结尾处(覆盖dest结尾处的'\0')并添加'\0'
		return *this;
	}
}

MyString::operator char*() const        ///自动转换函数？？？？
{
    return mpData;
}

const MyString  operator+(const MyString &str1,const MyString &str2)
{
    MyString temp(str1);//创建临时对象
    temp+=str2;
    return temp;
}
ostream& operator<<(ostream& os, const MyString& str)///???
{
    os<<(char*)str;
    return os;
}                                                      ///???

int main()
{
	MyString a("Hello ");
	MyString b("World!");
	MyString c(NULL);
	c=a+b;
	a += b;
	a.Show();
	c.Show();
}
