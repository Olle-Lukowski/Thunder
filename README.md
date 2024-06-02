# Thunder

Thunder is a game engine built from scratch in C(89). 
It is built to be fast, light, and run literally anywhere with no dependencies (not even libc).

## Getting Started
Thunder uses a custom build system, which needs to be bootstrapped by compiling `build.c` in the root directory of the project. 
You can then run the resulting executable to see what is possible with Thunder.

### Example Bootstrap Commands
MacOS (clang)
```sh
clang -nostdlib -std=c89 -Isrc/c/include -O2 -e __start build.c -o build
```
These are just examples, any C compiler that complies with the standard should work fine. 
If not, please open an issue. 
NOTE: I can only test the code on macOS for now.

## License
Thunder's source is all licensed under the MIT License, see
[License](LICENSE)
for more details.
