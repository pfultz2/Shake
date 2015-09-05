
#include "version.h"
#include "split.h"
#include <algorithm>

namespace shake {

version version::parse(const std::string& x)
{
    version v;
    for(auto&& elem:split(x, "."))
    {
        v.subs.push_back(std::stoi(elem));
    }
    return v;
}

std::string version::to_string() const
{
    return std::accumulate(this->subs.begin(), this->subs.end(), std::string(), [](auto&& result, auto&& value)
    {
        if (result.empty()) return std::to_string(value);
        else return result + "." + std::to_string(value);
    });
}

}
