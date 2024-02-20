#pragma once
#include "Settings.g.h"

namespace winrt::Hyperscan::implementation
{
    struct Settings
    {
        Settings() = default;

        static void SetAllocator(hstring const& moduleName, hstring const& allocProcName, hstring const& freeProcName);
    };
}
namespace winrt::Hyperscan::factory_implementation
{
    struct Settings : SettingsT<Settings, implementation::Settings>
    {
    };
}
