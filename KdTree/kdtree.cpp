#include "kdtree.hpp"
#include "kdnode.hpp"
#include <iostream>


using namespace std;

int main( int argc, char ** argv) {
    KdTree<int,int,int,int> t1(4);
    cout<<t1.depth()<<endl;

    return 0;
}