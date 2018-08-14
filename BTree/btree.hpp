#ifndef __BTREE_HPP
#define __BTREE_HPP

template <class Key, class Data>
class BTree{
    public:
    BTree() = default;
    virtual ~BTree() = default;
    BTree(const BTree<Key,Data>&) = default;
    BTree(BTree<Key,Data>&&) = default;
    BTree& operator=(const BTree<Key,Data>&) = default;
    BTree& operator=(BTree<Key,Data>&&) = default;
    
    private:
    int minimum_degree;
    BTnode<Key,Data> root;
};

#endif