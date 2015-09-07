/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    package.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_PACKAGE_H
#define SHAKE_GUARD_PACKAGE_H

#include <vector>
#include <unordered_map>
#include <string>
#include "version.h"
#include "requirement.h"

namespace shake {

struct package
{
    static package load(const std::string& path);
    std::string name;
    std::string path;
    std::string pkg;
    version ver;
    std::string url;
    std::string md5;
    std::unordered_map<std::string, requirement> deps;

    void unpack(const std::string &dir, const std::string cache="");
};

}

#endif