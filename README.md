> ~~Currently this is not working due to the game resetting settings on launch. I will try to find a way to fix this.~~<br>
> In version 1.3 it worked again, somehow miHoYo.

# Stelle120

Sets your custom FPS in Star Rail

## Usage

1. Download the latest release from the [releases page](https://github.com/teppyboy/stelle120/releases)
2. Run the executable

### Command line arguments

There are some CLI arguments you can use to customize the program.

+ `--target-fps=<fps>`: Sets the target FPS, by default will ask the user.
+ `--vsync=<1/0>`: Sets whether to enable VSync or not, by default will ask the user to disable if enabled.
+ `--no-pause`: Disables the "pause" (Press any key to continue) after the program has finished.
+ `--dry-run`: Do not save the changes to the file, just print the changes to the console.
+ `--help`: Prints the help message.

## Building

Either press the build button in VS Code or run `make` in the root directory.

### Cross-compiling

Assuming you have the mingw-w64 toolchain installed, run `make` in the root directory.

#### Why not Visual Studio (MSBuild)?

No.

## Credits

- https://github.com/nlohmann/json for the JSON library (lib/json.hpp)
- Stelle for being a cool MC

## License

[MIT](./LICENSE)
