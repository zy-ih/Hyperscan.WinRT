#include "pch.h"
#include "ExpressionExtended.h"
#include "ExpressionExtended.g.cpp"

namespace winrt::Hyperscan::implementation
{
    uint64_t ExpressionExtended::MinOffset()
    {
        return _minOffset;
    }
    void ExpressionExtended::MinOffset(uint64_t value)
    {
        _minOffset = value;
        flags |= HS_EXT_FLAG_MIN_OFFSET;
    }
    uint64_t ExpressionExtended::MaxOffset()
    {
        return _maxOffset;
    }
    void ExpressionExtended::MaxOffset(uint64_t value)
    {
        _maxOffset = value;
        flags |= HS_EXT_FLAG_MAX_OFFSET;
    }
    uint64_t ExpressionExtended::MinLength()
    {
        return _minLength;
    }
    void ExpressionExtended::MinLength(uint64_t value)
    {
        _minLength = value;
        flags |= HS_EXT_FLAG_MIN_LENGTH;
    }
    uint64_t ExpressionExtended::EditDistance()
    {
        return _editDistance;
    }
    void ExpressionExtended::EditDistance(uint64_t value)
    {
        _editDistance = value;
        flags |= HS_EXT_FLAG_EDIT_DISTANCE;
    }
    uint64_t ExpressionExtended::HammingDistance()
    {
        return _hammingDistance;
    }
    void ExpressionExtended::HammingDistance(uint64_t value)
    {
        _hammingDistance = value;
        flags |= HS_EXT_FLAG_HAMMING_DISTANCE;
    }
    void ExpressionExtended::Reset()
    {
        flags = 0ULL;
    }
}
