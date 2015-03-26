/*
 * flag.h
 *
 *  Created on: 26 Mar 2015
 *      Author: lester
 */

#ifndef FLAG_H_
#define FLAG_H_

#include <stdexcept>
#include <limits>
/**
 * Flags base on enum type
 */
template<typename B, typename S = unsigned>
class BitFlags {
    static_assert(std::is_unsigned<S>::value,"Member variable holding bit flags must be an unsigned type");
    S flag;
public:
    BitFlags(S v = 0)
            : flag(v) {

    }
    bool is(B bit) const {
        static_assert((1<< bit) <= std::numeric_limits<S>::max(),"There is not enough space to hold this flag");
        return ((flag & (1 << bit)) != 0);
    }
    void set(B bit) {
        static_assert((1<< bit) <= std::numeric_limits<S>::max(),"There is not enough space to hold this flag");
        flag |= (1 << bit);
    }
    void clear(B bit) {
        static_assert((1<< bit) <= std::numeric_limits<S>::max(),"There is not enough space to hold this flag");
        flag &= ~(1 << bit);
    }
};



#endif /* FLAG_H_ */
