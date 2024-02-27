#include "pch.h"
#include "SScanner.h"
#include "SScanner.g.cpp"
#include "StreamScanner.h"

namespace winrt::Hyperscan::implementation
{
    ::winrt::Hyperscan::implementation::StreamScanner* GetStreamScannerImpl(::winrt::Hyperscan::StreamScanner const& scanner) noexcept
    {
        return winrt::get_self<::winrt::Hyperscan::implementation::StreamScanner>(scanner);
    }
    SScanner::SScanner(winrt::Hyperscan::StreamScanner const& streamScanner)
    {
        _streamScanner = streamScanner;
        Global::check_hs_error(hs_open_stream(GetStreamScannerImpl(_streamScanner)->_dataBase.get(), 0, &_stream));
        Global::check_hs_error(hs_clone_scratch(GetStreamScannerImpl(_streamScanner)->_scratch.get(), _scratch.put()));
    }
    void SScanner::ScanNext(winrt::Windows::Storage::Streams::IBuffer const& buffer)
    {
        Global::check_hs_error(hs_scan_stream(_stream, reinterpret_cast<const char*>(buffer.data()), buffer.Length(), 0, _scratch.get(),
            [](unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context) -> int
        {
            MatchEventArgs event_args(from, to, id, flags);
            static_cast<SScanner*>(context)->Matched.invoke(*static_cast<SScanner*>(context), event_args);
            return event_args.ReturnValue();
        }, this));
    }

    void SScanner::Close()
    {
        if (_stream)
        {
            Global::check_hs_error(hs_close_stream(_stream, _scratch.get(), [](unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context) -> int
            {
                MatchEventArgs event_args(from, to, id, flags);
                static_cast<SScanner*>(context)->Matched.invoke(*static_cast<SScanner*>(context), event_args);
                return event_args.ReturnValue();
            }, this));
            _stream = nullptr;
        }
    }
    SScanner::~SScanner()
    {
        Close();
    }
}
