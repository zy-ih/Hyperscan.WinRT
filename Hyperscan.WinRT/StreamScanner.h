#pragma once
#include "StreamScanner.g.h"
#include "Compiler.h"
#include "SScanner.h"

namespace winrt::Hyperscan::implementation
{
    struct StreamScanner : StreamScannerT<StreamScanner, Hyperscan::implementation::Compiler>
    {
        StreamScanner()
        {
            _mode = CompileMode::Stream;
            Platform(PlatformInfo::HostPlatformInfo());
        }

        winrt::Hyperscan::SScanner CreateScanner() const;
    };
}
namespace winrt::Hyperscan::factory_implementation
{
    struct StreamScanner : StreamScannerT<StreamScanner, implementation::StreamScanner>
    {
    };
}
