#pragma once
#include "PlatformInfo.g.h"

namespace winrt::Hyperscan::implementation
{
    struct PlatformInfo : PlatformInfoT<PlatformInfo>
    {
        PlatformInfo() = default;
        PlatformInfo(CPUFeatures features, CompilerTune tune);
        static Hyperscan::PlatformInfo HostPlatformInfo();
        wil::single_threaded_rw_property<CPUFeatures> Features;
        wil::single_threaded_rw_property<CompilerTune> Tune;
    };
}
namespace winrt::Hyperscan::factory_implementation
{
    struct PlatformInfo : PlatformInfoT<PlatformInfo, implementation::PlatformInfo>
    {
    };
}
