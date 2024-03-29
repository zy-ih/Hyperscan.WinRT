#pragma once
#include "MatchEventArgs.g.h"

namespace winrt::Hyperscan::implementation
{
    // 将 hs_match_event_t 回调转换为事件处理
    struct MatchEventArgs : MatchEventArgsT<MatchEventArgs>
    {
        MatchEventArgs() = default;
        MatchEventArgs(uint64_t from, uint64_t to, uint32_t id, uint32_t flags);
        wil::single_threaded_property<uint64_t> From;
        wil::single_threaded_property<uint64_t> To;
        wil::single_threaded_property<uint32_t> Id;
        wil::single_threaded_property<uint32_t> Flags;
        wil::single_threaded_rw_property<uint32_t> ReturnValue;
    };
}

namespace winrt::Hyperscan::factory_implementation
{
    struct MatchEventArgs : MatchEventArgsT<MatchEventArgs, implementation::MatchEventArgs>
    {
    };
}
