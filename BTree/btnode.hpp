#ifndef __BTNODE_HPP
#define __BTNODE_HPP

#include <functional>
using std::function;
#include <vector>
using std::vector;

template <class Key, class Data>
class BTnode
{
    friend class BTree<Key, Data>;

  public:
    BTnode() { current_nr_of_keys = 0; };
    virtual ~BTnode() = default;
    BTnode(const BTnode<Key, Data> &) = default;
    BTnode &operator=(const BTnode<Key, Data> &) = default;
    BTnode(BTnode<Key, Data> &&) = default;
    BTnode &operator=(BTnode<Key, Data> &&) = default;
    BTnode(bool _is_leaf, int _minimum_degree) : is_leaf{_is_leaf}, minimum_degree_{minimum_degree}
    {
        current_nr_of_keys = 0;
        keys = vector<Key>(2 * minimum_degree - 1);
        data = vector<Data>(2 * minimum_degree - 1);
        if (!is_leaf)
        {
            childpointers = vector<BTnode<Key, Data> *>(2 * minimum_degree);
        }
    }

    void traverse(function<void(const BTnode<Key, Data> &)>);
    BTnode<Key, Data> *search(const Key &);
    void insert_without_split(const Key &, const Data &);
    void split_node(int, BTnode<Key, Data> *);
    void remove_bottom_up(const Key &);
    bool empty() const;
    bool keys_full() const;

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

template <class Key, class Data>
void BTnode<Key, Data>::insert_without_split(const Key &key, const Data &data)
{
    int i = current_nr_of_keys -1;
    if(is_leaf){
        while(i>=0 && keys[i]>key){
            keys[i+1] = move(keys[i]);
            data[i+1] = move(data[i]);
            i--;
        }
        keys[i+1] = key;
        data[i+1] = data;
        current_nr_of_keys+=1;
    }
    else {
        while(i>=0 && keys[i]>key){
            i--;
        }
        if(childpointers[i]->keys_full()){
            split_node(i+1,childpointers[i+1]);
            if(keys[i+1]<key){
                i++;
            }
        }
        childpointers[i+1]->insert_without_split(key,data);
    }
}

template <class Key, class Data>
void BTnode<Key, Data>::split_node(int to_split_child_index, BTnode<Key, Data> *to_split)
{
    BTnode<Key, Data> new_node(to_split->is_leaf, to_split->minimum_degree);
    new_node.current_nr_of_keys = minimum_degree - 1;

    for (int i = 0; i < minimum_degree - 1; i++)
    {
        new_node.keys[i] = move(to_split->keys[minimum_degree + i]);
        new_node.data[i] = move(to_split->data[minimum_degree + i]);
    }
    if (!to_split->is_leaf)
    {
        for(int i=0;i<minimum_degree;i++){
            new_node.childpointers[i] = to_split->childpointers[minimum_degree+i];
        }
    }
    to_split->current_nr_of_keys = minimum_degree -1;
    for(int j=current_nr_of_keys; j>=to_split_child_index+1;j--){
        this->childpointers[j+1] = this->childpointers[j];        
    }
    this->childpointers[to_split_child_index+1] = &new_node; //!FIX

    for(int j=current_nr_of_keys-1; j>=to_split_child_index;j--){
        this->keys[j+1] = this->keys[j];
    }
    this->keys[to_split_child_index] = to_split->keys[minimum_degree-1];

    this->current_nr_of_keys += 1;
}

template <class Key, class Data>
bool BTnode<Key, Data>::empty() const
{
    return current_nr_of_keys == 0;
}

template <class Key, class Data>
bool BTnode<Key, Data>::keys_full() const
{
    return current_nr_of_keys == minimum_degree * 2 - 1;
}

#endif