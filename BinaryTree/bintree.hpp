#ifndef __BINTREE_H
#define __BINTREE_H

#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::ostream;
#include <cassert>
#include <stack>
using std::stack;
#include <functional>
using std::function;
#include <memory>
#include <queue>
using std::queue;
#include <sstream>
using std::stringstream;
#include <string>
#include <map>
#include <vector>
using std::vector;
#include <utility>
using std::pair;
#include <string>
using std::stoi;
using std::string;

template <class T>
class BinTree;

template <class T>
class BinTreeNode;

template <class T>
using BinTreeNodeptr = std::unique_ptr<BinTreeNode<T>>;

enum class Order
{
    Pre,
    In,
    Post
};

#pragma region BinTree class definition
template <class T>
class BinTree : private BinTreeNodeptr<T>
{
    using BinTreeNodeptr<T>::BinTreeNodeptr;

  public:
    int size() const;
    istream &read(istream &);
    ostream &output_to_file(ostream &) const;
    ostream &output_to_file_bfs(ostream &) const;
    void DFS(function<void(T &&)>, function<void(T &&)>, function<void(T &&)>);
    void DFS(function<void(T &&)>, enum Order);
    void BFS(function<void(T &&)>);
    friend istream &operator>>(istream &is, BinTree<T> &bt)
    {
        return bt.read(is);
    }
    friend ostream &operator<<(ostream &os, const BinTree<T> &bt)
    {
        return bt.output_to_file(os);
        //return bb.output_to_file_bfs(os);
    }
};
#pragma endregion BinTree class definition

#pragma region BinTreeNode class definition
template <class T>
class BinTreeNode
{
  public:
    BinTreeNode(T _item) : item(_item) {}

  private:
    T item;
    BinTree<T> left, right;
    friend class BinTree<T>;
};
#pragma endregion BinTreeNode class definition

template <class T>
int BinTree<T>::size() const
{
    if (!*this)
        return 0;
    else
        return (*this)->left.size() + (*this)->right.size() + 1;
}

template <class T>
istream &BinTree<T>::read(istream &is)
{
    string line;
    getline(is, line);
    int number_of_nodes = stoi(line);
    vector<BinTree<T> *> knopen(number_of_nodes);
    vector<pair<int, int>> kinderen(number_of_nodes);
    vector<bool> no_root(number_of_nodes);
    for (int i = 0; i < number_of_nodes; i++)
    {
        T value;
        int l, r;
        getline(is, line);
        stringstream ss(line);                      // je kan met stringstream tokens inlezen op voorwaarde dat je zeker bent welk type wanneer komt
        ss >> value >> l >> r;                      // hier weeet je zeker dat je value van T type is, in ons vb gaat dat een string zijn, gevolgd door 2 ints l en r
        knopen[i] = new BinTree<T>();               // zet lege binbomen klaar voor elke knoop, BinTree<T>* omwille van new
        BinTree<T> temp(new BinTreeNode<T>(value)); // gebruikt geërfde constructor om een binknoop met value aan te maken, CLion kent constr inheritance niet, dus markeert dit als fout
        knopen[i]->swap(temp);                      // knopen op i wordt de net geconstrueerde knoop
        kinderen[i] = {l, r};                       // gebruik initializer list om het pair in te vullen
        // terwijl je overloopt, als je knopen tegenkomt die kinderen hebben ( dwz r of l != -1) dan kunnen die kinderen in geen geval de root knoop zijn -> no_root[r of l] = true;
        if (l != -1)
        {
            no_root[l] = true;
        }
        if (r != -1)
        {
            no_root[r] = true;
        }
    }

    int root; //nadat we alle knopen hebben ingelezen gaan we op zoek naar wie wel de root is, er is maar 1 element in de no_root tabel die false heeft als waarde. De knoop op die index is de root
    for (int i = 0; i < number_of_nodes; i++)
    {
        if (!no_root[i])
        {
            root = i;
        }
    }

    // we gaan de boom bouwen, details over dit proces in afbeelding op github
    for (int i = 0; i < number_of_nodes; i++)
    {
        if (kinderen[i].first != -1)
        {
            knopen[i]->get()->left.swap(*knopen[kinderen[i].first]); // L-kind verplaatsen naar de knoop zodat het een echt linkerkind wordt
            knopen[kinderen[i].first] = &(knopen[i]->get()->left);   // pointer aanpassen
        }
        if (kinderen[i].second != -1)
        {
            knopen[i]->get()->right.swap(*knopen[kinderen[i].second]);
            knopen[kinderen[i].second] = &(knopen[i]->get()->right);
        }
    }
    this->swap(*knopen[root]);
    return is;
}

template <class T>
ostream &BinTree<T>::output_to_file(ostream &os) const
{
    if ((*this))
    {
        return this->output_to_file_bfs(os);
    }
    return os;
}

template <class T>
ostream &BinTree<T>::output_to_file_bfs(ostream &os) const
{
    if ((*this))
    {
        os << size() << endl;
        queue<BinTreeNode<T> *> ATW; // FIFO: een lijst met BinTreeNode<T>* elementen
        ATW.push(this->get());       // je moet van de huidige boom de inhoud van de knoop op
        int kindnr = 1;
        BinTreeNode<T> *current = ATW.front();
        while (current != 0)
        {
            os << current->item << ' ';
            if (!current->left)
                os << "-1 ";
            else
            {
                os << kindnr++ << ' ';
                ATW.push(current->left.get());
            }
            if (!current->right)
                os << "-1\n";
            else
            {
                os << kindnr++ << '\n';
                ATW.push(current->right.get());
            }
            ATW.pop();
            if (ATW.front() != 0)
                current = ATW.front();
            else
                current = 0;
        }
    }
    return os;
}

template <class T>
void BinTree<T>::DFS(function<void(T &&)> preorder, function<void(T &&)> inorder, function<void(T &&)> postorder)
{
    stack<pair<BinTreeNode<T> *, int>> ATW;
    if ((*this) != 0)
    {
        ATW.emplace((*this).get(), 1);
        while (!ATW.empty())
        {
            BinTreeNode<T> *current = ATW.top().first;
            int pass = ATW.top().second;
            ATW.top().second++;
            switch (pass)
            {
            case 1:
                preorder(move(current->item));
                if (current->left)
                    ATW.emplace(current->left.get(), 1);
                break;
            case 2:
                inorder(move(current->item));
                if (current->right)
                    ATW.emplace(current->right.get(), 1);
                break;
            case 3:
                postorder(move(current->item));
                ATW.pop();
            }
        }
    }
}

template <typename T>
void BinTree<T>::DFS(function<void(T &&)> orderfct, Order ord)
{
    stack<pair<BinTreeNode<T> *, int>> ATW;
    if ((*this) != 0)
    {
        ATW.emplace(this->get(), 1);
        while (!ATW.empty())
        {
            BinTreeNode<T> *current = ATW.top().first;
            int pass = ATW.top().second;
            ATW.top().second++;
            switch (pass)
            {
            case 1:
                if (ord == Order::Pre)
                {
                    orderfct(move(current->item));
                }
                if (current->left)
                {
                    ATW.emplace(current->left.get(), 1);
                }
                break;
            case 2:
                if (ord == Order::In)
                {
                    orderfct(move(current->item));
                }
                if (current->right)
                {
                    ATW.emplace(current->right.get(), 1);
                }
                break;
            case 3:
                if (ord == Order::Post)
                {
                    orderfct(move(current->item));
                }
                ATW.pop();
            }
        }
    }
}

template <typename T>
void BinTree<T>::BFS(function<void(T &&)> fct)
{
    if (*this)
    {
        queue<BinTreeNode<T> *> ATW;
        ATW.emplace(this->get());
        while (!ATW.empty())
        {
            BinTreeNode<T> *current = ATW.front();
            fct(move(current->item));
            if (current->left)
            {
                ATW.emplace(current->left.get());
            }
            if (current->right)
            {
                ATW.emplace(current->right.get());
            }
            ATW.pop();
        }
    }
}

#endif