#include<iostream>
#include<cstring>
using namespace std;
/*���¶�ʡ�Ե�ǰ�����thisָ�룬���ڱ�Ҫʱ����thisָ�루��ǰ����*/

class MyString
{
public:
	MyString(const char* pData = NULL);	    // ��ͨ���캯��
	MyString(const MyString &);	        	    // �������캯��
	~ MyString();                               // ��������
	MyString& operator =(const MyString &);	// ��ֵ����
	MyString& operator += (const MyString &);
	operator char* () const;        // �Զ�ת������
	void Show()
	{
		cout << mpData << endl;
	}
private:
	char *mpData;		// ���ڱ����ַ���
};


const MyString  operator+(const MyString &, const MyString &); //�ַ�������
ostream& operator<<(ostream& os, const MyString& str); 		///������� ???


MyString::MyString(const char* pData)
{
	if(pData == NULL)
	{
		mpData = new char[1];
		mpData[0] = '\0';
	}
	else
	{
		mpData = new char[strlen(pData) + 1]; //+1��ʾ��β��'\0'
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

MyString& MyString::operator =(const MyString&str)//���������A=B A=(operator=(B));
{
	if(this == &str) //�Ƚ����������Ƿ�һ�����Ƚϵ�ַ�Ƿ�һ�£�
		return *this;//���ظ�ֵ��Ķ���
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
		char*temp = mpData; //��ʱ����ǰ�������ַ�������������
		mpData = new char[strlen(temp) + strlen(str.mpData) + 1];
		strcpy(mpData, temp);
		delete temp;
		strcat(mpData,str.mpData);//��str.Data��ָ�ַ�����ӵ�mpData��β��(����dest��β����'\0')�����'\0'
		return *this;
	}
}

MyString::operator char*() const        ///�Զ�ת��������������
{
    return mpData;
}

const MyString  operator+(const MyString &str1,const MyString &str2)
{
    MyString temp(str1);//������ʱ����
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
