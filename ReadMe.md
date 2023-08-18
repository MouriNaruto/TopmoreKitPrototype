# TOPMORE Kit (Prototype Demo)

大家好，我是毛利

本仓库属于对 https://www.bilibili.com/opus/829932078655078422 和 https://www.bilibili.com/read/cv25757577 的回应

作为开发者 A 的我，最后退出 Legna 的事务的时候，提供了可编译的源代码，Git 那套流程都不习惯的 LegnaTeam 搞不定那就不是我的事情了

其次我退出以后赠品 SSD 是通过闪送归还 Legna 的，也没有得到任何开发收入

还有 Legna 在明知道我只想直接和 Legna 本人进行合作的时候让第三人即项目管理 B 插足且希望让其中途把我踢出的举动太过明显

使得本来就缺少安全感的我直接暴力结束合作成为了开发者 A，当然**幸运的是没有和他们签署任何合同**

当然我也看到了达墨那群人提了“重新约新的开发公司进行洽谈，给大家提供更好的版本”这点

总之我希望他们顺利，我看看能否把之前的源代码找出来，整理下开源出来好了，算是我的一点心意

反正我就是一个做开源项目的开发者，当时试图和 Legna 的合作属于我第一次在非前辈和工作地点那边做闭源项目

现在想想，属于失败的合作，也不想再做类似的尝试，既然是这样的话，我觉得那样可以不用让我之前辛苦写的家伙吃灰

当然本仓库主要还是为了证明我当时即使退出项目没有拿到钱归还了赠品 SSD 后依然提供了**有效的、可编译**的源代码，而且代码写的并不是那么不可维护

Documents 里有些当时的文档，感兴趣的人可以参考参考（小）

## 构建方法

- 安装 Visual Studio 2022 并勾选 "使用 C++ 的桌面开发" 工作负荷。
- 去 https://github.com/ProjectMile/Mile.Qt 使用 onekey 开头的脚本编译定制后的 Qt
- 在 Visual Studio 中安装 Qt VS Tools 插件，并在 "扩展" -> "Qt VS Tools" -> "Qt Versions" 设置你编译好的 Qt 工具链 (https://doc.qt.io/qtvstools/qtvstools-managing-qt-versions.html)，以下是我的开发环境配置
  - Mile.Qt_x64, D:\Tools\Mile.Qt\x64
  - Mile.Qt_x86, D:\Tools\Mile.Qt\x86
- 使用 Visual Studio 编译本项目
