
#include "split.h"
#include <sstream>

namespace shake {

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
