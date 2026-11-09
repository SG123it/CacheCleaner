@echo off

cmake -B build -G "MinGW Makefiles"
cmake --build build
"C:\Program Files\Inno Setup 6\Compil32.exe" /cc "setup.iss"

pause