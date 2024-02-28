#include "pch.h"
#include "Global.h"
#include "Settings.h"
#include "Settings.g.cpp"


namespace winrt::Hyperscan::implementation
{
    // 设置外部分配函数作为Hyperscan的分配函数 允许跨abi调用
    // @param moduleName: 模块名称
    // @param allocProcName: 分配函数
    // @param freeProcName: 释放函数
    void Settings::SetAllocator(hstring const& moduleName, hstring const& allocProcName, hstring const& freeProcName)
    {
        wil::unique_hmodule module(GetModuleHandleW(moduleName.c_str()));
        auto hs_alloc = reinterpret_cast<hs_alloc_t>(GetProcAddress(module.get(), to_string(allocProcName).c_str()));

        auto hs_free(reinterpret_cast<hs_free_t>(GetProcAddress(module.get(), to_string(freeProcName).c_str())));
        Global::check_hs_error(hs_set_allocator(hs_alloc, hs_free));
        Global::hs_alloc = hs_alloc;
        Global::hs_free = hs_free;
    }
}
