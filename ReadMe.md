# TOPMORE Kit (Prototype Demo)

## 构建方法

- 安装 Visual Studio 2022 并勾选 "使用 C++ 的桌面开发" 工作负荷。
- 去 https://github.com/ProjectMile/Mile.Qt 使用 onekey 开头的脚本编译定制后的 Qt
- 在 Visual Studio 中安装 Qt VS Tools 插件，并在 "扩展" -> "Qt VS Tools" -> 
  "Qt Versions" 设置你编译好的 Qt 工具链 
  (https://doc.qt.io/qtvstools/qtvstools-managing-qt-versions.html)，
  以下是我的开发环境配置
  - Mile.Qt_x64, D:\Tools\Mile.Qt\x64
  - Mile.Qt_x86, D:\Tools\Mile.Qt\x86
- 使用 Visual Studio 编译本项目
