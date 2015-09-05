/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    file.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_FILE_H
#define SHAKE_GUARD_FILE_H

#include <cstdio>
#include <cstring>
#include <cassert>
#include <memory>

namespace shake {

struct file
{
    std::unique_ptr<FILE, int(*)(FILE*)> handler;
    file(FILE* f) : handler(f, &std::fclose)
    {
        if (f == nullptr) throw std::runtime_error(std::strerror(errno));
    }

    template<class F>
    file(FILE* f, F closer) : handler(f, closer)
    {
        if (f == nullptr) throw std::runtime_error(std::strerror(errno));
    }

    bool eof()
    {
        assert(this->handler != nullptr);
        return std::feof(this->handler.get());
    }

    int error()
    {
        assert(this->handler != nullptr);
        return std::ferror(this->handler.get());
    }

    void clear_error()
    {
        assert(this->handler != nullptr);
        return std::clearerr(this->handler.get());
    }

    template<class T>
    std::size_t read(T& x)
    {
        assert(this->handler != nullptr);
        return std::fread(&x, sizeof(T), 1, this->handler.get());
    }

    template<class T>
    std::size_t write(const T& x)
    {
        assert(this->handler != nullptr);
        return std::fwrite(&x, sizeof(T), 1, this->handler.get());
    }


};

}

#endif