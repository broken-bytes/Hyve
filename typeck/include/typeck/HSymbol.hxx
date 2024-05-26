#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Hyve::Typeck {
	class HSymbol {
    public:
        std::string Name;
        std::weak_ptr<HSymbol> Parent;
        std::vector<std::shared_ptr<HSymbol>> Children;
    };
}