# Stelle120

Sets your custom FPS in Star Rail

## Usage

1. Download the latest release from the [releases page](https://github.com/teppyboy/stelle120/releases)
2. Run the executable

## Building

Either press the build button in VS Code or run manually:

```bash
g++ -g src/stelle120.cpp -o stelle120.exe
```
### Cross-compiling

Assuming you have the mingw-w64 toolchain installed, run:

```bash
x86_64-w64-mingw32-g++ -g src/stelle120.cpp -o stelle120.exe
```

#### Why not Visual Studio?

No.

## Credits

- https://github.com/nlohmann/json for the JSON library (lib/json.hpp)
- Stelle for being a cool MC

## License

[MIT](./LICENSE)
