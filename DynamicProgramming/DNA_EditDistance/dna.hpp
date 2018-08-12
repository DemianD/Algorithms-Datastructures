#ifndef __DNA_HPP
#define __DNA_HPP

#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iomanip>
#include <algorithm>

class DNAsequence : public string
{
  public:
    DNAsequence() = default;
    DNAsequence(const string &content) : string{content} {};
    DNAsequence(string &&content) : string{move(content)} {};
    virtual ~DNAsequence() = default;
    DNAsequence(const DNAsequence &other) = default;
    DNAsequence &operator=(const DNAsequence &other) = default;
    DNAsequence(DNAsequence &&other) = default;
    DNAsequence &operator=(DNAsequence &&other) = default;

    int d_td(const string &) const;
    int d_bu(const string &) const;

    int d_top_down(const DNAsequence &) const;
    int d_top_down_op(const DNAsequence &, vector<vector<int>> &, int, int) const;

    int d_bottom_up(const DNAsequence &) const;
};

int DNAsequence::d_td(const string& other) const {    
   return d_top_down(DNAsequence{other});    
}

int DNAsequence::d_top_down(const DNAsequence &other) const
{
    const size_t FROM_LENGTH = size() + 1;
    const size_t TO_LENGTH = other.size() + 1;
    vector<vector<int>> distances(FROM_LENGTH, vector<int>(TO_LENGTH, -1));
    int distance = d_top_down_op(other, distances, FROM_LENGTH - 1, TO_LENGTH - 1);
    return distance;
}

int DNAsequence::d_top_down_op(const DNAsequence &other, vector<vector<int>> &distances, int from, int to) const
{
    if (distances[from][to] < 0)
    {
        if (from == 0)
        {
            distances[from][to] = to;
        }
        else if (to == 0)
        {
            distances[from][to] = from;
        }
        else if ((*this)[from - 1] == other[to - 1])
        { // if the letters at the locations are the same, you can move diagonally
            distances[from][to] = d_top_down_op(other, distances, from - 1, to - 1);
        }
        else
        {
            int additions = 1 + d_top_down_op(other, distances, from, to - 1);
            int deletions = 1 + d_top_down_op(other, distances, from - 1, to);
            int changes = 1 + d_top_down_op(other, distances, from - 1, to - 1);
            distances[from][to] = std::min({additions, deletions, changes});
        }
    }
    return distances[from][to];
}

#endif