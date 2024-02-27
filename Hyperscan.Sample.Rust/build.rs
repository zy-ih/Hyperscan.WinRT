fn main() {
    if let Err(error) = windows_bindgen::bindgen([
        "--in",
        if cfg!(debug_assertions) {
            "../x64/Debug/Hyperscan.WinRT/Hyperscan.winmd"
        } else {
            "../x64/Release/Hyperscan.WinRT/Hyperscan.winmd"
        },
        &format!("{}\\System32\\WinMetadata", env!("windir")),
        "--out",
        "src/hyperscan.rs",
        "--filter",
        "Hyperscan",
    ]) {
        panic!("{error}");
    }
}
