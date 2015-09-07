/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    md5.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_MD5_H
#define SHAKE_GUARD_MD5_H

#include <string>

namespace shake {

std::string md5(const char* data, std::size_t size);

template<class T>
std::string md5(const T& x)
{
    return md5(x.data(), x.size());
}

std::string md5_file(const std::string& name);

}

#endif