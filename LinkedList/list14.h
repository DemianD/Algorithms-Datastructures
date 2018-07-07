//C++14 compatible singly linked list
#ifndef __List14_H
#define __List14_H
//
#define DEBUG
//
//#define ITERATOR

#include <iostream>
#include <memory>
#include <algorithm>
using std::endl;
using std::ostream;

template <class T>
class ListNode;
template <class T>
class List;

template <class T>
using ListNodeptr = std::unique_ptr<ListNode<T>>;

template <class T>
ostream &operator<<(ostream &os, const List<T> &l);

template <class T>
void swap(List<T> &&a, List<T> &&b);

template <class T>
class List : private ListNodeptr<T>
{
    // Constructors, default, copy & move
  public:
    List(){};

  public:
    List(const List<T> &);

  public:
    List(List<T> &&);

    // Taking unique_ptr's constructors
    using ListNodeptr<T>::ListNodeptr;

    // Operations
  public:
    // Duplicates are allowed
    void add(const T &);

  public:
    // Number of times the supplied key is found in the list
    int getTimesFound(const T &) const;

  public:
    // List size
    int size() const;

  public:
    // Only removes the first occurrence of the argument
    void remove(const T &);

  public:
    // Removes the first node
    void removeFirst();

  public:
    void insertionsort();

    // zoek geeft een pointer naar de List die de sleutelwaarde bevat,
    // en geeft een pointer naar de lege List op het einde als de sleutel niet
    // voorkomt.

  protected:
    // Search returns a pointer to a list, containing the key (argument)
    // or a pointer to an empty list if the key isn't found
    const List *search(const T &) const;

  protected:
    // Search returns a pointer to a list, containing the key (argument)
    // or a pointer to an empty list if the key isn't found
    List *search(const T &);

  protected:
    // searchInSorted assumes a sorted list and returns a list where the key should be
    List<T> *searchInSorted(const T &sl);

  public:
  // Copy assignment operator
    List<T> &operator=(const List<T> &);

  public:
  // Move assignment operator
    List<T> &operator=(List<T> &&) = default;

  public:
  // Move assignment operator when the right-hand operand is a ListNodeptr<T> instead of a List<T>
    List<T> &operator=(ListNodeptr<T> &&);

    // Output operator overwrite
    friend ostream &operator<<<>(ostream &os, const List &l);
    // Swap operation
    friend void swap<>(List<T> &&, List<T> &&);

  public:
    void output(ostream &os) const;
    
  public:
    class iterator
    {
      public:
        iterator(ListNode<T> *l = 0);
        const T &operator*() const;
        const iterator &operator++();
        bool operator!=(const iterator &i);
    };
    iterator begin() const;
    iterator end() const;
};

// Implementation of the constructors / operators
template <class T>
List<T>::List(const List<T> &l)
{
    std::cerr << "\tcalled List<T> copy constructor\n";
    if (this != &l)
    {
        ListNode<T> *tmp = l.get();
        while (tmp != nullptr)
        {
            voegToe(tmp->sl);
            tmp = tmp->volgend.get();
        }
    }
    else
        std::cerr << "\t you tried to copy construct yourself, won't do the copy\n";
}

template <class T>
List<T>::List(List<T> &&l)
{
    std::cerr << "\tcalled List<T> move constructor\n";
    (*this).operator=(std::move(l));
}

template <class T>
List<T> &List<T>::operator=(const List<T> &l)
{
    std::cerr << "\tcalled List<T> copy operator\n";
    if (this != &l)
    {
        this->reset(nullptr);
        ListNode<T> *tmp = l.get();
        while (tmp != nullptr)
        {
            voegToe(tmp->sl);
            tmp = tmp->volgend.get();
        }
    }
    else
        std::cerr << "\t you tried to copy operator on yourself, won't do the copy\n";
    return *this;
}

//template<class T>
//List<T>& List<T>::operator=(List<T>&& l){
//	std::cerr<<"\tcalled List<T> move operator for List<T> rvalue ref\n";
//	//(*this).ListNodeptr<T>::operator=(std::move(l));
//	return *this;
//}

template <class T>
List<T> &List<T>::operator=(ListNodeptr<T> &&l)
{
    std::cerr << "\tcalled List<T> move operator for ListNodeptr<T> rvalue ref\n";
    (*this).ListNodeptr<T>::operator=(std::move(l));
    return *this;
}

template <class T>
void List<T>::voegToe(const T &sl)
{
    ListNodeptr<T> nieuw(new ListNode<T>(sl));
    ListNodeptr<T>::swap(nieuw->volgend);
    *this = std::move(nieuw);
}

template <class T>
void swap(List<T> &a, List<T> &b)
{
    std::cerr << "a before: ";
    a.schrijf(std::cerr);
    std::cerr << "\nb before: ";
    b.schrijf(std::cerr);
    std::cerr << "\n";

    List<T> tmp;
    tmp = std::move(b);
    b = std::move(a);
    a = std::move(tmp);

    std::cerr << "a after: ";
    a.schrijf(std::cerr);
    std::cerr << "\nb after: ";
    b.schrijf(std::cerr);
    std::cerr << "\n";
}

template <class T>
class ListNode
{
    friend class List<T>;

  public:
    List<T> volgend;
    ListNode(const T &);
    ~ListNode();

  protected:
    T sl;
#ifdef DEBUG
  public:
    static bool controle(int gemaakt, int verwijderd);

  protected:
    static int aantalGemaakt;
    static int aantalVerwijderd;
#endif
};

template <class T>
int ListNode<T>::aantalGemaakt = 0;
template <class T>
int ListNode<T>::aantalVerwijderd = 0;

template <class T>
ListNode<T>::ListNode(const T &_sl) : sl(_sl)
{
    std::cerr << "Knoop met sleutel " << sl << " wordt gemaakt\n";
    aantalGemaakt++;
}

template <class T>
ListNode<T>::~ListNode()
{
    std::cerr << "Knoop met sleutel " << sl << " wordt verwijderd\n";
    aantalVerwijderd++;
}
#ifdef DEBUG
template <class T>
bool ListNode<T>::controle(int gemaakt, int verwijderd)
{
    if (aantalGemaakt == gemaakt && aantalVerwijderd == verwijderd)
        return true;
    else
    {
        std::cerr << "Fout bij controle:\n";
        std::cerr << "Aantal gemaakte knopen   : " << aantalGemaakt << " (moet zijn: " << gemaakt << ")\n";
        std::cerr << "Aantal verwijderde knopen: " << aantalVerwijderd << " (moet zijn: " << verwijderd << ")\n";
        throw "Mislukte controle";
    };
};
#endif

template <class T>
ostream &operator<<(ostream &os, const List<T> &l)
{
#ifdef ITERATOR
    for (auto &&sleutel : l)
        os << sleutel << ", ";
#else
    if (l.get())
    {
        os << l.get()->sl << ", ";
        os << l.get()->volgend;
    }
#endif
    return os;
}

template <class T>
void List<T>::schrijf(ostream &os) const
{
#ifdef ITERATOR
    if (this->get() != 0)
    {
        os << this->get()->sl;
        std::for_each(++begin(), end(), [&](const T &sl) { os << " . " << sl; });
    }
#else
    {
        ListNode<T> *kn = this->get();
        if (kn != 0)
        {
            os << kn->sl;
            kn = kn->volgend.get();
        };
        while (kn != 0)
        {
            os << " . " << kn->sl;
            kn = kn->volgend.get();
        };
    }
#endif
}
//oplossing:

template <class T>
const List<T> *List<T>::zoek(const T &sl) const
{
    const List<T> *pl = this;
    while (*pl && pl->get()->sl != sl)
        pl = &(pl->get()->volgend);
    return pl;
}
template <class T>
int List<T>::geefaantal(const T &sl) const
{
    const List<T> *plaats = zoek(sl);
    //noot: plaats==0 is false zelfs als plaats een nulpointer is
    if (*plaats)
        return 1 + plaats->get()->volgend.geefaantal(sl);
    else
        return 0;
};

template <class T>
int List<T>::geefaantal() const
{
    if (*this)
        return 1 + this->get()->volgend.geefaantal();
    else
        return 0;
};

template <class T>
List<T> *List<T>::zoek(const T &sl)
{
    List *pl = this;
    while (*pl && pl->get()->sl != sl)
        pl = &(pl->get()->volgend);
    return pl;
}

template <class T>
void List<T>::verwijderEerste()
{
    if (this->get() != 0)
    {
        ListNodeptr<T> staart(std::move(this->get()->volgend));
        this->reset();
        ListNodeptr<T>::swap(staart);
    }
}

template <class T>
void List<T>::verwijder(const T &sl)
{
    zoek(sl)->verwijderEerste();
}

template <class T>
List<T> *List<T>::zoekGesorteerd(const T &sl)
{
    List *plaats = this;
    while (*plaats && plaats->get()->sl < sl)
        plaats = &plaats->get()->volgend;
    return plaats;
};

template <class T>
void List<T>::insertionsort()
{
    ListNodeptr<T> ongesorteerd = std::move(*this);
    while (ongesorteerd)
    {
        List *plaats = zoekGesorteerd(ongesorteerd.get()->sl);
        ListNodeptr<T> dummy = std::move(ongesorteerd);
        //vermits ongesorteerd een nullpointer is, is het equivalent van volgende lijnen ongeveer
        //ongesorteerd=std::move(dummy.get()->volgend);
        //std::swap(*plaats,dummy.get()->volgend);
        std::swap(ongesorteerd, dummy.get()->volgend);
        dummy.get()->volgend = std::move(*plaats);
        *plaats = std::move(dummy);
    };
};
#endif
