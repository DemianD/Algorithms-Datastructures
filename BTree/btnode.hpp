#ifndef __BTNODE_HPP
#define __BTNODE_HPP

#include <functional>
using std::function;
#include <vector>
using std::vector;

template <class Key, class Data>
class BTnode
{
  public:
    BTnode(){};
    virtual ~BTnode() = default;
    BTnode(const BTnode<Key, Data> &) = default;
    BTnode &operator=(const BTnode<Key, Data> &) = default;
    BTnode(BTnode<Key, Data> &&) = default;
    BTnode &operator=(BTnode<Key, Data> &&) = default;
    BTnode(bool _is_leaf, int _minimum_degree) : is_leaf{_is_leaf}, minimum_degree_{minimum_degree}
    {
        current_nr_of_keys = 0;
        keys = vector<Key>(2 * minimum_degree - 1);
        childpointers = vector<BTnode<Key, Data> *>(2 * minimum_degree);
    }

    void traverse(function<void(const BTnode<Key, Data> &)>);
    BTnode<Key, Data> *search(const Key &);
    void insert_bottom_up(const Key &, const Data &);
    void remove_bottom_up(const Key &);

  private:
    bool is_leaf;
    int current_nr_of_keys;
    int minimum_degree;
    vector<BTnode<Key, Data> *> childpointers;
    vector<Key> keys;
    vector<Data> data;
}

template <Key, Data>
void BTnode<Key, Data>::traverse(function<void(const BTnode<Key, Data> &)> &operation)
{
    int i;
    for (i = 0; i < current_nr_of_keys; i++)
    {
        if (!is_leaf)
        {
            childpointers[i]->traverse(operation);
        }
        operation(*this);
    }
    // since there is always a child more than there are keys (keys: 2t-1, childpointers: 2t)
    // we should also traverse the final child
    if (!is_leaf)
    {
        childpointers[i]->traverse(operation)
    }
    operation(*this);
}

template <Key, Data>
BTnode<Key, Data> *BTnode<Key, Data>::search(const Key &key)
{
    // you could also do binary search or interpolating search
    int i = 0;
    while (i < current_nr_of_keys && key > keys[i])
    {
        i++;
    }
    // do we have the key here?
    if (keys[i] == key)
    {
        return this;
    }

    // if we didn't have the key here and there are no deeper level (aka this is already a leaf, then we don't have the key)
    else if (is_leaf)
    {
        return nullptr;
    }
    // if there are other levels, we may try to look if the key is there
    else
    {
        return childpointers[i]->search(key);
    }
}

#endif