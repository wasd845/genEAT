### GenEAT 🛠️

GenEAT is a powerful tool designed to streamline the process of generating export table hijacking DLLs. By simply providing the name of a DLL file along with the original function name prefix or the name after hijacking, GenEAT automatically generates a compilable DLL source code. Users only need to compile the generated source code to obtain an export table hijacking DLL.

#### Building

GenEAT uses CMake build system.

```bash
# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the project
cmake --build . --config Release
```

#### Usage

1. Build the tool using one of the methods above.
2. Execute GenEAT with the following parameters:
   - `-d` : Path to the DLL file.
   - `-c` : Path to save the generated C source file.
   - `-n` : Original function name prefix or hijacked name.

Example:
```
GenEAT.exe -d ./example.dll -c ./example.c -n old_example
```

After execution, GenEAT will produce the `example.c` file, which can be compiled to obtain the export table hijacking DLL.

#### Features

- **Cross-Platform**: Supports building on multiple platforms using CMake.
- **Efficiency**: Automates the generation process, saving time and effort.
- **Flexibility**: Supports customization of function name prefixes or hijacked names.
- **Simplicity**: Users only need to compile the generated source code to obtain the desired DLL.

#### Special Thanks

Special thanks to lyshark for the valuable contributions and support to this project.

#### How to Contribute

Contributions to GenEAT are welcome! Feel free to submit issues, feature requests, or pull requests.

#### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

#### 🚀 Happy Hijacking! 🚀
