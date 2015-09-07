#include "slurp.h"
#include "file.h"
#include <vector>

namespace shake {

std::string slurp(const std::string& name)
{
    file f = std::fopen(name.c_str(), "r+");
    f.seek(0, SEEK_END);
    std::vector<char> buffer(f.tell());
    f.seek(0, SEEK_SET);
    f.read(buffer);
    return std::string(buffer.begin(), buffer.end());
}

}