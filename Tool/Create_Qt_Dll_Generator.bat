setlocal

rem QT windeployqt.exe
set qt_path=C:\Qt\6.3.0\msvc2019_64\bin
set debug=Debug
set release=Release
set program_path=..\Result\MProjectServer\x64\%debug%\MProjectServer.exe

call %qt_path%\windeployqt.exe %program_path%