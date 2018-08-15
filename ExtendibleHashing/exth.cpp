#include "exth.hpp"
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    ExtendibleHashTable<int,int> ht(1);
    ht.insert(0,0);
    ht.insert(1,1);
    ht.insert(2,2);
    ht.insert(3,3);
    return 0;
}