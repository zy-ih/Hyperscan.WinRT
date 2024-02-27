#include <iostream>
#include <winrt/Hyperscan.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Security.Cryptography.h>

int main()try
{
    winrt::init_apartment();

    winrt::Hyperscan::BlockScanner block_scanner;
    block_scanner.Compile(LR"(-\w+=\w+\b)", winrt::Hyperscan::CompileFlags::Caseless | winrt::Hyperscan::CompileFlags::UTF8 | winrt::Hyperscan::CompileFlags::SOMLeftMost);
    block_scanner.SOMHorizon(winrt::Hyperscan::SOMHorizonMode::SOMHorizonSmall);

    auto data = winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(LR"(cmake -G "Visual Studio 17 2022" -A x64 -Thost=x64 -DCMAKE_CXX_STANDARD=17 -Droot7=ON -DCMAKE_CXX_FLAGS="/arch:AVX2" -DCMAKE_INSTALL_PREFIX=C:\Users\ultim\root-6.26 ../root_src)", winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf8);
    block_scanner.Matched([&](winrt::Windows::Foundation::IInspectable const& sender, winrt::Hyperscan::MatchEventArgs const& args)
    {
        std::cout << std::string_view(reinterpret_cast<char*>(data.data()) + args.From(), args.To() - args.From()) << '\n';
    });
    auto pdata = data.data();
    block_scanner.Scan(data);
}
catch (const winrt::hresult_error& e)
{
    std::cerr << winrt::to_string(e.message()) << '\n';
}
