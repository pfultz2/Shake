/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    download.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_DOWNLOAD_H
#define SHAKE_GUARD_DOWNLOAD_H

#include <string>

namespace shake {

void download(const std::string& url, const std::string& filename);

}

#endif