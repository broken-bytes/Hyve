#pragma once

namespace Hyve::Core {
    enum class HAccessLevel {
        Public, // Public across all modules
        Internal, // Public within the module
        Private, // Private to the scope
        Fileprivate // Private to the file
    };
}