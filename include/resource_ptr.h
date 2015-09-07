/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    resource_ptr.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_RESOURCE_PTR_H
#define SHAKE_GUARD_RESOURCE_PTR_H

#include <memory>

namespace shake {

template<class T, void(*Deleter)(T*)>
struct deleter
{
    deleter()
    {}
    void operator()(T* x) const
    {
        Deleter(x);
    }
};

template<class T, void(*Deleter)(T*)>
using resource_ptr = std::unique_ptr<T, deleter<T, Deleter>>;

}

#endif