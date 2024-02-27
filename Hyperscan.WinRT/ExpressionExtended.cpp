#include "pch.h"
#include "ExpressionExtended.h"
#include "ExpressionExtended.g.cpp"

namespace winrt::Hyperscan::implementation
{
    uint64_t ExpressionExtended::MinOffset()
    {
        return _ext.min_offset;
    }
    void ExpressionExtended::MinOffset(uint64_t value)
    {
        _ext.min_offset = value;
        _ext.flags |= HS_EXT_FLAG_MIN_OFFSET;
    }
    uint64_t ExpressionExtended::MaxOffset()
    {
        return _ext.max_offset;
    }
    void ExpressionExtended::MaxOffset(uint64_t value)
    {
        _ext.max_offset = value;
        _ext.flags |= HS_EXT_FLAG_MAX_OFFSET;
    }
    uint64_t ExpressionExtended::MinLength()
    {
        return _ext.min_length;
    }
    void ExpressionExtended::MinLength(uint64_t value)
    {
        _ext.min_length = value;
        _ext.flags |= HS_EXT_FLAG_MIN_LENGTH;
    }
    uint32_t ExpressionExtended::EditDistance()
    {
        return _ext.edit_distance;
    }
    void ExpressionExtended::EditDistance(uint32_t value)
    {
        _ext.edit_distance = value;
        _ext.flags |= HS_EXT_FLAG_EDIT_DISTANCE;
    }
    uint32_t ExpressionExtended::HammingDistance()
    {
        return _ext.hamming_distance;
    }
    void ExpressionExtended::HammingDistance(uint32_t value)
    {
        _ext.hamming_distance = value;
        _ext.flags |= HS_EXT_FLAG_HAMMING_DISTANCE;
    }
    void ExpressionExtended::Reset()
    {
        _ext.flags = 0ULL;
    }
}
