
#include "requirement.h"
#include "compare.h"
#include "split.h"

#define SHAKE_REQUIREMENT_COMPARE_OP(oper, name) \
if (x == #oper) r.op = std::name<version>(); \
else

namespace shake {

requirement requirement::parse(const std::string& s)
{
    requirement r;
    r.op = std::equal_to<version>();
    for(auto&& x:split(s, " "))
    {
        if (not x.empty())
        {
            SHAKE_COMPARE_OPS(SHAKE_REQUIREMENT_COMPARE_OP)
            {
                r.v = version::parse(x);
            }
        }
    }
    return r;
}

}
