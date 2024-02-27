#pragma once
#include "ExpressionExtended.g.h"

namespace winrt::Hyperscan::implementation
{
    struct ExpressionExtended : ExpressionExtendedT<ExpressionExtended>
    {
        ExpressionExtended() = default;

        uint64_t MinOffset();
        void MinOffset(uint64_t value);
        uint64_t MaxOffset();
        void MaxOffset(uint64_t value);
        uint64_t MinLength();
        void MinLength(uint64_t value);
        uint32_t EditDistance();
        void EditDistance(uint32_t value);
        uint32_t HammingDistance();
        void HammingDistance(uint32_t value);
        void Reset();

        hs_expr_ext_t _ext{.flags = 0ULL};
    };
}

namespace winrt::Hyperscan::factory_implementation
{
    struct ExpressionExtended : ExpressionExtendedT<ExpressionExtended, implementation::ExpressionExtended>
    {
    };
}
