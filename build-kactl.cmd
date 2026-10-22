@echo off
setlocal
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0build-kactl.ps1" %*
set "buildResult=%ERRORLEVEL%"
echo.
if not "%buildResult%"=="0" echo Build failed. Check the error above and the logs in build.
pause
exit /b %buildResult%
