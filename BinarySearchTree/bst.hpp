#ifndef __BST_HPP
#define __BST_HPP

#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
#include <cassert>
#include <stack>
using std::stack;
#include <queue>
using std::queue;
#include <functional>
using std::function;
#include <memory>
using std::unique_ptr;
#include <utility>
using std::move;
using std::pair;

template <class T>
class BST;

template <class T>
class BSTnode;

template <class T>
using BSTnodeptr = unique_ptr<BSTnode<T>>;

enum class Order
{
    Pre,
    In,
    Post
};

template <class T>
class BST : private BSTnodeptr<T>
{
    using BSTnodeptr<T>::BSTnodeptr;

  public:
    BST<T>() { cout << "BST<T>()" << endl; };
    ~BST<T>() { cout << "~BST<T>()" << endl; }
    BST<T>(const BST<T> &) = default;
    BST<T>(BST<T> &&) = default;
    BST<T> &operator=(const BST<T> &) = default;
    BST<T> &operator=(BST<T> &&) = default;

    BST<T>(const T &_item) : BSTnodeptr<T>(new BSTnode<T>(_item)) { cout << "BST<T>(const&)" << endl; };
    BST<T>(T &&_item) : BSTnodeptr<T>(new BSTnode<T>(move(_item))) { cout << "BST<T>(&&)" << endl; };

    BST<T> &operator=(BSTnodeptr<T> &&_other)
    {
        this->BSTnodeptr<T>::operator=(move(_other));
        return *this;
    }

    void DFS(function<void(T &&)> preorderfct, function<void(T &&)> inorderfct, function<void(T &&)> postorderfct)
    {
        if (*this)
        {
            stack<pair<BSTnode<T> *, int>> ATW;
            ATW.emplace((*this).get(), 1);
            while (!ATW.empty())
            {
                BSTnode<T> *current = ATW.top().first();
                int pass = ATW.top().second;
                ATW.top().second++;
                switch (pass)
                {
                case 1:
                    preorderfct(move(current->item));
                    if (current->left)
                        ATW.emplace(current->left.get(), 1);
                    break;
                case 2:
                    inorderfct(move(current->item));
                    if (current->right)
                        ATW.emplace(current->right.get(), 1);
                    break;
                case 3:
                    postorderfct(move(current->item));
                    ATW.pop();
                }
            }
        }
    };
    void DFS(function<void(T &&)> orderfct, Order ord)
    {
        if (*this)
        {
            stack<pair<BSTnode<T> *, int>> ATW;
            ATW.emplace(this->get(), 1);
            while (!ATW.empty())
            {
                BSTnode<T> *current = ATW.top().first;
                int pass = ATW.top().second;
                ATW.top().second++;
                switch (pass)
                {
                case 1:
                    if (ord == Order::Pre)
                        orderfct(move(current->item));
                    if (current->left)
                        ATW.emplace(current->left.get(), 1);
                    break;
                case 2:
                    if (ord == Order::In)
                        orderfct(move(current->item));
                    if (current->right)
                        ATW.emplace(current->right.get(), 1);
                    break;
                case 3:
                    if (ord == Order::Post)
                        orderfct(move(current->item));
                    ATW.pop();
                    break;
                }
            }
        }
    };
    void BFS(function<void(T &&)> fct)
    {
        if (*this)
        {
            queue<BSTnode<T> *> ATW;
            ATW.emplace(this->get());
            while (!ATW.empty())
            {
                BSTnode<T> *current = ATW.front();
                fct(move(current->item));
                if (current->left)
                    ATW.emplace(current->left.get());
                if (current->right)
                    ATW.emplace(current->right.get());
                ATW.pop();
            }
        }
    };

    friend istream &operator>>(istream &is, BST<T> &bst)
    {
        return bst.read_from_file(is);
    }
    friend ostream &operator<<(ostream &os, const BST<T> &bst)
    {
        //return bb.output_to_stream_bfs(os);
        return bst.output_to_stream(os);
    }
    void add(const T &);
    void add(T &&);

    void remove(const T &);
    void remove(T &&);

    void test()
    {
        cout << "called test" << endl;
        cout << this->get()->item << endl;
    }

    void testvec()
    {
        cout << "called testvec" << endl;
        for (const auto &x : this->get()->item)
        {
            cout << x << ", ";
        }
        cout << endl;
    }

    BST<T> *find(const T &key)
    {
        const BST<T> *bst = this;

        if (key == bst->get()->item)
            return bst;
        else if (key < bst->get()->item)
            return bst->get()->left.find(key);
        else if (key > bst->get()->item)
            return bst->get()->right.find(key);
    }

    int aantalSleutels() const
    {
        if (!*this)
        {
            return 0;
        }
        else
        {
            return this->get()->left.aantalSleutels() + this->get()->right.aantalSleutels() + 1;
        }
    }

    ostream &output_to_stream(ostream &);
    istream &read_from_file(istream &);
    ostream &output_to_stream_bfs(ostream &os) const;

  private:
};

template <class T>
class BSTnode
{
    friend class BST<T>;

  public:
    BSTnode() { cout << "BSTnode()" << endl; };
    ~BSTnode() { cout << "~BSTnode()" << endl; }
    explicit BSTnode(const T &_item) : item(_item){};
    explicit BSTnode(T &&_item) : item(move(_item)){};
    explicit BSTnode(const BSTnode<T> &_other) : item(_other.item), left(_other.left), right(_other.right){};
    explicit BSTnode(BSTnode<T> &&_other) : item(move(_other.item)), left(move(_other.left)), right(move(_other.right)){};
    BSTnode<T> &operator=(const BSTnode<T> &_other)
    {
        this->item = _other.item;
        this->left = _other.left;
        this->right = _other.right;
        return *this;
    };
    BSTnode<T> &operator=(BSTnode<T> &&_other)
    {
        this->item = move(_other.item);
        this->left = move(_other.left);
        this->right = move(_other.right);
        return *this;
    };

    friend ostream &operator<<(ostream &os, const BSTnode<T> &_node)
    {
        os << _node.item;
        //os << "\t Left child: " << *(_node.left.get()) << endl;
        //os << "\t Right child: " << *(_node.right.get()) << endl;
        return os;
    };

  private:
    T item;
    BST<T> left, right;
};

#endif
