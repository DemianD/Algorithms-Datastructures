#ifndef __SORTVECTOR_HPP
#define __SORTVECTOR_HPP
/**
 \class sortvector
 \brief is een klasse van sorteerbare vectoren
 Bovenop de vectoreigenschappen zijn er hulpfuncties om sorteervergelijkingen
 te vergemakkelijken.
*/
#include <iostream>
   using std::istream;
   using std::ostream;
   using std::move;
   using std::swap;
   using std::cout;
   using std::endl;
#include <iomanip>   // voor setw
   using std::setw;
#include <cstdlib>   // voor rand - opletten!! 
#include <vector>
    using std::vector;
#include <map>
    using std::map;

template<class T>
class Sortvector:public vector<T>{
  public:

    /// \fn Constructor: het argument geeft de grootte aan
    /// bij constructie zal de tabel opgevuld worden met
    /// n verschillende Ts in random volgorde
    /// (zie hulplidfuncties)
    Sortvector(int);
    using vector<T>::vector;
    /// \fn Constructor inheritance van vector is vereist om in de implementatie
    /// Sortvector(int grootte): vector<T>(grootte) te mogen schrijven

    Sortvector(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(Sortvector<T>&& v) = delete;
    Sortvector(Sortvector<T>&& v) = delete;

    /// \fn vul_range vul vector met de waarden T(0)...T(size()-1) in volgorde
    void vul_range();
    void draai_om();
    void vul_omgekeerd();
    /// \fn Knuth-Fisher-Yates zie impl voor algo
    void shuffle();


    void vul_random_zonder_dubbels();
    void vul_random(); //< nog niet implementeren

    bool is_gesorteerd() const;
    /// \fn is_range controleert of *this eruit ziet als het resultaat van vul_range(), d.w.z.
    /// dat, voor alle i, (*this)[i]==T(i);
    bool is_range() const;

    friend ostream& operator<<(ostream& os, const Sortvector<T>& s){
        s.schrijf(os);
        return os;
    }

  private: 
    void schrijf(ostream & os)const;
};

template <class T>
Sortvector<T>::Sortvector(int grootte): vector<T>(grootte) {
vul_range();
}

template <class T>
void Sortvector<T>::vul_range() {
    for(int i=0;i< this->size();i++){
        this->at(i)=T(i);
        //this->operator[](i)=i; // werkt ook
    }
}

template <class T>
void Sortvector<T>::draai_om() {
    for(int i=0;i<this->size()/2;i++){
        swap(this->at(i),this->at(this->size()-1-i));
    }
}

template <class T>
void Sortvector<T>::vul_omgekeerd() {
    for(int i=this->size() -1; i>= 0; i--){
        this->at(i)=T(i);
    }
}

template <class T>
void Sortvector<T>::shuffle() {
    /// \fn -- To shuffle an array a of n elements (indices 0..n-1):
    /// for i from n−1 downto 1 do
    ///     j ← random integer such that 0 ≤ j ≤ i
    ///     exchange a[j] and a[i]
    int j;
    for(int i=this->size()-1; i>=1; i--){
        j=rand()%i;
        swap(this->at(i),this->at(j));
    }

}

template <class T>
void Sortvector<T>::vul_random() {
   for(int i=0; i<this->size();i++){
       this->at(i)=T(rand());
   }
}


template <class T>
void Sortvector<T>::vul_random_zonder_dubbels() {
    map<int,bool> present;
    int tmp;
    for(int i=0;i<this->size();i++){
        tmp = rand()%this->size();
        while(present.find(tmp) != present.end()){
            tmp=rand()%this->size();
        }
        this->at(i)=T(tmp);
        present[tmp]=true;
    }
}

template <class T>
bool Sortvector<T>::is_gesorteerd() const {
    bool is_gesorteerd = true;
    for(int i=0;is_gesorteerd && i<this->size()-1;i++){
        if((*this)[i] > (*this)[i+1]) is_gesorteerd=false;
    }
    return is_gesorteerd;
}

template <class T>
bool Sortvector<T>::is_range() const {
    bool is_range=true;
    for(int i=0;is_range&&i<this->size();i++){
        if((*this)[i]!=T(i)) is_range=false;
    }
    return is_range;
}


template <class T>
void Sortvector<T>::schrijf(ostream & os)const{
    for(auto&& t : *this){
        os<<t<<" ";
    }
    os<<"\n";
}
#endif