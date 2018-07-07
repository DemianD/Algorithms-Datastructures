// testing program for the c++14 linked list implementation
#include <iostream>
#include <cstdlib>
#include "list14.h"
#include <string>

using std::cerr;
using std::string;
int gemaakt=0;   //aantallen gemaakte en verwijderde knopen.
int verwijderd=0;
// Wat volgt is een toepassing;
// deze wordt normaal door de gebruiker geschreven.
//class ListNode:public string{
//    int a;
//public:
//    ListNode(){};
//};
List<int> maak(){
    List<int> l;
    l.add(int(7));
    l.add(int(45));
    l.add(int(15));
    l.add(int(45));
    l.add(int(25));
    l.add(int(35));
    l.add(int(45));
    l.add(int(55));
    gemaakt+=8;   
    return l;    
};


int main(){
    {
	
       cerr<<"maak met transfer\n";
        List<int> l;
        l=maak();
        l.output(cerr);
    	cerr<<endl;
        ListNode<int>::control(gemaakt,verwijderd);
        
        cerr<<"\n\nverwijderen\n";
        l.remove(45);
        verwijderd++;
        l.remove(123);
        ListNode<int>::control(gemaakt,verwijderd);
        
//    //    for (auto s:l)
//    //        cerr<<s<<"\n";
//    //    l.output(cerr);

        cerr<<"\n\nLosse oproep maak\n";
        maak();
        verwijderd +=8;
        ListNode<int>::control(gemaakt,verwijderd);
        
        cerr<<"\n\nmaak() in constructor\n";
        List<int> l2(maak());
        ListNode<int>::control(gemaakt,verwijderd);
        
        cerr<<"\n\nduplicaat 1\n";
        l2=l;
        cerr<<"\t inhoud van L1:\n";
        l.output(cerr);        
        cerr<<"\n\t inhoud van L2:\n";
        l2.output(cerr);
        cerr<<"\n";
		verwijderd+=8;
        gemaakt+=7;        
        ListNode<int>::control(gemaakt,verwijderd);
        
        cerr<<"\n\nduplicaat 2\n";
        l2=l;
        gemaakt+=7;
        verwijderd+=7;
        ListNode<int>::control(gemaakt,verwijderd);
        
        cerr<<"\n\nduplicaat 3\n";
        l2=l2;
        ListNode<int>::control(gemaakt,verwijderd);
        
        l2.output(cerr);             
        cerr<<"\n\nduplicaat 4\n";
        List<int> l3;
        cerr<<"List l3 staat leeg klaar\n\n";
        l3.add(int(99));
        gemaakt++;
        ListNode<int>::control(gemaakt,verwijderd);
        cerr<<"start of l3=l2=l\n";
        l3 = l2 = l;
        verwijderd+=8;  
        gemaakt+=14;    
        ListNode<int>::control(gemaakt,verwijderd);

        
        cerr<<"\n\ninsertion sort\n";
        l2.insertionsort();
        cerr<<"does this look sorted?\n";
        cerr<<"Content of l2:\n";
        l2.output(cerr);
        cerr<<"\n";
        ListNode<int>::control(gemaakt,verwijderd);
        cerr<<"verwijderen\n";
        cerr<<"Content of l1:\n";
        l.output(cerr);
        cerr<<"\n";
        l.remove(45);
        l.remove(45);
        l.remove(45);
        l.remove(45);
        verwijderd+=2;
        cerr<<"Content of l1:\n";
        l.output(cerr);
        cerr<<"\n";
        ListNode<int>::control(gemaakt,verwijderd);
        
        cerr<<"\n\nswappen\n";
        swap(l2,l);
        ListNode<int>::control(gemaakt,verwijderd);
//        l2.output(cerr);
//        cerr<<"\n";        
	}
    verwijderd+=19;
    ListNode<int>::control(gemaakt,verwijderd);
    return 0;
}
