#include "kdtree.hpp"
#include "kdnode.hpp"
#include <iostream>
#include <random>

const int TEST_SIZE = 10;

using namespace std;

int main(int argc, char **argv)
{
    KdTree<int, int, int, int> t1(4);
    cout << t1.depth() << endl;
    vector<tuple<int, int, int, int>> data;
    KdNode<int, int, int, int> n{{1, 1, 1, 1}};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        data.emplace_back(tuple<int, int, int, int>(dis(gen), dis(gen), dis(gen), dis(gen)));
    }
    t1.insert(move(data), 0);
    return 0;
}