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
#include <exception>
#include <stdexcept>
#include <cerrno>
#include <memory>

namespace shake {

namespace detail {

template<class T>
std::size_t ptr_sizeof(T*)
{
    return sizeof(T);
}

}

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

    void throw_error()
    {
        const char* message = std::strerror(this->error());
        this->clear_error();
        throw std::runtime_error(message);
    }

    long tell()
    {
        assert(this->handler != nullptr);
        return std::ftell(this->handler.get());
    }

    void seek(long offset, int origin)
    {
        assert(this->handler != nullptr);
        int err = std::fseek(this->handler.get(), offset, origin);
        if (err != 0) this->throw_error();
    }

    template<class T, typename std::enable_if<(std::is_pod<T>()), int>::type = 0>
    std::size_t read(T& x)
    {
        assert(this->handler != nullptr);
        return std::fread(&x, sizeof(T), 1, this->handler.get());
    }

    template<class T, typename std::enable_if<(!std::is_pod<T>()), int>::type = 0>
    std::size_t read(T& x)
    {
        assert(this->handler != nullptr);
        return std::fread(x.data(), detail::ptr_sizeof(x.data()), x.size(), this->handler.get());
    }

    template<class T, typename std::enable_if<(std::is_pod<T>()), int>::type = 0>
    std::size_t write(const T& x)
    {
        assert(this->handler != nullptr);
        return std::fwrite(x.data(), detail::ptr_sizeof(x.data()), x.size(), this->handler.get());
    }

    template<class T, typename std::enable_if<(!std::is_pod<T>()), int>::type = 0>
    std::size_t write(const T& x)
    {
        assert(this->handler != nullptr);
        return std::fwrite(&x, sizeof(T), 1, this->handler.get());
    }


};

}

#endif