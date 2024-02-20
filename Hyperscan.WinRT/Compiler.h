#pragma once
#include "Compiler.g.h"
#include "Global.h"

namespace winrt::Hyperscan::implementation
{
    struct Compiler : CompilerT<Compiler>
    {
        Compiler() = default;

        PlatformInfo Platform()const;
        void Platform(const PlatformInfo& value) noexcept;
        wil::untyped_event<winrt::Hyperscan::MatchEventArgs> Matched;

        void Compile(hstring const& pattern, winrt::Hyperscan::CompileFlags const& flags);
        void CompileLiteral(hstring const& pattern, winrt::Hyperscan::CompileFlags const& flags);
        void CompileMultiLiteral(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns, winrt::Hyperscan::CompileFlags const& flags);
        void CompileMulti(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns, winrt::Hyperscan::CompileFlags const& flags);
        void CompileMultiEx(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns, winrt::Hyperscan::CompileFlags const& flags, winrt::Hyperscan::ExpressionExtended const& extended);
    protected:
        Global::unique_hs_database _dataBase{nullptr};
        hs_platform_info_t _platform;
        CompileMode _mode;
    };
}
