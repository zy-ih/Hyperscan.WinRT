#pragma once
#include "MatchEventArgs.g.h"

namespace winrt::Hyperscan::implementation
{
    struct MatchEventArgs : MatchEventArgsT<MatchEventArgs>
    {
        MatchEventArgs() = default;
        MatchEventArgs(uint64_t from, uint64_t to, uint32_t id, uint32_t flags);
        wil::single_threaded_property<uint64_t> From;
        wil::single_threaded_property<uint64_t> To;
        wil::single_threaded_property<uint32_t> Id;
        wil::single_threaded_property<uint32_t> Flags;
    };
}

namespace winrt::Hyperscan::factory_implementation
{
    struct MatchEventArgs : MatchEventArgsT<MatchEventArgs, implementation::MatchEventArgs>
    {
    };
}
