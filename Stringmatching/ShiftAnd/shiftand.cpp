#include <iostream>
#include "bitpattern.hpp"
#include "shiftand.hpp"
#include <string>
#include <queue>
#include <array>

using namespace std;

int main(int argc, char **argv)
{
    Bitpatroon x = Bitpatroon::eenbit(2);

    uchar var[] = "aras";
    Shiftand sa(var, 4);
    queue<const uchar *> plaats;
    const uchar hooiberg[] = "ara ras rasa arasarassa";

    sa.zoek(plaats, hooiberg, 32);
    while (!plaats.empty())
    {
        const uchar *p = plaats.front();
        cout << "patroon komt voor in hooiberg ";
        for (int i = 0; i < sizeof(var) / sizeof(var[0]) - 1; i++)
        {
            cout << *(p + i);
        }
        cout << endl;
        plaats.pop();
    }
    return 0;
}