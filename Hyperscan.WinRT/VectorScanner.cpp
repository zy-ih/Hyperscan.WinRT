#include "pch.h"
#include "VectorScanner.h"
#include "VectorScanner.g.cpp"

namespace winrt::Hyperscan::implementation
{
    struct buffers_info
    {
        std::vector<const char*> _buffers;
        std::vector<unsigned int> _lengths;
    };

    buffers_info GetBuffersInfo(winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::Streams::IBuffer> const& buffers)
    {
        buffers_info info;
        info._buffers.reserve(buffers.Size());
        info._lengths.reserve(buffers.Size());
        for (auto&& buffer : buffers)
        {
            info._buffers.push_back(reinterpret_cast<const char*>(buffer.data()));
            info._lengths.push_back(buffer.Length());
        }
        return info;
    }

    void VectorScanner::Scan(winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::Streams::IBuffer> const& buffers) const
    {
        Global::unique_hs_scratch local_scratch{nullptr};
        Global::check_hs_error(hs_clone_scratch(_scratch.get(), local_scratch.put()));

        auto info = GetBuffersInfo(buffers);
        Global::check_hs_error(hs_scan_vector(_dataBase.get(), info._buffers.data(), info._lengths.data(), buffers.Size(), 0, local_scratch.get(),
            [](unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context) -> int
        {
            MatchEventArgs event_args(from, to, id, flags);
            static_cast<VectorScanner*>(context)->Matched.invoke(*static_cast<VectorScanner*>(context), event_args);
            return event_args.ReturnValue();
        }, const_cast<VectorScanner*>(this)));
    }

    winrt::Windows::Foundation::IAsyncAction VectorScanner::ScanAsync(winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::Streams::IBuffer> buffers) const
    {
        const auto strong_this = const_cast<VectorScanner*>(this)->get_strong();
        co_await winrt::resume_background();
        Scan(buffers);
    }
}
