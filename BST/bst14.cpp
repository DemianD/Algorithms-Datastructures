#include <iostream>
#include <memory>
#include "bst14.hpp"

using namespace std;


int main(int argc, char** argv){
    BST<int,int> t;
    t.add(10,1);
    t.add(5,2);
    t.add(15,3);
    cout<<"t1\t";
    t.output(cout);
    BST<int,int> t2 = move(t);
    cout<<"t1\t";
    t.output(cout);    
    cout<<"t2\t";
    t2.output(cout);
    //BST<int,int> t3 = t2;  
    BST<int,int> t4;    
    t4 = move(t2);
    cout<<"t2\t";
    cout<<"t4\t";
    t4.output(cout);
    //t4 = t3;
       
    BST<int,int> nodeptr = std::make_unique<BSTnode<int,int>>();
    t4 = move(nodeptr);
    return 0;
}