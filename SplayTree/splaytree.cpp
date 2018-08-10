#include "splaynode.hpp"
#include "splaytree.hpp"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int i = 0;
    SplayTree<int, int> t1(50, 50);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(100, 100);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(75, 75);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(25, 25);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(0, 0);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(40, 40);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    t1.insert_bottom_up(200, 200);

    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();

    t1.search(200);
    cout << i++ << '.' << '\n'
         << endl;
    t1.pretty_print();
    return 0;
}