#ifndef __RBTREE_HPP
#define __RBTREE_HPP

#define CONSTRUCTION_LOGGING 0

#include "rbnode.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include <iomanip>
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
class RBtree : public RBnodeptr<Key, Data>
{
  public:
    RBtree() : RBnodeptr<Key, Data>{nullptr}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "RBtree()\n";
    };
    RBtree(const Key &_k, const Data &_d, const Color &_c) : RBnodeptr<Key, Data>{make_unique<RBnode<Key, Data>>(_k, _d, _c)}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "RBtree(Key&,Data&,Color&)\n";
    };
    virtual ~RBtree() = default;

    RBtree(const RBtree<Key, Data> &other) //: RBnodeptr<Key, Data>{nullptr}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "RBtree(const RBtree&)\n";

        if (other)
        {
            this->reset(new RBnode<Key, Data>(*other));
        }
    };
    RBtree &operator=(const RBtree<Key, Data> &other)
    {
        if (CONSTRUCTION_LOGGING)
            cout << "operator=(const RBtree&)\n";

        RBtree<Key, Data> temp{other};
        temp.swap(*this);
        return *this;
    };

    RBtree(RBtree<Key, Data> &&other) : RBnodeptr<Key, Data>{move(other)}
    {
        if (CONSTRUCTION_LOGGING)
            cout << "RBtree(RBtree&&)\n";
    };

    RBtree &operator=(RBtree<Key, Data> &&other)
    {
        if (CONSTRUCTION_LOGGING)
            cout << "operator=(RBtree&&)\n";

        this->swap(other);
        return *this;
    };

    int depth() const;
    void rotate(bool);
    void insert_bottom_up(const Key &, const Data &);
    void insert_top_down(const Key &, const Data &);
    void remove_bottom_up(const Key &);
    void remove_top_down(const Key &);
    bool repOK() const;
    Color getColor() const;

    void inorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void preorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void postorder(std::function<void(const RBnode<Key, Data> &)> visit) const;
    void output(ostream &os) const;
    void pretty_print(int indent = 0) const;

  protected:
    std::tuple<RBtree<Key, Data> *, RBnode<Key, Data> *> search(const Key &);
    std::tuple < RBtree<Key, Data> *, RBtree<Key, Data> *, RBtree<Key, Data> *>get_family_pointers(const RBtree<Key, Data> * const);
    int black_depth(bool &) const;
};

template <class Key, class Data>
std::tuple<RBtree<Key, Data> *, RBnode<Key, Data> *> RBtree<Key, Data>::search(const Key &key)
{
    RBtree<Key, Data> *location = this;
    RBnode<Key, Data> *parent = nullptr;

    while (*location && (*location)->key != key)
    {
        parent = location->get();
        if (key > (*location)->key)
        {
            location = &(*location)->right;
        }
        else
        {
            location = &(*location)->left;
        }
    }
    return std::tuple(location, parent);
}

template <class Key, class Data>
int RBtree<Key, Data>::depth() const
{
    if (!*this)
    {
        return -1;
    }
    return std::max((*this)->left.depth(), (*this)->right.depth()) + 1;
}

template <class Key, class Data>
void RBtree<Key,Data>::insert_bottom_up(const Key &key, const Data &data)
{
    auto [location, parent] = search(key);
    if(*location){
        return;
    }
    *location = RBtree<Key,Data>(key,data,Color::RED);
    (*location)->parent = parent;
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
        os << "(" << node.key << " -> " << node.data << " ->" << node.color << ")";
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