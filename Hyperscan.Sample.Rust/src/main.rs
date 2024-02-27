mod hyperscan;
use std::process::Command;

use windows::{core::*, Foundation::*, Security::Cryptography::*};

fn main() -> Result<()> {
    let block_scanner = hyperscan::BlockScanner::new()?;
    block_scanner.Compile(
        h!(r#"-\w+=\w+\b"#),
        hyperscan::CompileFlags::Caseless
            | hyperscan::CompileFlags::SOMLeftMost
            | hyperscan::CompileFlags::UTF8,
    )?;
    block_scanner.SetSOMHorizon(hyperscan::SOMHorizonMode::SOMHorizonSmall)?;

    let data = CryptographicBuffer::ConvertStringToBinary(h!(r#"cmake -G "Visual Studio 17 2022" -A x64 -Thost=x64 -DCMAKE_CXX_STANDARD=17 -Droot7=ON -DCMAKE_CXX_FLAGS="/arch:AVX2" -DCMAKE_INSTALL_PREFIX=C:\Users\ultim\root-6.26 ../root_src"#),BinaryStringEncoding::Utf8).unwrap();

    block_scanner.Matched(&EventHandler::<hyperscan::MatchEventArgs>::new(
        |_sender, args| {
            println!(
                "match form {} to {}",
                args.as_ref().unwrap().From()?,
                args.as_ref().unwrap().To()?
            );
            Ok(())
        },
    ))?;

    block_scanner.Scan(&data)?;
    let _ = Command::new("cmd.exe").arg("/c").arg("pause").status();
    Ok(())
}
