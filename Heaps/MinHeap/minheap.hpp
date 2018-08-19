#ifndef __MINHEAP_HPP
#define __MINHEAP_HPP

#include <vector>
using std::vector;
#include <utility>
using std::pair;

template <class Key, class Data>
class MinHeap {
    public:
    MinHeap() = default;
    MinHeap(const int size) {heap = vector<pair<Key,Data>>(size);}
    virtual ~MinHeap() = default;
    MinHeap(const MinHeap<Key,Data>&) = default;
    MinHeap(MinHeap<Key,Data>&&) = default;
    MinHeap<Key,Data>& operator=(const MinHeap<Key,Data>&) = default;
    MinHeap<Key,Data>& operator=(MinHeap<Key,Data>&&) = default;

    void insert(Key&&,Data&&);
    void remove_root();
    void min_heapify_On(size_t root=0);
    void min_heapify_Onlgn(vector<pair<Key,Data>>&&);
    void sift_up(size_t);
    void sift_down(size_t);

     // 0 indexed backing datastructure
    constexpr size_t parent(size_t node) const {
        return node > 0 ? (node-1)/2 : node;
    }

    constexpr size_t left(size_t parent) const {
        return 2*parent + 1;
    }

    constexpr size_t right(size_t parent) const {
        return 2*parent + 2;
    }

    private:
    vector<pair<Key,Data>> heap;
};

template <class Key, class Data>
void MinHeap<Key,Data>::insert(Key&& _k, Data&& _d) {

}

template <class Key, class Data>
void MinHeap<Key,Data>::remove_root() {

}

template <class Key, class Data>
void MinHeap<Key,Data>::min_heapify_On(size_t root) {

}

template <class Key, class Data>
void MinHeap<Key,Data>::min_heapify_Onlgn(vector<pair<Key,Data>>&& data) {

}

template <class Key, class Data>
void MinHeap<Key,Data>::sift_up(size_t node) {

}

template <class Key, class Data>
void MinHeap<Key,Data>::sift_down(size_t node) {

}

#endif
