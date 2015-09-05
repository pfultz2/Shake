/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    requirement.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_REQUIREMENT_H
#define SHAKE_GUARD_REQUIREMENT_H

#include <functional>
#include "version.h"

namespace shake {

struct requirement
{
    static requirement parse(const std::string& x);
    version v;
    std::function<bool(const version& x, const version& y)> op;
    
    bool satisifies(const version& x) const
    {
        if (this->v.empty()) return true;
        return this->op(this->v, x);
    }
};

}

#endif