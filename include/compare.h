/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    compare.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_COMPARE_H
#define SHAKE_GUARD_COMPARE_H

#define SHAKE_COMPARE_OPS(m) \
m(<, less) \
m(>, greater) \
m(<=, less_equal) \
m(>=, greater_equal) \
m(==, equal_to) \
m(!=, not_equal_to)


#endif