#include "pch.h"
#include "Compiler.h"
#include "Compiler.g.cpp"
#include "Pattern.h"
#include "ExpressionExtended.h"

namespace winrt::Hyperscan::implementation
{
    struct patterns_info
    {
        std::vector<const char*> _expressions;
        std::vector<size_t> _lengths;
        std::vector<unsigned int> _flags;
        std::vector<unsigned int> _ids;
        std::vector<const hs_expr_ext_t*> _exts;
        unsigned int _size;
    };

    static patterns_info GetPatternsInfo(Windows::Foundation::Collections::IVectorView<Hyperscan::Pattern> const& patterns);

    void Compiler::Compile(hstring const& pattern, winrt::Hyperscan::CompileFlags const& flags)
    {
        Global::unique_hs_compile_error compile_error{nullptr};
        Global::check_hs_error(hs_compile(to_string(pattern).c_str(), std::to_underlying(flags), CompileMode(), &_platform, _dataBase.put(), compile_error.put()), std::move(compile_error));
        Global::check_hs_error(hs_alloc_scratch(_dataBase.get(), _scratch.put()));
    }
    void Compiler::CompileLiteral(hstring const& pattern, winrt::Hyperscan::CompileFlags const& flags)
    {
        std::string u8pattern = winrt::to_string(pattern);
        Global::unique_hs_compile_error compile_error{nullptr};
        Global::check_hs_error(hs_compile_lit(u8pattern.c_str(), std::to_underlying(flags), u8pattern.length(), CompileMode(), &_platform, _dataBase.put(), compile_error.put()), std::move(compile_error));
        Global::check_hs_error(hs_alloc_scratch(_dataBase.get(), _scratch.put()));
    }
    void Compiler::CompileMultiLiteral(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns)
    {
        auto info = GetPatternsInfo(patterns);
        Global::unique_hs_compile_error compile_error{nullptr};
        Global::check_hs_error(hs_compile_lit_multi(info._expressions.data(), info._flags.data(), info._ids.data(), info._lengths.data(), info._size, CompileMode(), &_platform, _dataBase.put(), compile_error.put()), std::move(compile_error));
        Global::check_hs_error(hs_alloc_scratch(_dataBase.get(), _scratch.put()));
    }
    void Compiler::CompileMulti(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns)
    {
        auto info = GetPatternsInfo(patterns);
        Global::unique_hs_compile_error compile_error{nullptr};
        Global::check_hs_error(hs_compile_multi(info._expressions.data(), info._flags.data(), info._ids.data(), info._size, CompileMode(), &_platform, _dataBase.put(), compile_error.put()), std::move(compile_error));
        Global::check_hs_error(hs_alloc_scratch(_dataBase.get(), _scratch.put()));
    }
    void Compiler::CompileMultiEx(winrt::Windows::Foundation::Collections::IVectorView<winrt::Hyperscan::Pattern> const& patterns)
    {
        auto info = GetPatternsInfo(patterns);
        Global::unique_hs_compile_error compile_error{nullptr};
        Global::check_hs_error(hs_compile_ext_multi(info._expressions.data(), info._flags.data(), info._ids.data(), info._exts.data(), info._size, CompileMode(), &_platform, _dataBase.put(), compile_error.put()), std::move(compile_error));
        Global::check_hs_error(hs_alloc_scratch(_dataBase.get(), _scratch.put()));
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

    winrt::hstring Compiler::GetDatabaseInfo() const
    {
        char* info = nullptr;
        auto auto_free = wil::scope_exit([=] { Global::hs_free(info); });
        Global::check_hs_error(hs_database_info(_dataBase.get(), &info));
        return winrt::to_hstring(info);
    }

    uint64_t Compiler::GetDatabaseSize() const
    {
        uint64_t size = 0;
        Global::check_hs_error(hs_database_size(_dataBase.get(), &size));
        return size;
    }

    uint32_t Compiler::CompileMode() const noexcept
    {
        return std::to_underlying(_mode) | std::to_underlying(SOMHorizon());
    }

    patterns_info GetPatternsInfo(Windows::Foundation::Collections::IVectorView<Hyperscan::Pattern> const& patterns)
    {
        patterns_info info;
        auto& [es, ls, fs, is, exts, size] = info;
        size = patterns.Size();
        es.resize(size);
        ls.resize(size);
        fs.resize(size);
        is.resize(size);
        exts.resize(size, nullptr);

        for (uint32_t i = 0; i < size; i++)
        {
            auto pattern_impl = winrt::get_self<Hyperscan::implementation::Pattern>(patterns.GetAt(i));
            es[i] = pattern_impl->_expression.c_str();
            ls[i] = pattern_impl->_expression.length();
            fs[i] = std::to_underlying(patterns.GetAt(i).Flags());
            is[i] = patterns.GetAt(i).Id();
            if (pattern_impl->Extended() != nullptr)
            {
                auto ext_impl = winrt::get_self<Hyperscan::implementation::ExpressionExtended>(pattern_impl->Extended());
                exts[i] = &ext_impl->_ext;
            }
        }
        return info;
    }
}
