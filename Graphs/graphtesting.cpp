#include "graph.hpp"
#include "kosaraju.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void test_kosaraju();

int main(int argc, char **argv)
{
    test_kosaraju();
    return 0;
}

void test_kosaraju()
{
    Graph<DirectionType::DIRECTED> G(11);
    G.insertEdge(0, 1);
    G.insertEdge(1, 2);
    G.insertEdge(2, 0);
    G.insertEdge(1, 3);
    G.insertEdge(3, 4);
    G.insertEdge(4, 5);
    G.insertEdge(5, 3);
    G.insertEdge(6, 5);
    G.insertEdge(6, 7);
    G.insertEdge(7, 8);
    G.insertEdge(8, 9);
    G.insertEdge(9, 6);
    G.insertEdge(9, 10);
    Kosaraju k(G);
    k.findSCCs();

    for (const auto &row : k.SCCs)
    {
        for (const auto &col : row)
        {
            cout << setw(4) << col;
        }
        cout << endl;
    }
}