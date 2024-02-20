#pragma once
#include "ExpressionInfo.g.h"

namespace winrt::Hyperscan::implementation
{
    struct ExpressionInfo : ExpressionInfoT<ExpressionInfo>
    {
        ExpressionInfo() = default;
        ExpressionInfo(uint32_t minWidth, uint32_t maxWidth, bool isUnorderedMatches, bool isMatchesAtEOD, bool isMatchesOnlyAtEOD);
        wil::single_threaded_rw_property<uint32_t> MinWidth;
        wil::single_threaded_rw_property<uint32_t> MaxWidth;
        wil::single_threaded_rw_property<bool> IsUnorderedMatches;
        wil::single_threaded_rw_property<bool> IsMatchesAtEOD;
        wil::single_threaded_rw_property<bool> IsMatchesOnlyAtEOD;
    };
}

namespace winrt::Hyperscan::factory_implementation
{
    struct ExpressionInfo : ExpressionInfoT<ExpressionInfo, implementation::ExpressionInfo>
    {
    };
}
