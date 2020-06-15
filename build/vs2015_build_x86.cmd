@echo off
"C:\Program Files\CMake\bin\cmake.exe" -G "Visual Studio 14 2015" ..\src -B vs2015
"%VS140COMNTOOLS%\..\IDE\devenv" "vs2015\base.sln" /Rebuild "Release|win32" /Project "base"
md lib
copy /y vs2015\lib\Release\base.dll lib\base.dll
copy /y vs2015\lib\Release\base.lib lib\base.lib
pause
