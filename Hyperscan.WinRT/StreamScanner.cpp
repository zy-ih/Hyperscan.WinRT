#include "pch.h"
#include "StreamScanner.h"
#include "StreamScanner.g.cpp"

namespace winrt::Hyperscan::implementation
{
    winrt::Hyperscan::SScanner StreamScanner::CreateScanner() const
    {
        return winrt::Hyperscan::SScanner(*this);
    }
}
