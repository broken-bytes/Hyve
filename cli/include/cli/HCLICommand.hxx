#pragma once

#include <functional>
#include <string>

namespace Hyve::CLI {
    struct HCLICommand {
        std::string ShortName;
        std::string LongName;
        std::string Alias;
        std::string Help;
        std::function<void(std::string)> Handler;
    };
}