
#include "md5.h"
#include "slurp.h"
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>

namespace shake {

std::string md5(const char* data, std::size_t size)
{
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char*) data, size, result);

    std::stringstream ss;
    for(int x:result) ss << std::setfill('0') << std::setw(2) << std::hex << x;

    return ss.str();
}

std::string md5_file(const std::string& name)
{
    return md5(slurp(name));
}

}
