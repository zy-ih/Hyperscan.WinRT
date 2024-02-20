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
        uint64_t EditDistance();
        void EditDistance(uint64_t value);
        uint64_t HammingDistance();
        void HammingDistance(uint64_t value);
        void Reset();

    private:
        uint64_t flags = 0ULL;
        uint64_t _minOffset;
        uint64_t _maxOffset;
        uint64_t _minLength;
        uint64_t _editDistance;
        uint64_t _hammingDistance;
    };
}

namespace winrt::Hyperscan::factory_implementation
{
    struct ExpressionExtended : ExpressionExtendedT<ExpressionExtended, implementation::ExpressionExtended>
    {
    };
}
