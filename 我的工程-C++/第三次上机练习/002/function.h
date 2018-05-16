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

    //Display函数最好改成取得一个连分数字符串表示的函数，从而避免使用cout。
    //如：  char *  TheString(int len); 。 这里使用Display只是为了方便。
    void  Display(int len);
private:
    int                     ai;
    ContinueFraction    *   next;
};

#endif /* CONTINUEFRACTION_H_ */
