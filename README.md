# Thunder

Thunder is a game engine built from scratch in C(99). 
It is built to be fast, light, and run literally anywhere with no dependencies.

## Getting Started
Thunder uses CMake as its build system, and includes nothing by default.
Everything is a plugin, and you can build Thunder in any way you want.
The recommended way to get started is to take a look at the `examples` directory,
and then pick one or more examples to build. Then, simply run a command like
```sh
cmake -B build -DEXAMPLES=example1\;example2
```

NOTE: I can only test the code on macOS for now.

## License
Thunder's source is all licensed under the MIT License, see
[License](LICENSE)
for more details.
