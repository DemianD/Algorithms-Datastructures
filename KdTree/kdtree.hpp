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
#include <cmath>
using std::max;

template <class... Key>
class KdNode;

template <class... Key>
class KdTree : public unique_ptr<KdNode<Key...>>{
    public:
    KdTree() = default;
    virtual ~KdTree() = default;
    KdTree(const KdTree<Key...>&) = default;
    KdTree<Key...>& operator=(const KdTree<Key...>&) = default;
    KdTree(KdTree<Key...>&&) = default;
    KdTree<Key...>& operator=(KdTree<Key...>&&) = default;
    KdTree(const int _dim) : dimensions{_dim} {}
    
    void insert(const vector<tuple<Key...>>&);    
    void insert(vector<tuple<Key...>>&&);    
    void insert(const tuple<Key...>&);    
    void insert(tuple<Key...>&&);    
    tuple<Key...>* search(tuple<Key...>&);

    int depth() const;

    private:
    int dimensions;
};

template <class... Key>
int KdTree<Key...>::depth() const
{
    if (!*this)
    {
        return -1;
    }
    return max((*this)->left.depth(), (*this)->right.depth()) + 1;
}


#endif