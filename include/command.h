/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    command.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef SHAKE_GUARD_COMMAND_H
#define SHAKE_GUARD_COMMAND_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#define SHAKE_PRIMITIVE_CAT(x, ...) x ## __VA_ARGS__
#define SHAKE_CAT(x, ...) SHAKE_PRIMITIVE_CAT(x, __VA_ARGS__)

#define SHAKE_PRIMITIVE_STRINGIZE(...) #__VA_ARGS__
#define SHAKE_STRINGIZE(...) SHAKE_PRIMITIVE_STRINGIZE(__VA_ARGS__)

namespace shake {


struct command_context
{
    std::vector<std::string> options;
    std::vector<std::string> subs;
};
using command_function = std::function<void(const command_context&)>;

void add_command(const std::string& name, command_function);
command_function get_command(const std::string& name);

void run_command(int argc, char *argv[]);


struct auto_register_command
{
    auto_register_command(std::string name, command_function f)
    {
        add_command(name, f);
    }
};


#define SHAKE_COMMAND(name) \
struct name \
{ void operator()(const shake::command_context& context) const; }; \
static shake::auto_register_command SHAKE_CAT(name, _register) = shake::auto_register_command(SHAKE_STRINGIZE(name), name()); \
void name::operator()(const shake::command_context& context) const
}

#endif