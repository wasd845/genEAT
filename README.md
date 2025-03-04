### GenEAT 🛠️

GenEAT is a powerful tool designed to streamline the process of generating export table hijacking DLLs. By simply providing the name of a DLL file along with the original function name prefix or the name after hijacking, GenEAT automatically generates a compilable DLL source code. Users only need to compile the generated source code to obtain an export table hijacking DLL.

#### Platform Support

⚠️ **Note**: GenEAT is currently only supported on Windows platforms due to its dependency on Windows-specific PE file structures and APIs.

#### Building

GenEAT uses CMake build system. Make sure you have CMake and a C++ compiler (Visual Studio 2019 or later recommended) installed.

```powershell
# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the project
cmake --build . --config Release
```

The compiled executable will be located at `build/Release/genEAT.exe`.

#### Usage

1. Build the tool using the instructions above.
2. Execute GenEAT with the following parameters:
   - `-d` : Path to the DLL file you want to analyze
   - `-c` : Path to save the generated C++ source file
   - `-n` : Original DLL name for export

Example:
```powershell
genEAT.exe -d example.dll -c output.cpp -n original.dll
```

After execution, GenEAT will generate the `output.cpp` file containing the export table hijacking code. You can then compile this file into a DLL using your preferred C++ compiler.

#### Features

- **Automated Generation**: Simplifies the process of creating export table hijacking DLLs
- **PE File Analysis**: Accurately reads and processes Windows PE file structures
- **Export Table Handling**: Properly manages and generates export table entries
- **Easy Integration**: Generated code is ready to compile into a working DLL

#### Special Thanks

Special thanks to lyshark for the valuable contributions and support to this project.

#### How to Contribute

Contributions to GenEAT are welcome! Feel free to submit issues, feature requests, or pull requests.

#### License

This project is licensed under the MIT License - see the LICENSE file for details.
