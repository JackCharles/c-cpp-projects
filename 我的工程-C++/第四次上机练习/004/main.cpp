#include <iostream>
#include"headfile.h"
using namespace std;

int main()
{
    Hero ahero(100056,3);
    Horse h1(2000,28,32,8),h2(60045,14,7,2);
    ahero.GetHorse(h2);
    ahero.Fight(h1);
    ahero.Recover();
    h1.recover();
    h2.recover();
    return 0;
}
