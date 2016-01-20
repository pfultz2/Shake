/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    environment.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_ENVIRONMENT_H
#define SHAKE_GUARD_ENVIRONMENT_H

#include <vector>
#include <unordered_map>
#include <string>

namespace shake {

struct environment
{
    std::vector<std::string> channels;
    std::string prefix;

    bool cross_compile;
    std::string system_name;

    std::string c;
    std::string cxx;
    std::string rc;

    std::string cflags;
    std::string cxxflags;
    std::string ldflags;

};

}

#endif