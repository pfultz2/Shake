/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    split.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_SPLIT_H
#define SHAKE_GUARD_SPLIT_H

#include <vector>
#include <string>

namespace shake {

std::vector<std::string> split(const std::string& text, const std::string& delim);

}

#endif