@echo off
start "" "C:\Program Files (x86)\Notepad++\notepad++.exe" src/*.cpp src/*.h
start compile_and_run.bat
start SideBySide.vbs