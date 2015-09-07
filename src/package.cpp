
#include "package.h"
#include <yaml-cpp/yaml.h>
#include "download.h"
#include "string_utils.h"
#include "merge_path.h"
#include "filesystem.h"
#include "md5.h"

#include <iostream>

namespace shake {

package package::load(const std::string& path)
{
    package result;
    YAML::Node p = YAML::LoadFile(path);
    result.name = p["name"].as<std::string>();
    result.url = p["url"].as<std::string>();
    result.ver = version::parse(p["version"].as<std::string>());
    result.md5 = trim(p["md5"].as<std::string>());
    
    if (p["package"]) result.pkg = p["package"].as<std::string>();
    else result.pkg = result.name;

    if (p["depends"].IsMap())
    {
        for(auto&& x:p["depends"])
        {
            result.deps.insert(std::make_pair(x.first.as<std::string>(), requirement::parse(x.second.as<std::string>())));
        }
    }
    else if (p["depends"].IsSequence())
    {
        for(auto&& x:p["depends"])
        {
            result.deps.insert(std::make_pair(x.as<std::string>(), requirement()));
        }
    }

    return result;
}

bool package::download_to(const std::string &dir)
{
    auto filename = merge_path(dir, split(this->url, "/").back());
    if (not exists(filename)) download(this->url, filename);
    std::cout << "Md5: " << md5_file(filename) << "\n";
    std::cout << "Md5: " << this->md5 << "\n";
    return md5_file(filename) == this->md5;
}

}
