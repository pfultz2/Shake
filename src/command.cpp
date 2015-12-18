#include "command.h"
#include <array>

namespace shake {
std::unordered_map<std::string, command_function> commands;

void add_command(const std::string& name, command_function f)
{
    commands.insert(std::make_pair(name, f));
}
command_function get_command(const std::string& name)
{
    return commands.at(name);
}

command_context parse_command(const std::vector<std::string>& args)
{
    command_context result;
    // TODO: Skip command name
    auto start = args.begin() + 2;

    std::for_each(start, args.end(), [&](const std::string& s)
    {
        std::array<char, 2> double_dash = {'-', '-'};
        if (std::equal(double_dash.begin(), double_dash.end(), s.begin())) result.options.push_back(s);
        else result.subs.push_back(s);
    });

    return result;
}

void run_command(int argc, char *argv[])
{
    std::vector<std::string> args(argv, argv+argc);
    command_context ctx = parse_command(args);
    // TODO: Check for help and version options
    get_command(args.at(1))(ctx);
}
}
