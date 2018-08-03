#ifndef __RBTREE_HPP
#define __RBTREE_HPP

#define CONSTRUCTION_LOGGING

#include "rbnode.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include <algorithm>
#include <functional>
#include <memory>
using std::make_unique;
using std::unique_ptr;
#include <sstream>
#include <stack>
#include <tuple>

template <class Key, class Data>
class RBnode;

template <class Key, class Data>
using RBnodeptr = unique_ptr<RBnode<Key, Data>>;

template <class Key, class Data>
class RBtree : public RBnodeptr
{
  public:
    RBtree() : RBnodeptr{nullptr} { cout << "RBtree()\n"; };
    RBtree(const Key &_k, const Data &_d, const Color &_c) : RBnodeptr{make_unique<RBnode<Key, Data>>(_k, _d, _c)} { cout << "RBtree(Key&,Data&,Color&)\n"; };
    virtual ~RBtree() = default;

    RBtree(const RBtree<Key, Data> &other) : RBnodeptr{nullptr}
    {
        if (other)
        {
            this->reset(*other)
        }
    };
    RBtree &operator=(const RBtree<Key, Data> &other)
    {
        RBtree<Key, Data> temp{other};
        temp.swap(*this);
        return *this;
    };

    RBtree(RBtree<Key, Data> &&other) : RBnodeptr{move(other)} {};
    RBtree &operator=(RBtree<Key, Data> &&other)
    {
        this->swap(other);
        return *this;
    };

    int depth() const;
    void rotate(bool);
    void add_bottom_up(const Key&, const Data&);
    void add_top_down(const Key&, const Data&);
    bool repOK() const;
    Color getColor() const;

    void inorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void preorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void postorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void output(ostream &os) const;
    void pretty_print(int indent = 0) const;
};

template <class Key, class Data>
int RBtree<Key,Data>::depth() const {
    if(!*this){
        return 0;
    }
    return (std::max((*this)->left.depth(),(*this)->right.depth())+1);
}



template <class Key, class Data>
void RBtree<Key, Data>::inorder(std::function<void(const RBnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        (*this)->left.inorder(visit);
        visit(**this);
        (*this)->right.inorder(visit);
    };
}

template <class Key, class Data>
void RBtree<Key, Data>::preorder(std::function<void(const RBnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        visit(**this);
        (*this)->left.preorder(visit);
        (*this)->right.preorder(visit);
    }
}

template <class Key, class Data>
void RBtree<Key, Data>::postorder(std::function<void(const RBnode<Key, Data> &)> visit) const
{
    if (*this)
    {
        (*this)->left.postorder(visit);
        (*this)->right.postorder(visit);
        visit(**this);
    }
}

template <class Key, class Data>
void RBtree<Key, Data>::output(ostream &os) const
{
    inorder([&os](const RBnode<Key, Data> &node) {
        os << "(" << node.key << " -> " << node.data << ")";
        os << "\n  Left child: ";
        if (node.left)
            os << node.left->key;
        else
            os << "-----";
        os << "\n  Right child: ";
        if (node.right)
            os << node.right->key;
        else
            os << "-----";
        os << "\n";
    });
}

template <class Key, class Data>
void RBtree<Key, Data>::pretty_print(int indent) const
{
    if (*this)
    {
        if ((*this)->right)
            (*this)->right.pretty_print(indent + 4);

        if (indent)
        {
            cout << std::setw(indent) << ' ';
        }
        cout << (*this)->key << ',' << (*this)->data << '\n';

        if ((*this)->left)
            (*this)->left.pretty_print(indent + 4);
    }
}

#endif