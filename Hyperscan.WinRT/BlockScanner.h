#pragma once
#include "BlockScanner.g.h"
#include "Compiler.h"

namespace winrt::Hyperscan::implementation
{
    struct BlockScanner : BlockScannerT<BlockScanner, Hyperscan::implementation::Compiler>
    {
        BlockScanner()
        {
            _mode = CompileMode::Block;
            Platform(PlatformInfo::HostPlatformInfo());
        };

        void Scan(winrt::Windows::Storage::Streams::IBuffer const& buffer);
    };
}
namespace winrt::Hyperscan::factory_implementation
{
    struct BlockScanner : BlockScannerT<BlockScanner, implementation::BlockScanner>
    {
    };
}
