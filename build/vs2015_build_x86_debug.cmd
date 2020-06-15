@echo off
"C:\Program Files\CMake\bin\cmake.exe" -G "Visual Studio 14 2015" ..\src -B vs2015
"%VS140COMNTOOLS%\..\IDE\devenv" "vs2015\base.sln" /Rebuild "Debug|win32" /Project "base"
md lib
copy /y vs2015\lib\Debug\base.dll lib\base.dll
copy /y vs2015\lib\Debug\base.lib lib\base.lib
pause
