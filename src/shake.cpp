
#include "filesystem.h"
#include "package.h"
#include <iostream>

int main(int argc, char *argv[])
{
    std::string name = "package.yml";
    shake::lsr(argv[1], [&](auto d)
    {
        std::cout << d.path << "\t" << d.name << std::endl;
        if (name == d.name)
        {
            shake::package p = shake::package::load(d.path);
            std::cout << p.name << "\t" << p.ver.to_string() << std::endl;
            std::cout << "Download" << std::endl;
            if (p.download_to(argv[1])) std::cout << "Match md5 sum\n";
            else std::cout << "Md5 sums don't match\n";
        }
    });
}
