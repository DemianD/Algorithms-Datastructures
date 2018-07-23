#ifndef __SORTINGMETHODS_HPP
#define __SORTINGMETHODS_HPP
#include "sortvector.hpp"
#include "chrono.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
    using std::move;
    using std::swap;
    using std::endl;
    using std::cout;
#include <algorithm>  // for STL sort
#include <iomanip>   // setw
#include <climits> // INT_MAX

template <typename T>
class Sorteermethode{
    public:
// The function operator
        virtual void operator()(vector<T> & v) const = 0;

// \fn measure(int kortste, int langste, ostream& os) schrijft naar os een overzicht (met de nodige ornamenten)
// met de snelheid van de opgegeven sorteermethode *this. Er wordt 1 lijn uitgedrukt voor elke mogelijke
// grootte. Deze groottes zijn kleinste, 10*kleinste, 100*kleinste,
// enzovoorts, tot aan grootste.
// Op een lijn staat de snelheid van de methode toegepast op
// (1) een random tabel
// (2) een al gesorteerde tabel.
// (3) een omgekeerd gesorteerde tabel.

// Deze functie werkt alleen als T een toekenning van een int toelaat,
// zodat bv.
//    T a=5;
// geldig is.
void measure(int kortste, int langste, ostream& os);

};
template <typename T>
void Sorteermethode<T>::measure(int kortste, int langste, ostream& os){
    Chrono chron;
    os<<setw(10)<<"lengte"<<setw(10)<<"random"<<setw(12)<<"gesorteerd"<<setw(12)<<"omgekeerd"<<endl;

    for(int i=1;i<=langste;i*=10) {
        Sortvector<T> vec(kortste*i);

        os<<setw(10)<<i;

        vec.vul_random();
        chron.start();
        (*this)(vec);
        chron.stop();
        os<<setw(10)<<chron.elapsed();

        chron.start();
        (*this)(vec);
        chron.stop();
        os<<setw(12)<<chron.elapsed();

        vec.draai_om();
        chron.start();
        (*this)(vec);
        chron.stop();
        os<<setw(12)<<chron.elapsed();
        os<<endl;
    }
}

/** \class STLSort
   \brief STANDARD TEMPLATE LIBRARY SORT
*/
template <typename T>
class STLSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const{
    sort(v.begin(),v.end());
}

/** \class InsertionSort
*/
template <typename T>
class InsertionSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;   
};

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const{
    for(int i=1; i<v.size(); i++){
        T h;
        h=move(v[i]);
        int j=i-1;
        while(j>=0 && h<v[j]){
            v[j+1] = move(v[j]);
            j--;
        }
        v[j+1] = move(h);
    }
}

/** \class Selectionsort
*/

template<typename T>
class SelectionSort : public Sorteermethode<T> {
public:
    void operator() (vector<T>& v) const;
};

template<typename T>
void SelectionSort<T>::operator()(vector<T>& v)const {
    for(int i = v.size()-1; i>0;i--){
        int maxindex = i;
        T hulp = move(v[i]);
        for(int j = 0;j<i;j++){
            if(v[maxindex] < v[j]) {
                maxindex = j;
            }
        }
        v[i] = move(v[maxindex]);
        v[maxindex] = move(hulp);
    }
}




/** \class Shellsort
*/
 
template <typename T>
class ShellSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
};

template<typename T>
void ShellSort<T>::operator()(vector<T>& v) const{
    // k volgens de reeks van tokuda k=ceil(9*(9/4)^i-4)/5)
    vector<int> increments;
    int u = 0;
    while(std::ceil((9*std::pow(9.0/4,u)-4)/5) < v.size()/2){
        increments.push_back(std::ceil((9*std::pow(9.0/4,u)-4)/5));
        u++;
    }


    int k=increments[--u];
    while(k>=1){
        for(int i = k; i<v.size(); i++){
            T h = move(v[i]);
            int j = i-k;
            while(j>=0 && h<v[j]){
                v[j+k]=move(v[j]);
                j-=k;
            }
            v[j+k]=move(h);
        }
        k = increments[--u];
    }
}

template<typename T>
class TDMergeSort : public Sorteermethode<T>{
    private:
    void mergesort(vector<T>&,int,int,vector<T>&) const;
    void merge(vector<T>&,int,int,int,vector<T>&) const;
    public:
    void operator()(vector<T>&v) const;
};

template<typename T>
void TDMergeSort<T>::operator()(vector<T>& v) const{
    vector<T> h((v.size()+1) / 2);
    mergesort(v,0,v.size(),h);
}

template<typename T>
void TDMergeSort<T>::mergesort(vector<T>& v, int links, int rechts, vector<T>& hulp) const{
    if(links < rechts-1){
        int midden = links + (rechts-links)/2;
        mergesort(v,links,midden,hulp);
        mergesort(v,midden,rechts,hulp);
        merge(v,links,midden,rechts,hulp);
    }  
}
// old merge
//template<typename T>
//void TDMergeSort<T>::merge(vector<T>& v, int links, int midden, int rechts, vector<T>& hulp) const{
//        int j = links;
//        int li = links;
//        int ri = midden;
//        while (li < midden && ri < rechts) {
//            if (v[li] < v[ri]) {
//                hulp[j++] = v[li++];
//            } else {
//                hulp[j++] = v[ri++];
//            }
//        }
//
//        while (li < midden) {
//            hulp[j++]=v[li++];
//        }
//        while (ri < rechts) {
//            hulp[j++]=v[ri++];
//        }
//    for(int i=links;i<rechts;i++){
//        v[i]=move(hulp[i]);
//    }
//}
template<typename T>
void TDMergeSort<T>::merge(vector<T>& v, int links, int midden, int rechts, vector<T>& hulp) const {
    hulp = {v.begin()+links, v.begin()+midden};
    int j = links;
    int ri = midden;
    midden -= links;
    int li = 0;

    while (li < midden && ri < rechts) {
        if (hulp[li] <= v[ri]) {
            v[j++] = hulp[li++];
        } else {
            v[j++] = v[ri++];
        }
    }

    while (li < midden) {
        v[j++]=hulp[li++];
    }
    while (ri < rechts) {
        v[j++]=v[ri++];
    }
}


template<typename T>
class BUMergeSort : public Sorteermethode<T>{
    private:
    void mergesort(vector<T>&,int,int,vector<T>&) const;
    void merge(vector<T>&, int,int,int,vector<T>&) const;
    public:
    void operator()(vector<T>&)const;
};

template<typename T>
void BUMergeSort<T>::operator()(vector<T>& v) const {
    vector<T> h(v.size());
    mergesort(v,0,v.size(),h);
}

template<typename T>
void BUMergeSort<T>::merge(vector<T>& v, int links, int midden, int rechts, vector<T>& hulp) const{
    int j = links;
    int li = links;
    int ri = midden;
    while (li < midden && ri < rechts) {
        if (v[li] < v[ri]) {
            hulp[j++] = v[li++];
        } else {
            hulp[j++] = v[ri++];
        }
    }

    while (li < midden) {
        hulp[j++]=v[li++];
    }
    while (ri < rechts) {
        hulp[j++]=v[ri++];
    }
    for(int i=links;i<rechts;i++){
        v[i]=hulp[i];
    }
}

template<typename T>
void BUMergeSort<T>::mergesort(vector<T>& v, int links, int rechts, vector<T>& hulp) const {
    for(int width=1; width < v.size(); width = 2*width){
        for(int i=0; i<v.size();i = i + 2*width){
            merge(v,i,std::min(i+width,(int)v.size()),std::min(i+2*width,(int)v.size()),hulp);
        }
    }
}


template<typename T>
class QuicksortLpiv : public Sorteermethode<T> {
    private:
    void quicksort(vector<T>&,int,int) const;
    public:
    void operator()(vector<T>&) const;
};

template<typename T>
void QuicksortLpiv<T>::quicksort(vector<T>& v,int l,int r) const{
    if(l<r){
        // ik kies L als spil, R kiezen kan ook, dan ga je wel eerst L een grotere moeten zoeken ipv rechts een kleinere
        T pivot = v[l];
        int i = l; 
        int j = r;

        while(v[j]>pivot) j--;
        while(i<j){
            swap(v[i],v[j]);
            i++;
            while(v[i]<pivot) i++;
            //j--;
            while(v[j]>pivot) j--;
        }
    quicksort(v,l,j);
    quicksort(v,j+1,r);
    }  
}

template<typename T>
void QuicksortLpiv<T>::operator()(vector<T>& v) const{
    quicksort(v,0,v.size()-1);
}


template<typename T>
class QuicksortRpiv : public Sorteermethode<T>{
    private:
    void quicksort(vector<T>&, int, int) const;
    public:
    void operator()(vector<T>&) const;
};


template<typename T>
void QuicksortRpiv<T>::quicksort(vector<T>& v, int l, int r) const{
    if(l<r){
        T pivot = v[r];
        int i = l; 
        int j = r;
        while(v[i]<pivot) i++;
        while(i<j){
            swap(v[i],v[j]);
            j--;
            while(v[j]>pivot) j--;
            i++;
            while(v[i]<pivot) i++;
        }
    quicksort(v,l,i-1);
    quicksort(v,i,r);
    }
}

template<typename T>
void QuicksortRpiv<T>::operator()(vector<T>& v) const {
    quicksort(v,0,v.size()-1);
}

template<typename T>
class DualPivotQuicksort : public Sorteermethode<T> {
    private:
        void quicksort(vector<T>&,int,int) const;
    public:
        void operator()(vector<T>&) const;
};

template<typename T>
void DualPivotQuicksort<T>::operator()(vector<T>& v) const{
    quicksort(v,0,v.size()-1);
}

template<typename T>
void DualPivotQuicksort<T>::quicksort(vector<T>& v, int left, int right) const{
    if(left<right){
        if(v[left]>v[right]) swap(v[left],v[right]);
        T lpiv = v[left];
        T rpiv = v[right];

        int l = left + 1;
        int k = l;
        int g = right -1;
        
        while(k<=g){
            if(v[k] < lpiv) {
                swap(v[k],v[l]);
                ++l;
            }
            else if(v[k] >= rpiv){
                while(v[g] > rpiv && k < g) --g;
                swap(v[k],v[g]);
                --g;
                if(v[k] < lpiv){
                    swap(v[k],v[l]);
                    ++l;
                }
            }
            ++k;
        }
        --l; 
        swap(v[left],v[l]);
        ++g;        
        swap(v[right],v[g]);

        quicksort(v,left,l-1);
        quicksort(v,l+1,g-1);
        quicksort(v,g+1,right);
    }
}

class Countingsort : Sorteermethode<int> {
    public:
    void operator()(vector<int>&) const;
};

void Countingsort::operator()(vector<int>& v) const{
    int kl = INT_MAX;
    int gr = 0;

    for(int t: v){
        if(t<kl) kl=t;
        else if(t>gr) gr=t;
    }

    vector<int> freq(gr+1);

    for(int t: v){
        freq[t] += 1;
    }

    vector<int> result;

    for(int i = 0;i<freq.size();i++){
        for(int j = 0; j<freq[i];j++){
            result.push_back(i);
        }
    }
    v = move(result);
}

class CountingSort2 : Sorteermethode<int> {
public:
    void operator()(vector<int>&)const;
};

void CountingSort2::operator()(vector<int>& v)const {
    int kl = INT_MAX;
    int gr = 0;

    for(int t: v){
        if(t<kl) kl=t;
        else if(t>gr) gr=t;
    }

    vector<int> freq(gr-kl+1);
    for(int t:v){
        freq[t]++;
    }

    for(int i=1;i<freq.size();i++){
        freq[i]+=freq[i-1];
    }

    vector<int> tmp(v.size());
    for(int i=0;i<v.size();i++){
        tmp[freq[v[i]]]=v[i];
        freq[v[i]] -= 1;
    }
    v = move(tmp);
}

#endif 