set app=Diskra
gcc -o %app%.exe main.c
title %app%
echo off
cls
%app%.exe
pause