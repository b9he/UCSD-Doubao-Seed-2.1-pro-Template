# KACTL 本地修改与编译

项目：`D:\Template\kactl\kactl`

## 最常用的方法

修改并保存源文件，然后双击项目目录里的 `build-kactl.cmd`。

看到 `Build succeeded` 后，打开同目录下的 `kactl.pdf`。完整编译会生成测试说明 PDF，并将主文档编译两遍以更新目录。编译窗口最后会保留，按任意键关闭。

如果 PDF 被阅读器锁住而无法覆盖，请先关闭阅读器中的 PDF，再编译。

## 在 PowerShell 中编译

```powershell
Set-Location 'D:\Template\kactl\kactl'
powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\build-kactl.ps1
```

只想快速预览时，在最后加上 `-Fast`。快速模式只编译主文档一次，目录可能需要下次完整编译才会更新。

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File .\build-kactl.ps1 -Fast
```

## 用原来的 make 命令

双击项目目录里的 `kactl-terminal.cmd`，然后在打开的终端里执行：

```text
make kactl
```

这个专用终端会配置 Python、LaTeX、Make 和 Unix 工具路径，并修正 Windows 的 TEXINPUTS 分隔符。

## 修改和移除代码段

- 改算法代码：编辑 `D:\Template\kactl\kactl\content` 对应分类下的 `.h` 或 `.cpp` 文件。
- 控制 PDF 收录内容：编辑对应分类的 `chapter.tex`。
- 修改章节顺序、队名或封面：编辑 `D:\Template\kactl\kactl\content\kactl.tex`。

例如，在 `D:\Template\kactl\kactl\content\data-structures\chapter.tex` 中，把

```tex
\kactlimport{FenwickTree.h}
```

改成

```tex
% \kactlimport{FenwickTree.h}
```

保存后重新编译，树状数组就不再单独出现在 PDF 中。保留 `.h` 文件可以让依赖它的其他算法继续使用。

## 已配置的工具

- 独立 TinyTeX / TeX Live 2026：`D:\Template\kactl\.tools\TinyTeX`。
- 复用 Python 3.12.4：`D:\anaconda3\python.exe`。
- 复用 GNU Make 4.4.1：`D:\mingw64\bin\mingw32-make.exe`。
- 复用 Git 的 Unix 工具：`D:\Program Files (x86)\Git\usr\bin`。
- 兼容入口：`D:\Template\kactl\.tools\bin`。

Python 预处理脚本只需要标准库；无需额外安装 pip 库。编译脚本自动启用 UTF-8。

请保留上述目录。若迁移项目到其他电脑，需要相应调整脚本中的 Python、Make 和 Git 路径。

## 日志和补装 LaTeX 包

编译失败时，查看 `D:\Template\kactl\kactl\build\kactl-pass1-console.log`、`kactl-pass2-console.log` 或 `test-session-console.log`。

以后增加新的 LaTeX 功能、遇到缺包提示时，在专用终端中执行：

```text
tlmgr install 包名
```

首次配置前的主 PDF 备份：`D:\Template\kactl\kactl\build\kactl-before-windows-setup.pdf`。

## 官方来源

- TinyTeX：https://github.com/rstudio/tinytex-releases
- 已下载安装包：`TinyTeX-1-windows-v2026.10.exe`。
- 安装包 SHA-256：`36c329c644683d981a668419d13c8804696e2816ae4d287ad755788fee231a31`，已与官方发布记录核对。
- LaTeX 包镜像：https://ctan.math.illinois.edu/systems/texlive/tlnet
