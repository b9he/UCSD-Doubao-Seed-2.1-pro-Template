@echo off
setlocal
cd /d "%~dp0"
set "PATH=%~dp0..\.tools\bin;%~dp0..\.tools\TinyTeX\bin\windows;D:\Program Files (x86)\Git\usr\bin;%PATH%"
set "TEXINPUTS=.;content/tex/;"
set "PYTHONUTF8=1"
set "PYTHONIOENCODING=utf-8"
set "max_print_line=1048576"
echo KACTL build environment ready.
echo Run: powershell -NoProfile -ExecutionPolicy Bypass -File .\build-kactl.ps1
echo Or: make kactl
cmd.exe /k
