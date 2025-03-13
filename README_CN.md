### GenEAT 导出表劫持工具 🛠️

GenEAT 是一个强大的工具，专门用于简化导出表劫持 DLL 的生成过程。只需提供 DLL 文件名以及原始函数名前缀或劫持后的名称，GenEAT 就能自动生成可编译的 DLL 源代码。用户只需编译生成的源代码即可获得导出表劫持 DLL。

#### 平台支持

⚠️ **注意**：由于 GenEAT 依赖于 Windows 特定的 PE 文件结构和 API，目前仅支持 Windows 平台。

#### 构建步骤

GenEAT 使用 CMake 构建系统。请确保已安装 CMake 和 C++ 编译器（推荐使用 Visual Studio 2019 或更高版本）。

```powershell
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake ..

# 构建项目
cmake --build . --config Release
```

编译后的可执行文件将位于 `build/Release/genEAT.exe`。

#### 使用方法

1. 按照上述说明构建工具。
2. 使用以下参数执行 GenEAT：
   - `-d` : 要分析的 DLL 文件路径
   - `-c` : 生成的 C++ 源文件保存路径
   - `-n` : 用于导出的原始 DLL 名称

示例：
```powershell
genEAT.exe -d example.dll -c output.cpp -n original.dll
```

执行后，GenEAT 将生成包含导出表劫持代码的 `output.cpp` 文件。然后您可以使用首选的 C++ 编译器将此文件编译为 DLL。

#### 主要特性

- **自动化生成**：简化导出表劫持 DLL 的创建过程
- **PE 文件分析**：准确读取和处理 Windows PE 文件结构
- **导出表处理**：正确管理和生成导出表项
- **易于集成**：生成的代码可直接编译为可用的 DLL

#### 特别感谢

特别感谢 lyshark 对本项目的宝贵贡献和支持。

#### 如何贡献

欢迎为 GenEAT 做出贡献！随时提交问题、功能请求或拉取请求。

#### 许可证

本项目采用 GPLv3 许可证 - 详见 LICENSE 文件。

#### 关键词

导出表劫持、DLL 注入、PE 文件分析、Windows 安全、DLL 劫持、API Hook、导出函数、Windows 开发工具