#ifndef __DNA_HPP
#define __DNA_HPP

#include <iostream>
#include <string>
using std::string;
#include <vector>
#include <iomanip>
#include <algorithm>

class DNAsequence: public string {
    public:
    DNAsequence() = default;
    DNAsequence(const string& content): string{content}{};
    DNAsequence(string && content) : string{content} {};
    virtual ~DNAsequence() = default;
    DNAsequence(const DNAsequence& other) = default;
    DNAsequence& operator=(const DNAsequence& other) = default;
    DNAsequence(DNAsequence&& other) = default;
    DNAsequence& operator=(DNAsequence&& other) = default;

    
};

#endif