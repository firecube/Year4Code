@echo off

REM remove automatic created obj folder
rd obj /S /Q >nul 2>&1

PATH=%PATH%;C:\Espressif\xtensa-lx106-elf\bin;C:\tools\mingw64\bin;C:\tools\mingw64\msys\1.0\bin
make -f Makefile %1 %2 %3 %4 %5