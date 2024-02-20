#include "pch.h"
#include "BlockScanner.h"
#include "BlockScanner.g.cpp"

namespace winrt::Hyperscan::implementation
{
    void BlockScanner::Scan(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        Global::unique_hs_scratch scratch{nullptr};
        Global::check_hs_error(hs_alloc_scratch(_dataBase.get(), scratch.put()));
        Global::check_hs_error(hs_scan(_dataBase.get(), reinterpret_cast<const char*>(buffer.data()), buffer.Length(), 0, scratch.get(),
            [](unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context) ->int
        {
            static_cast<BlockScanner*>(context)->Matched.invoke(*static_cast<BlockScanner*>(context), MatchEventArgs(from, to, id, flags));
            return 0;
        }, this));
    }
}
