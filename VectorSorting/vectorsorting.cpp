#include <iostream>
#include <algorithm>
#include <exception>
#include <ctime>
#include "sortvector.hpp"
#include "sortingmethods.hpp"
#include "intstring.hpp"

using std::cout;
using std::endl;
using std::for_each;
using std::exception;

int main() {

    try {
        srand(time(0));
        cout << "Hello, World!" << endl;
        Sortvector<double> v(25);
        cout << "Normal Sortvector, is gesorteerd ? " << v.is_gesorteerd() << " en is range? " << v.is_range() << endl;
        cout << v;
        v.push_back(1);
        cout << "Normal Sortvector, is gesorteerd ? " << v.is_gesorteerd() << " en is range? " << v.is_range() << endl;
        cout << v;


        cout << "draai_om()" << endl;
        v.draai_om();
        cout << v;

        cout << "shuffle()" << endl;
        v.shuffle();
        cout << v;

        cout << "vul_random()" << endl;
        v.vul_random();
        cout << v;

        // 1. STL sort
        STLSort<double> stlsorter;
        stlsorter(v);
        cout << "stlsorter(v)" << endl;
        cout << v;
        stlsorter.measure(10, 10000, cout);

//        // 2. Insertion sort
//        cout << "vul_random_zonder_dubbels()" << endl;
//        v.vul_random_zonder_dubbels();
//        cout << v;
//        InsertionSort<double> insertionsorter;
//        insertionsorter(v);
//        cout << "insertionsorter(v)" << endl;
//        cout << v;
//        insertionsorter.measure(10, 1000,
//                             cout); // Niet te hoog zetten, insertionsort is worst case O(n²) en avg case ook O(n²), 10000->al 60+sec bij omgekeerd
//
//        cout << "Sortvector<Intstring>" << endl;
//        Sortvector<Intstring> strv(5);
//        strv.vul_random_zonder_dubbels();
//        STLSort<Intstring> stlsorter2;
//        stlsorter2(strv);
//        cout << strv;
////    stlsorter2.measure(10,1000000,cout);
//
//        v.vul_random_zonder_dubbels();
//        cout << v;
//        SelectionSort<double> selectionsorter;
//        selectionsorter(v);
//        cout << "selectionsorter(v)" << endl;
//        cout << v;
//        selectionsorter.measure(10, 1000, cout);
//
//        // 3. Shellsort
//        v.vul_random_zonder_dubbels();
//        cout << v;
//        ShellSort<double> shellsorter;
//        shellsorter(v);
//        cout << "shellsorter(v)" << endl;
//        cout << v;
//        shellsorter.measure(10, 1000, cout);
//
        // 4. TD merge sort
        v.vul_random_zonder_dubbels();
        cout << v;
        TDMergeSort<double> tdmergesorter;
        tdmergesorter(v);
        cout << "tdmergesorter(v)" << endl;
        cout << v;
        tdmergesorter.measure(10, 1000, cout);
//
//        // 5. BU merge sort
//        v.vul_random_zonder_dubbels();
//        cout << v;
//        BUMergeSort<double> bumergesorter;
//        bumergesorter(v);
//        cout << "bumergesorter(v)" << endl;
//        cout << v;
//        bumergesorter.measure(10, 1000, cout);

    // 6. Quicksort left pivot
    v.vul_random_zonder_dubbels();
    cout<<v;
    QuicksortLpiv<double> quicksorterlpiv;
    quicksorterlpiv(v);
    cout<<"quicksorterlpiv(v)"<<endl;
    cout<<v;
//
//    quicksorterlpiv.measure(10,1000,cout);
//
//    // 7. Quicksort right pivot
//    v.vul_random_zonder_dubbels();
//    cout<<v;
//    QuicksortRpiv<double> quicksorterrpiv;
//    quicksorterrpiv(v);
//    cout<<"quicksorterrpiv(v)"<<endl;
//    cout<<v;
//
//    quicksorterrpiv.measure(10,1000,cout);
//
//    // 8. Quicksort dual pivot
//    v.vul_random_zonder_dubbels();
//    cout<<v;
//    DualPivotQuicksort<double> quicksortdual;
//    quicksortdual(v);
//    cout<<"quicksortdual(v)"<<endl;
//    cout<<v;
//
//    quicksortdual.measure(10,1000,cout);
//
//    // 9. counting sort
//    Sortvector<int> w(8);
//    w.assign({0,0,12,5,7,3,4,7});
//    cout<<w;
//    Countingsort countingsorter;
//    countingsorter(w);
//    cout<<"countingsorter(w)"<<endl;
//    cout<<w;
//
//    // 10. counting sort 2
//    Sortvector<int> x(15);
//    x.assign({2,8,97,25,84,67,87,24,0,2,2,5,67,87,99});
//    cout<<x;
//    CountingSort2 countingsorter2;
//    countingsorter2(x);
//    cout<<"coutingsorter2(x)"<<endl;
//    cout<<x;
//    return 0;
    }
    catch(exception& e){
        cout<<e.what();
    }
}
