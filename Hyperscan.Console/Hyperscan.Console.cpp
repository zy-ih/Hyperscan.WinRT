#include <iostream>
#include <winrt/Hyperscan.h>

int main()try
{
    winrt::init_apartment();

    winrt::Hyperscan::BlockScanner block_scanner;

    block_scanner.Compile(L"++", winrt::Hyperscan::CompileFlags::Caseless | winrt::Hyperscan::CompileFlags::UTF8 | winrt::Hyperscan::CompileFlags::SOMLeftMost | winrt::Hyperscan::CompileFlags::UCP);
}
catch (const winrt::hresult_error& e)
{
    std::cerr << winrt::to_string(e.message()) << '\n';
}
