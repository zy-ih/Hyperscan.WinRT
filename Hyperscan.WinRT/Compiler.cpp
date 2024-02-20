#include "pch.h"
#include "Compiler.h"
#include "Compiler.g.cpp"

namespace winrt::Hyperscan::implementation
{
    void Compiler::Compile(hstring const& pattern, winrt::Hyperscan::CompileFlags const& flags)
    {
        Global::unique_hs_compile_error compile_error{nullptr};
        Global::check_hs_error(hs_compile(to_string(pattern).c_str(), std::to_underlying(flags), std::to_underlying(_mode), &_platform, _dataBase.put(), compile_error.put()), std::move(compile_error));
    }
    void Compiler::CompileLiteral(hstring const& pattern, winrt::Hyperscan::CompileFlags const& flags)
    {
        std::string u8pattern = winrt::to_string(pattern);
        Global::unique_hs_compile_error compile_error{nullptr};
        Global::check_hs_error(hs_compile_lit(u8pattern.c_str(), std::to_underlying(flags), u8pattern.length(), std::to_underlying(_mode), &_platform, _dataBase.put(), compile_error.put()), std::move(compile_error));
    }
    void Compiler::CompileMultiLiteral(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns, winrt::Hyperscan::CompileFlags const& flags)
    {
    }
    void Compiler::CompileMulti(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns, winrt::Hyperscan::CompileFlags const& flags)
    {
    }
    void Compiler::CompileMultiEx(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns, winrt::Hyperscan::CompileFlags const& flags, winrt::Hyperscan::ExpressionExtended const& extended)
    {
    }

    winrt::Hyperscan::PlatformInfo Compiler::Platform() const
    {
        return PlatformInfo(Hyperscan::CPUFeatures(_platform.cpu_features), Hyperscan::CompilerTune(_platform.tune));
    }

    void Compiler::Platform(const PlatformInfo& value) noexcept
    {
        _platform.cpu_features = std::to_underlying(value.Features());
        _platform.tune = std::to_underlying(value.Tune());
    }

}
