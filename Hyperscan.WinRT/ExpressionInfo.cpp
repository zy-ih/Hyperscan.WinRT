#include "pch.h"
#include "ExpressionInfo.h"
#include "ExpressionInfo.g.cpp"

namespace winrt::Hyperscan::implementation
{
    ExpressionInfo::ExpressionInfo(uint32_t minWidth, uint32_t maxWidth, bool isUnorderedMatches, bool isMatchesAtEOD, bool isMatchesOnlyAtEOD):
        MinWidth{minWidth}, MaxWidth{maxWidth}, IsUnorderedMatches{isUnorderedMatches},
        IsMatchesAtEOD{isMatchesAtEOD}, IsMatchesOnlyAtEOD{isMatchesOnlyAtEOD}
    {
    }
}
