#ifndef __KDTREE_HPP
#define __KDTREE_HPP

#include <tuple>
using std::tuple;
#include <vector>
using std::vector;
#include <utility>
using std::move;
#include <memory>
using std::unique_ptr;

template <class Key>
class KdNode;

template <class Key>
class KdTree : public unique_ptr<KdNode<Key>>{
    public:
    KdTree() = default;
    virtual ~KdTree() = default;
    KdTree(const KdTree<Key>&) = default;
    KdTree<Key>& operator=(const KdTree<Key>&) = default;
    KdTree(KdTree<Key>&&) = default;
    KdTree<Key>& operator=(KdTree<Key>&&) = default;
    KdTree(const int _dim) : dimensions{_dim} {}

    template <class... Dimensions>
    void insert(vector<tuple<Dimensions...>>);
    template <class... Dimensions>
    void insert(tuple<Dimensions...>);
    template <class... Dimensions>
    tuple<Dimensions...>* search(tuple<Dimensions...>&);

    private:
    int dimensions;
};

#endif