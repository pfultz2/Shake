/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    builder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_BUILDER_H
#define SHAKE_GUARD_BUILDER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "environment.h"

namespace shake {

struct build_context
{
    environment e;
};

struct builder
{
    struct schema
    {
        enum class type
        {
            sequence,
            map,
            string
        };
        std::map<std::string, type> keys;
    };

    virtual schema get_schema() = 0;

    virtual void build(const build_context& ctx) = 0;

    virtual void set(const std::string& key, const std::string& value)
    {}

    virtual void set(const std::string& key, const std::map<std::string, std::string>& m)
    {}

    virtual void set(const std::string& key, const std::vector<std::string>& seq)
    {}

    virtual void set(const std::vector<std::string>& seq)
    {}

    virtual ~builder
    {}
};

std::unordered_map<std::string, std::shared_ptr<builder>>& builders();

template<class T>
struct builder_factory
{
    builder_factory()
    {
        builders()[T::name()] = T::create();
    }
};

template<class Derived>
struct builder_decorator : builder
{
    static builder_factory<Derived> register_;
};

template<class Derived>
builder_factory<Derived> builder_decorator<Derived>::register_ = builder_factory<Derived>();

}

#endif