#include "pch.h"
#include "Global.h"
#include "Pattern.h"
#include "Pattern.g.cpp"

namespace winrt::Hyperscan::implementation
{
    hstring Pattern::Expression() const
    {
        return to_hstring(_expression);
    }

    void Pattern::Expression(hstring const& value)
    {
        _expression = to_string(value);
    }
    winrt::Hyperscan::ExpressionInfo Pattern::GetExpressionInfo() const
    {
        hs_expr_info_t* expr_info{nullptr};
        auto auto_free = wil::scope_exit([=] { Global::hs_free(expr_info); });
        Global::unique_hs_compile_error compile_error{nullptr};
        Global::check_hs_error(::hs_expression_info(_expression.c_str(), std::to_underlying(Flags()), &expr_info, compile_error.put()), std::move(compile_error));

        return {
            expr_info->min_width,
            expr_info->max_width,
            static_cast<bool>(expr_info->unordered_matches),
            static_cast<bool>(expr_info->matches_at_eod),
            static_cast<bool>(expr_info->matches_only_at_eod)
        };
    }

    Pattern::Pattern(const hstring& expression, CompileFlags flags, const ExpressionExtended& extended, uint32_t id):Flags{flags}, Extended{extended}, Id{id}
    {
        Expression(expression);
    }

}
