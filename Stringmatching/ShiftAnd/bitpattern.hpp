#ifndef __BITPATTERN_HPP
#define __BITPATTERN_HPP
#include <iostream>
typedef unsigned int uint;
const int patroonlengte = sizeof(uint) * 8;
class Bitpatroon {
public:
    uint bits;
    Bitpatroon(uint u = 0) : bits(u) {  };
//EN-operator
    const Bitpatroon operator&(const Bitpatroon& b) const {
        return Bitpatroon(bits & b.bits);
    }
//OF-operator
    const Bitpatroon operator|(const Bitpatroon& b) const {
        return Bitpatroon(bits | b.bits);
    }
//EN-=-operator
    const Bitpatroon& operator&=(const Bitpatroon& b) {
        bits &= b.bits;
        return *this;
    }
//OF-=-operator
    const Bitpatroon& operator|=(const Bitpatroon& b) {
        bits |= b.bits;
        return *this;
    }
//logische operatoren
    bool en(const Bitpatroon& b) const {
        return (bits & b.bits) != 0;
    }
    bool of(const Bitpatroon& b) const {
        return (bits | b.bits) != 0;
    }
//let op: shiftoperaties verplaatsen niets als verplaatsing >= patroonlengte.
    const Bitpatroon shiftlinks(uint verplaatsing) const {
        return Bitpatroon(bits << verplaatsing);
    }
    const Bitpatroon shiftrechts(uint verplaatsing) const {
        return Bitpatroon(bits >> verplaatsing);
    }
//niet beveiligd: u moet kleiner dan patroonlengte zijn.
//geef een bitpatroon waarvan de u-de bit van links aan staat
    static Bitpatroon eenbit(uint u) {
        int q = patroonlengte;
        int v = patroonlengte - 1 - u;
        return Bitpatroon(uint(1) << (patroonlengte - 1 - u));
    }
    friend std::ostream& operator<<(std::ostream& os, const Bitpatroon& b) {
        for (int i = 0; i < patroonlengte; i++) {
            os << b.en(eenbit(i));
        }
        return os;
    }
};
#endif
