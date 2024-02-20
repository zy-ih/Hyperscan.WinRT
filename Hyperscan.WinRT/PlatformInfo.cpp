#include "pch.h"
#include "Global.h"
#include "PlatformInfo.h"
#include "PlatformInfo.g.cpp"

namespace winrt::Hyperscan::implementation
{
    PlatformInfo::PlatformInfo(CPUFeatures features, CompilerTune tune):Features{features}, Tune{tune}
    {
    }

    Hyperscan::PlatformInfo PlatformInfo::HostPlatformInfo()
    {
        hs_platform_info_t platform;
        Global::check_hs_error(::hs_populate_platform(&platform));
        return Hyperscan::PlatformInfo{CPUFeatures(platform.cpu_features), CompilerTune(platform.tune)};
    }
}
