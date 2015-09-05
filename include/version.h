/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    version.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_VERSION_H
#define SHAKE_GUARD_VERSION_H

#include <vector>
#include <string>
#include "compare.h"

#define SHAKE_VERSION_COMPARE_OP(op, name) \
    friend bool operator op (const version& x, const version& y) \
    { \
        return x.subs op y.subs; \
    }

namespace shake {

struct version
{
    static version parse(const std::string& x);
    std::vector<int> subs;

    bool empty() const { return subs.empty(); }

    std::string to_string() const;

    SHAKE_COMPARE_OPS(SHAKE_VERSION_COMPARE_OP)
};



}

#endif