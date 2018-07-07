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

    // search geeft een pointer naar de List die de itemeutelwaarde bevat,
    // en geeft een pointer naar de lege List op het einde als de itemeutel niet
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
    List<T> *searchInSorted(const T &item);

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
            add(tmp->item);
            tmp = tmp->next.get();
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
            add(tmp->item);
            tmp = tmp->next.get();
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
void List<T>::add(const T &item)
{
    ListNodeptr<T> nieuw(new ListNode<T>(item));
    ListNodeptr<T>::swap(nieuw->next);
    *this = std::move(nieuw);
}

template <class T>
void swap(List<T> &a, List<T> &b)
{
    std::cerr << "a before: ";
    a.output(std::cerr);
    std::cerr << "\nb before: ";
    b.output(std::cerr);
    std::cerr << "\n";

    List<T> tmp;
    tmp = std::move(b);
    b = std::move(a);
    a = std::move(tmp);

    std::cerr << "a after: ";
    a.output(std::cerr);
    std::cerr << "\nb after: ";
    b.output(std::cerr);
    std::cerr << "\n";
}

template <class T>
class ListNode
{
    friend class List<T>;

  public:
    List<T> next;
    ListNode(const T &);
    ~ListNode();

  protected:
    T item;
#ifdef DEBUG
  public:
    static bool control(int gemaakt, int removed);

  protected:
    static int numberMade;
    static int numberRemoved;
#endif
};

template <class T>
int ListNode<T>::numberMade = 0;
template <class T>
int ListNode<T>::numberRemoved = 0;

template <class T>
ListNode<T>::ListNode(const T &_item) : item(_item)
{
    std::cerr << "Knoop met itemeutel " << item << " wordt gemaakt\n";
    numberMade++;
}

template <class T>
ListNode<T>::~ListNode()
{
    std::cerr << "Knoop met itemeutel " << item << " wordt removed\n";
    numberRemoved++;
}
#ifdef DEBUG
template <class T>
bool ListNode<T>::control(int gemaakt, int removed)
{
    if (numberMade == gemaakt && numberRemoved == removed)
        return true;
    else
    {
        std::cerr << "Fout bij control:\n";
        std::cerr << "Aantal gemaakte knopen   : " << numberMade << " (moet zijn: " << gemaakt << ")\n";
        std::cerr << "Aantal removede knopen: " << numberRemoved << " (moet zijn: " << removed << ")\n";
        throw "Miitemukte control";
    };
};
#endif

template <class T>
ostream &operator<<(ostream &os, const List<T> &l)
{
#ifdef ITERATOR
    for (auto &&itemeutel : l)
        os << itemeutel << ", ";
#else
    if (l.get())
    {
        os << l.get()->item << ", ";
        os << l.get()->next;
    }
#endif
    return os;
}

template <class T>
void List<T>::output(ostream &os) const
{
#ifdef ITERATOR
    if (this->get() != 0)
    {
        os << this->get()->item;
        std::for_each(++begin(), end(), [&](const T &item) { os << " . " << item; });
    }
#else
    {
        ListNode<T> *kn = this->get();
        if (kn != 0)
        {
            os << kn->item;
            kn = kn->next.get();
        };
        while (kn != 0)
        {
            os << " . " << kn->item;
            kn = kn->next.get();
        };
    }
#endif
}
//oplossing:

template <class T>
const List<T> *List<T>::search(const T &item) const
{
    const List<T> *pl = this;
    while (*pl && pl->get()->item != item)
        pl = &(pl->get()->next);
    return pl;
}
template <class T>
int List<T>::getTimesFound(const T &item) const
{
    const List<T> *plaats = search(item);
    //noot: plaats==0 is false zelfs als plaats een nulpointer is
    if (*plaats)
        return 1 + plaats->get()->next.size(item);
    else
        return 0;
};

template <class T>
int List<T>::size() const
{
    if (*this)
        return 1 + this->get()->next.size();
    else
        return 0;
};

template <class T>
List<T> *List<T>::search(const T &item)
{
    List *pl = this;
    while (*pl && pl->get()->item != item)
        pl = &(pl->get()->next);
    return pl;
}

template <class T>
void List<T>::removeFirst()
{
    if (this->get() != 0)
    {
        ListNodeptr<T> staart(std::move(this->get()->next));
        this->reset();
        ListNodeptr<T>::swap(staart);
    }
}

template <class T>
void List<T>::remove(const T &item)
{
    search(item)->removeFirst();
}

template <class T>
List<T> *List<T>::searchInSorted(const T &item)
{
    List *plaats = this;
    while (*plaats && plaats->get()->item < item)
        plaats = &plaats->get()->next;
    return plaats;
};

template <class T>
void List<T>::insertionsort()
{
    ListNodeptr<T> unsorted = std::move(*this);
    while (unsorted)
    {
        List *plaats = searchInSorted(unsorted.get()->item);
        ListNodeptr<T> dummy = std::move(unsorted);
        //vermits unsorted een nullpointer is, is het equivalent van de volgende lijnen ongeveer
        //unsorted=std::move(dummy.get()->next);
        //std::swap(*plaats,dummy.get()->next);
        std::swap(unsorted, dummy.get()->next);
        dummy.get()->next = std::move(*plaats);
        *plaats = std::move(dummy);
    };
};
#endif
