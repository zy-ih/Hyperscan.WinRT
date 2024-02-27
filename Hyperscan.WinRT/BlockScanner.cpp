#include "pch.h"
#include "BlockScanner.h"
#include "BlockScanner.g.cpp"

namespace winrt::Hyperscan::implementation
{
    void BlockScanner::Scan(winrt::Windows::Storage::Streams::IBuffer const& buffer) const
    {
        Global::unique_hs_scratch local_scratch{nullptr};
        Global::check_hs_error(hs_clone_scratch(_scratch.get(), local_scratch.put()));
        Global::check_hs_error(hs_scan(_dataBase.get(), reinterpret_cast<const char*>(buffer.data()), buffer.Length(), 0, local_scratch.get(),
            [](unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context) -> int
        {
            MatchEventArgs event_args(from, to, id, flags);
            static_cast<BlockScanner*>(context)->Matched.invoke(*static_cast<BlockScanner*>(context), event_args);
            return event_args.ReturnValue();
        }, const_cast<BlockScanner*>(this)));
    }
    winrt::Windows::Foundation::IAsyncAction BlockScanner::ScanAsync(winrt::Windows::Storage::Streams::IBuffer buffer) const
    {
        const auto strong_this = const_cast<BlockScanner*>(this)->get_strong();
        co_await winrt::resume_background();
        Scan(buffer);
    }
}
