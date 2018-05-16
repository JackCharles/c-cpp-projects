#include <iostream>
using namespace std;
#include "function.h"

ContinueFraction::ContinueFraction(double value,int maxlen)
{
    ai = int(value);
    if ((maxlen>1) &&  (value-ai>0.00001))
        next = new ContinueFraction(1.0/(value-ai),maxlen-1);
    else
        next = NULL;
}
ContinueFraction::~ContinueFraction()
{
    delete next;
}

void  ContinueFraction::GetFzFm(long& fz,long& fm,int len)
{
    if ( (len==1) || (next == NULL)) {
        fz = ai;
        fm = 1;
    }else {
        next->GetFzFm(fz,fm,len-1);
        long newfz = ai*fz+fm;
        fm = fz;
        fz = newfz;
    }
}

int  ContinueFraction::GetAi(int index)
{
    if (index == 1)
        return ai;
    else if (next == NULL)
        return 0;
    else
        return next->GetAi(index-1);
}

void ContinueFraction::Display(int len)
{
    cout<<ai;
    if ( (len ==1) || (next == NULL) ) {
        cout<<endl;
    }else  {
        cout<<"+";
        next->Display(len-1);
    }
}
