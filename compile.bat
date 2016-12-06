@echo off

set PATH=C:\MinGW\bin;%PATH%
mingw32-make -f Makefile.win clean
mingw32-make -f Makefile.win

pause
