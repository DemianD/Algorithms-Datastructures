#include "rbtree.hpp"
#include "rbnode.hpp"

#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char **argv)
{
    RBtree<int,int> t1(10,10,Color::BLACK);
    return 0;
}