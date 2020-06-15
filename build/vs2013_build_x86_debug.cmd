@echo off
"C:\Program Files\CMake\bin\cmake.exe" -G "Visual Studio 12 2013" ..\src -B vs2013
"%VS120COMNTOOLS%\..\IDE\devenv" "vs2013\base.sln" /Rebuild "Debug|win32" /Project "base"
md lib
copy /y vs2013\lib\Debug\base.dll lib\base.dll
copy /y vs2013\lib\Debug\base.lib lib\base.lib
pause
