
#include "filesystem.h"
#include "package.h"
#include "command.h"
#include <iostream>

SHAKE_COMMAND(info)
{
    printf("info\n");
    printf("options\n");
    for(auto&& x:context.options) printf("%s\n", x.c_str());
    printf("subs\n");
    for(auto&& x:context.subs) printf("%s\n", x.c_str());
}

int main(int argc, char *argv[])
{
    shake::run_command(argc, argv);
    // std::string name = "package.yml";
    // shake::lsr(argv[1], [&](auto d)
    // {
    //     std::cout << d.path << "\t" << d.name << std::endl;
    //     if (name == d.name)
    //     {
    //         shake::package p = shake::package::load(d.path);
    //         std::cout << p.name << "\t" << p.ver.to_string() << std::endl;
    //         std::cout << "Download" << std::endl;
    //         p.unpack(argv[1]);
    //     }
    // });
}
