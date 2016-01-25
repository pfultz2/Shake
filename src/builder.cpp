
#include "builder.h"

static std::unordered_map<std::string, std::shared_ptr<builder>> builder_map = {};

std::unordered_map<std::string, std::shared_ptr<builder>>& builders()
{
    return builder_map;
}