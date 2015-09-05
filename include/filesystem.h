/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    filesystem.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_FILESYSTEM_H
#define SHAKE_GUARD_FILESYSTEM_H

#include <string>
#include <functional>

namespace shake {

bool exists(const char*);
inline bool exists(const std::string& path)
{
    return exists(path.c_str());
}

void make_dir(const char*);
inline void make_dir(const std::string& path)
{
    make_dir(path.c_str());
}


void make_path(const std::string& path);


struct dir
{
    const char* name;
    const char* path;
    const char* extension;
    bool is_dir;
    bool is_regular;
};

void ls(const char* path, std::function<void(dir)> f);
inline void ls(const std::string& path, std::function<void(dir)> f)
{
    ls(path.c_str(), f);
}

template<class F>
void lsr(const char* path, F f)
{
    ls(path, [&](dir d)
    {
        if (d.is_dir) lsr(d.path, f);
        f(d);
    });
}

template<class F>
void lsr(const std::string& path, F f)
{
    lsr(path.c_str(), f);
}

}

#endif