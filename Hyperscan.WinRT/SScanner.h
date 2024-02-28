#pragma once
#include "SScanner.g.h"
#include "Global.h"

namespace winrt::Hyperscan::implementation
{
    // SScanner 保有暂存和流状态，可以单独设置匹配事件
    struct SScanner : SScannerT<SScanner>
    {
        SScanner(winrt::Hyperscan::StreamScanner const& streamScanner);
        void ScanNext(winrt::Windows::Storage::Streams::IBuffer const& buffer);

        // 为托管环境支持确定性析构
        void Close();
        ~SScanner();
        wil::untyped_event<winrt::Hyperscan::MatchEventArgs> Matched;
        winrt::Hyperscan::SScanner CreateScanner() const;
    private:
        ::winrt::Hyperscan::StreamScanner _streamScanner{nullptr};
        Global::unique_hs_scratch _scratch;
        hs_stream_t* _stream{nullptr};
    };
}
namespace winrt::Hyperscan::factory_implementation
{
    struct SScanner : SScannerT<SScanner, implementation::SScanner>
    {
    };
}
