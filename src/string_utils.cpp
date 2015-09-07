
#include "string_utils.h"
#include <algorithm>

namespace shake {

std::string trim(const std::string &s)
{
    auto is_space = [](int c) { return std::isspace(c); };
    auto first = std::find_if_not(s.begin(), s.end(), is_space);
    auto last = std::find_if_not(s.rbegin(), s.rend(), is_space).base();
    return std::string(first, last);
}

std::vector<std::string> split(const std::string& text, const std::string& delim) 
{
    std::vector<std::string> tokens;
    int start = 0, end = 0;
    while ((end = text.find(delim, start)) != std::string::npos) 
    {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

}
