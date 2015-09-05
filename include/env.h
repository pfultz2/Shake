/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    env.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_ENV_H
#define SHAKE_GUARD_ENV_H

#include <string>

namespace shake {

void set_env_var(const std::string& key, const std::string& value);
std::string get_env_var(const std::string& key);

}

#endif
