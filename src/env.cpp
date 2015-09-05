
#include "env.h"
#include <cstdlib>

namespace shake {
void set_env_var(const std::string& key, const std::string& value)
{
    setenv(key.c_str(), value.c_str(), true);
}
std::string get_env_var(const std::string& key)
{
    return std::getenv(key.c_str());
}

}
