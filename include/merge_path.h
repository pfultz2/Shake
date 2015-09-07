/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    merge_path.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_MERGE_PATH_H
#define SHAKE_GUARD_MERGE_PATH_H

#include <string>
#include <cassert>

namespace shake {

inline std::string merge_path(const std::string& p1, const std::string& p2)
{
    assert((p2.front() != '/') && "Cannot merge with an absolute path");
    if (p1.back() != '/') return p1 + '/' + p2;
    else return p1 + p2;
}

}

#endif