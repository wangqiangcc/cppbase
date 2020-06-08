@echo off
"C:\Program Files\CMake\bin\cmake.exe" -G "Visual Studio 12 2013" ..\src -B vs2013
"%VS120COMNTOOLS%\..\IDE\devenv" "vs2013\base.sln" /Rebuild "Release|win32" /Project "base"
pause
