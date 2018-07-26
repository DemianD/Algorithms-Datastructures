#include <iostream>
#include <memory>
#include "bst14.hpp"

using namespace std;


int main(int argc, char** argv){
    BST<int,int> t;
    t.add(1,1);
    BST<int,int> t2 = move(t);
    BST<int,int> t3 = t2;
    BST<int,int> t4;
    t4 = move(t2);
    t4 = t3;
    
    unique_ptr nodeptr = std::make_unique<BSTnode<int,int>>();
    t4 = move(nodeptr);
    return 0;
}