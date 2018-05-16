#ifndef A_H
#define A_H
#include <iostream>
using namespace std;

class A {
public:
    inline void Display() const {
           cout<<"The argment is NULL"<<endl;
    }

    inline void Display(const char * str) const {
           cout<<"The argment is "<<str<<endl;
    }
    void OtherFunc() {
    }
};

#endif
