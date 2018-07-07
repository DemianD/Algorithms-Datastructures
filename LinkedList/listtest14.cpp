// testing program for the c++14 linked list implementation
#include <iostream>
#include <cstdlib>
#include "list14.h"
#include <string>

using std::cerr;
using std::cout;
using std::string;
int nodesCreated = 0;
int nodesRemoved = 0;

List<int> createList()
{
    List<int> l;
    l.add(int(7));
    l.add(int(45));
    l.add(int(15));
    l.add(int(45));
    l.add(int(25));
    l.add(int(35));
    l.add(int(45));
    l.add(int(55));
    nodesCreated += 8;
    return l;
};

 int main(int argc, char** argv)
{

    cout << "Creating bare list" << endl;
    List<int> l;
    l = createList();
    l.output(cerr);
    cerr << endl;
    ListNode<int>::control(nodesCreated, nodesRemoved);

    cerr << "\n\nverwijderen\n";
    l.remove(45);
    nodesRemoved++;
    l.remove(123);
    ListNode<int>::control(nodesCreated, nodesRemoved);

    //    //    for (auto s:l)
    //    //        cerr<<s<<"\n";
    //    //    l.output(cerr);

    cerr << "\n\nLosse oproep createList\n";
    createList();
    nodesRemoved += 8;
    ListNode<int>::control(nodesCreated, nodesRemoved);

    cerr << "\n\ncreateList() in constructor\n";
    List<int> l2(createList());
    ListNode<int>::control(nodesCreated, nodesRemoved);

    cerr << "\n\nduplicaat 1\n";
    l2 = l;
    cerr << "\t inhoud van L1:\n";
    l.output(cerr);
    cerr << "\n\t inhoud van L2:\n";
    l2.output(cerr);
    cerr << "\n";
    nodesRemoved += 8;
    nodesCreated += 7;
    ListNode<int>::control(nodesCreated, nodesRemoved);

    cerr << "\n\nduplicaat 2\n";
    l2 = l;
    nodesCreated += 7;
    nodesRemoved += 7;
    ListNode<int>::control(nodesCreated, nodesRemoved);

    cerr << "\n\nduplicaat 3\n";
    l2 = l2;
    ListNode<int>::control(nodesCreated, nodesRemoved);

    l2.output(cerr);
    cerr << "\n\nduplicaat 4\n";
    List<int> l3;
    cerr << "List l3 staat leeg klaar\n\n";
    l3.add(int(99));
    nodesCreated++;
    ListNode<int>::control(nodesCreated, nodesRemoved);
    cerr << "start of l3=l2=l\n";
    l3 = l2 = l;
    nodesRemoved += 8;
    nodesCreated += 14;
    ListNode<int>::control(nodesCreated, nodesRemoved);

    cerr << "\n\ninsertion sort\n";
    l2.insertionsort();
    cerr << "does this look sorted?\n";
    cerr << "Content of l2:\n";
    l2.output(cerr);
    cerr << "\n";
    ListNode<int>::control(nodesCreated, nodesRemoved);
    cerr << "verwijderen\n";
    cerr << "Content of l1:\n";
    l.output(cerr);
    cerr << "\n";
    l.remove(45);
    l.remove(45);
    l.remove(45);
    l.remove(45);
    nodesRemoved += 2;
    cerr << "Content of l1:\n";
    l.output(cerr);
    cerr << "\n";
    ListNode<int>::control(nodesCreated, nodesRemoved);

    cerr << "\n\nswappen\n";
    swap(l2, l);
    ListNode<int>::control(nodesCreated, nodesRemoved);
    //        l2.output(cerr);
    //        cerr<<"\n";

    nodesRemoved += 19;
    ListNode<int>::control(nodesCreated, nodesRemoved);    
    return 0;
}
