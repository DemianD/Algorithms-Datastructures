#include <iostream>
using std::cout;
using std::endl;
#include "bst.hpp"
#include <utility>
using std::move;
#include <memory>
using std::make_unique;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <functional>
using std::function;

void construction_tests();

int main(int argc, char ** argv){        
    //construction_tests();

    BST<int> bst;
    bst = move(make_unique<BSTnode<int>>(100));
    if(bst) {
        cout<<"Yes"<<endl;
    }
    else cout<<"No"<<endl;
    
    bst.add(50);
    bst.add(20);
    bst.add(10);
    bst.add(40);
    bst.add(50);
    bst.add(70);
    bst.add(-10);

    auto bfsfct = [](int item){ cout<<item<<endl; };
    bst.BFS(bfsfct);


    return 0;
}

void construction_tests(){
    vector<int> vx = { 1 };
    BST<string> b("hi");
    BST<int> bs(4);
    BST<int> bst(10);
    BST<vector<int>> bstv(vx);    
    b.test();
    bs.test();
    bst.test();
    bstv.testvec();
}