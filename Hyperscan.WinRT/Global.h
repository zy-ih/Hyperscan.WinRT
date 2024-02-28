#pragma once

namespace winrt::Hyperscan::Global
{
    // 全局分配/释放函数
    inline hs_alloc_t hs_alloc = malloc;
    inline hs_free_t hs_free = free;

    using unique_hs_compile_error = wil::unique_any<hs_compile_error_t*, decltype(&hs_free_compile_error), &hs_free_compile_error>;
    using unique_hs_database = wil::unique_any<hs_database_t*, decltype(&hs_free_database), &hs_free_database>;
    using unique_hs_scratch = wil::unique_any<hs_scratch_t*, decltype(&hs_free_scratch), &hs_free_scratch>;

    // 将 hs_error_t 转换为异常
    struct hyperscan_error :hresult_error
    {
        hyperscan_error(const hstring& message WINRT_IMPL_SOURCE_LOCATION_ARGS) noexcept: hresult_error(hresult{E_FAIL}, message, sourceInformation)
        {
        }
    };

    struct hyperscan_compile_error :hyperscan_error
    {
        using hyperscan_error::hyperscan_error;
    };

    [[noreturn]]
    inline void throw_hs_error(hs_error_t error)
    {
        if (error == HS_INVALID)
            throw hyperscan_error(L"A parameter passed to this function was invalid.");
        if (error == HS_NOMEM)
            throw std::bad_alloc();

        //if (error == HS_COMPILER_ERROR)
        //{
        //    throw hyperscan_error(L"The pattern compiler failed, and the hs_compile_error_t should be inspected for more detail.");
        //}

        if (error == HS_DB_VERSION_ERROR)
            throw hyperscan_error(L"The given database was built for a different version of Hyperscan.");
        if (error == HS_DB_PLATFORM_ERROR)
            throw hyperscan_error(L"The given database was built for a different platform (i.e., CPU type).");
        if (error == HS_DB_MODE_ERROR)
            throw hyperscan_error(L"The given database was built for a different mode of operation. This error is returned when streaming calls are used with a block or vectored database and vice versa.");
        if (error == HS_BAD_ALIGN)
            throw hyperscan_error(L"A parameter passed to this function was not correctly aligned.");
        if (error == HS_BAD_ALLOC)
            throw hyperscan_error(L"The memory allocator (either malloc() or the allocator set with hs_set_allocator()) did not correctly return memory suitably aligned for the largest representable data type on this platform.");
#ifdef _DEBUG
        if (error == HS_SCRATCH_IN_USE)
            throw hyperscan_error(L"The scratch region was already in use.");
#endif // _DEBUG

        if (error == HS_ARCH_ERROR)
            throw hyperscan_error(L"Unsupported CPU architecture.");
        if (error == HS_INSUFFICIENT_SPACE)
            throw hyperscan_error(L"Provided buffer was too small.");
        // if (error == HS_UNKNOWN_ERROR)
        throw hyperscan_error(L"Unexpected internal error.");
    }

    [[noreturn]]
    inline void throw_hs_compile_error(unique_hs_compile_error&& compile_error = nullptr)
    {
        std::wstring message_buffer;
        message_buffer.resize(256);

        if (compile_error.get()->expression >= 0)
            swprintf_s(message_buffer.data(), message_buffer.size(), L"The expression causing the compilation error has an index of %d.\nCompile Error: %ws", compile_error.get()->expression, winrt::to_hstring(compile_error.get()->message).c_str());
        else
            swprintf_s(message_buffer.data(), message_buffer.size(), L"Compile Error: %ws", winrt::to_hstring(compile_error.get()->message).c_str());
        throw hyperscan_compile_error(hstring(message_buffer));
    }

    inline void check_hs_error(hs_error_t error, unique_hs_compile_error&& compile_error = nullptr)
    {
        if (error == HS_SUCCESS)
            return;

        if (error == HS_SCAN_TERMINATED)
        {
            OutputDebugStringW(L"The engine was terminated by callback.");
            return;
        }

        if (error == HS_COMPILER_ERROR)
        {
            throw_hs_compile_error(std::move(compile_error));
        }

        throw_hs_error(error);
    }
}
