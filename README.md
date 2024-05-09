### GenEAT 🛠️

GenEAT is a powerful tool designed to streamline the process of generating export table hijacking DLLs. By simply providing the name of a DLL file along with the original function name prefix or the name after hijacking, GenEAT automatically generates a compilable DLL source code. Users only need to compile the generated source code to obtain an export table hijacking DLL.

#### Usage

1. Compile the tool.
2. Execute GenEAT.exe with the following parameters:
   - `-d` : Path to the DLL file.
   - `-c` : Path to save the generated C source file.
   - `-n` : Original function name prefix or hijacked name.

Example:
```
GenEAT.exe -d ./lyshark.dll -c ./lyshark.c -n old_lyshark
```

After execution, GenEAT will produce the `lyshark.c` file, which can be compiled to obtain the export table hijacking DLL.

#### Features

- **Efficiency**: Automates the generation process, saving time and effort.
- **Flexibility**: Supports customization of function name prefixes or hijacked names.
- **Simplicity**: Users only need to compile the generated source code to obtain the desired DLL.

#### How to Contribute

Contributions to GenEAT are welcome! Feel free to submit issues, feature requests, or pull requests.

#### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

#### 🚀 Happy Hijacking! 🚀
