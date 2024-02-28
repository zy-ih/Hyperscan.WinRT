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
        wil::single_threaded_rw_property<SOMHorizonMode> SOMHorizon;

        // 单模式匹配
        void Compile(hstring const& pattern, winrt::Hyperscan::CompileFlags const& flags);
        // 纯文本匹配
        void CompileLiteral(hstring const& pattern, winrt::Hyperscan::CompileFlags const& flags);
        // 多模式纯文本匹配
        void CompileMultiLiteral(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns);
        // 多模式匹配
        void CompileMulti(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns);
        // 多模式匹配扩展
        void CompileMultiEx(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns);
        hstring GetDatabaseInfo() const;
        uint64_t GetDatabaseSize() const;
    protected:
        hs_platform_info_t _platform;
        CompileMode _mode;
        uint32_t CompileMode() const noexcept;
    public:
        Global::unique_hs_database _dataBase{nullptr};
        Global::unique_hs_scratch _scratch{nullptr};
    };
}
