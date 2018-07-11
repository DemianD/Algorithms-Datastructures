#ifndef __BST_HPP
#define __BST_HPP

#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
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
class BST : public BSTnodeptr<T>
{
    using BSTnodeptr<T>::BSTnodeptr;

  public:
    BST<T>() = default;
    BST<T>(const BST<T> &) = default;
    BST<T>(BST<T> &&) = default;
    BST<T> &operator=(const BST<T> &) = default;
    BST<T> &operator=(BST<T> &&) = default;

    void DFS(function<void(T &&)>, function<void(T &&)>, function<void(T &&)>);
    void DFS(function<void(T &&)>, enum Order);
    void BFS(function<void(T &&)>);

    friend istream &operator>>(istream &is, BST<T> &bb)
    {
        return bb.read_from_file(is);
    }
    friend ostream &operator<<(ostream &os, const BST<T> &bb)
    {
        //return bb.output_to_stream_bfs(os);
        return bb.output_to_stream(os);
    }
    void add(const T &);
    void add(T &&);

    void remove(const T &);
    void remove(T &&);

    ostream &output_to_stream(ostream &);
    int aantalSleutels() const;
    istream &read_from_file(istream &);
    ostream &output_to_stream_bfs(ostream &os) const;

  private:
};

template <class T>
class BSTnode
{
    friend class BST<T>;

  public:
    BSTnode(){};
    explicit BSTnode(const T &_item) : item(_item){};
    explicit BSTnode(T &&_item) : item(move(_item)){};
    explicit BSTnode(const BSTnode<T> &_other) : item(_other.item), left(_other.left), right(_other.right){};
    explicit BSTnode(BSTnode<T> &&_other) : item(move(_other.item)), left(move(_other.left)), right(move(_other.right)){};
    BSTnode<T> &operator=(const BSTnode<T> &_other) :
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

    friend ostream &operator<<(ostream & os, const BSTnode<T> &_node){
        os << _node.item;
        os << "\t Left child: "<<_node.left<<endl;
        os << "\t Right child: "<<_node.right<<endl;        
        return os;
    };

  private:
    T item;
    BST<T> left, right;
};

#endif
