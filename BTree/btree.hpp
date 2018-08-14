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
    BTree(int _minimum_degree) : minimum_degree{_minimum_degree} {};
    void insert_bottom_up(const Key&, const Data&);
    
    private:
    int minimum_degree;
    BTnode<Key,Data> root;
};

template <class Key, class Data>
void insert_bottom_up(const Key& key, const Data& data) {
    if(root.empty()){
        root = BTnode(true,this->minimum_degree);
        root->keys[0] = key;
        root->data[0] = data;
        root->current_nr_of_keys = 1;
    }
    else if(root.keys_full()){

    }
    else {
        root->insert_without_split(key,data);
    }
}
#endif