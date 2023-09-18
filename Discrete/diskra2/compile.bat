set app=Diskra2
gcc -o %app%.exe main.c
title %app%
echo off
cls
%app%.exe
pause