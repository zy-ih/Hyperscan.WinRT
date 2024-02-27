#include "pch.h"
#include "MatchEventArgs.h"
#include "MatchEventArgs.g.cpp"


namespace winrt::Hyperscan::implementation
{
    MatchEventArgs::MatchEventArgs(uint64_t from, uint64_t to, uint32_t id, uint32_t flags):
        From{from}, To{to}, Id{id}, Flags{flags}, ReturnValue{0}
    {

    }

}
