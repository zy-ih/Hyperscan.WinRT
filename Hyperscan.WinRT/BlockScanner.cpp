#include "pch.h"
#include "BlockScanner.h"
#include "BlockScanner.g.cpp"

namespace winrt::Hyperscan::implementation
{
    void BlockScanner::Scan(winrt::Windows::Storage::Streams::IBuffer const& buffer) const
    {
        Global::unique_hs_scratch local_scratch{nullptr};
        // scratch 是不可重入的 每次clone一个新的
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
        // 获取this强引用 避免异步挂起期间对象销毁
        const auto strong_this = const_cast<BlockScanner*>(this)->get_strong();
        // 在线程池中执行 该过程是计算密集的
        co_await winrt::resume_background();
        Scan(buffer);
    }
}
