#ifndef CONTINUEFRACTION_H_
#define CONTINUEFRACTION_H_

class ContinueFraction
{
public:
    ContinueFraction(double value,int maxlen=100);
    ~ContinueFraction();
public:
    void  GetFzFm(long& fz,long& fm,int len);
    int   GetAi(int index);

    //Display������øĳ�ȡ��һ���������ַ�����ʾ�ĺ������Ӷ�����ʹ��cout��
    //�磺  char *  TheString(int len); �� ����ʹ��Displayֻ��Ϊ�˷��㡣
    void  Display(int len);
private:
    int                     ai;
    ContinueFraction    *   next;
};

#endif /* CONTINUEFRACTION_H_ */
