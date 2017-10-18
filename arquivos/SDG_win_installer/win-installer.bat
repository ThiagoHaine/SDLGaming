@echo off  
pushd "%~dp0"
move %cd%\windows\* C:\Windows\
move %cd%\mingw-files\* C:\MinGW\
setx Path "%Path%;C:\MinGW\bin" /m
pause