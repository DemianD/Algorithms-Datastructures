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
//class Lijstknoop:public string{
//    int a;
//public:
//    Lijstknoop(){};
//};
Lijst<int> maak(){
    Lijst<int> l;
    l.voegToe(int(7));
    l.voegToe(int(45));
    l.voegToe(int(15));
    l.voegToe(int(45));
    l.voegToe(int(25));
    l.voegToe(int(35));
    l.voegToe(int(45));
    l.voegToe(int(55));
    gemaakt+=8;   
    return l;    
};


int main(){
    {
	
       cerr<<"maak met transfer\n";
        Lijst<int> l;
        l=maak();
        l.schrijf(cerr);
    	cerr<<endl;
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        
        cerr<<"\n\nverwijderen\n";
        l.verwijder(45);
        verwijderd++;
        l.verwijder(123);
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        
//    //    for (auto s:l)
//    //        cerr<<s<<"\n";
//    //    l.schrijf(cerr);

        cerr<<"\n\nLosse oproep maak\n";
        maak();
        verwijderd +=8;
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        
        cerr<<"\n\nmaak() in constructor\n";
        Lijst<int> l2(maak());
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        
        cerr<<"\n\nduplicaat 1\n";
        l2=l;
        cerr<<"\t inhoud van L1:\n";
        l.schrijf(cerr);        
        cerr<<"\n\t inhoud van L2:\n";
        l2.schrijf(cerr);
        cerr<<"\n";
		verwijderd+=8;
        gemaakt+=7;        
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        
        cerr<<"\n\nduplicaat 2\n";
        l2=l;
        gemaakt+=7;
        verwijderd+=7;
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        
        cerr<<"\n\nduplicaat 3\n";
        l2=l2;
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        
        l2.schrijf(cerr);             
        cerr<<"\n\nduplicaat 4\n";
        Lijst<int> l3;
        cerr<<"lijst l3 staat leeg klaar\n\n";
        l3.voegToe(int(99));
        gemaakt++;
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        cerr<<"start of l3=l2=l\n";
        l3 = l2 = l;
        verwijderd+=8;  
        gemaakt+=14;    
        Lijstknoop<int>::controle(gemaakt,verwijderd);

        
        cerr<<"\n\ninsertion sort\n";
        l2.insertionsort();
        cerr<<"does this look sorted?\n";
        cerr<<"Content of l2:\n";
        l2.schrijf(cerr);
        cerr<<"\n";
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        cerr<<"verwijderen\n";
        cerr<<"Content of l1:\n";
        l.schrijf(cerr);
        cerr<<"\n";
        l.verwijder(45);
        l.verwijder(45);
        l.verwijder(45);
        l.verwijder(45);
        verwijderd+=2;
        cerr<<"Content of l1:\n";
        l.schrijf(cerr);
        cerr<<"\n";
        Lijstknoop<int>::controle(gemaakt,verwijderd);
        
        cerr<<"\n\nswappen\n";
        swap(l2,l);
        Lijstknoop<int>::controle(gemaakt,verwijderd);
//        l2.schrijf(cerr);
//        cerr<<"\n";        
	}
    verwijderd+=19;
    Lijstknoop<int>::controle(gemaakt,verwijderd);
    return 0;
}
