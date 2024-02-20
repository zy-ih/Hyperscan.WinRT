#pragma once
#include "Pattern.g.h"

namespace winrt::Hyperscan::implementation
{
    struct Pattern : PatternT<Pattern>
    {
        Pattern() = default;
        Pattern(const hstring& expression, CompileFlags flags, const ExpressionExtended& extended, uint32_t id);
        hstring Expression() const;
        void Expression(hstring const& value);
        winrt::Hyperscan::ExpressionInfo GetExpressionInfo() const;

        wil::single_threaded_rw_property<Hyperscan::CompileFlags> Flags;
        wil::single_threaded_rw_property<Hyperscan::ExpressionExtended> Extended;
        wil::single_threaded_rw_property<uint32_t> Id;

    private:
        std::string _expression;
    };
}

namespace winrt::Hyperscan::factory_implementation
{
    struct Pattern : PatternT<Pattern, implementation::Pattern>
    {
    };
}
