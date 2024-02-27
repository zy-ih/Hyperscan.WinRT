#pragma once
#include "VectorScanner.g.h"
#include "Compiler.h"

namespace winrt::Hyperscan::implementation
{
    struct VectorScanner : VectorScannerT<VectorScanner, Hyperscan::implementation::Compiler>
    {
        VectorScanner()
        {
            _mode = CompileMode::Vectored;
            Platform(PlatformInfo::HostPlatformInfo());
        }

        void Scan(winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::Streams::IBuffer> const& buffers) const;
        winrt::Windows::Foundation::IAsyncAction ScanAsync(winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::Streams::IBuffer> buffers) const;
    };
}
namespace winrt::Hyperscan::factory_implementation
{
    struct VectorScanner : VectorScannerT<VectorScanner, implementation::VectorScanner>
    {
    };
}
