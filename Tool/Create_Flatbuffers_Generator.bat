setlocal
@echo off

rem ReadMe:https://google.github.io/flatbuffers/flatbuffers_guide_using_schema_compiler.html

set flatc=flatbuffers/flatc.exe
set flat_path=../PacketStructure/

set MProjectServerPath=../MProjectServer/CommonLibrary/Packet
set MProjectTestClientPath=../MProjectServer/TestClient/Packet
set MProjectClientPath=../MProjectClient/MProjectClient/Assets/Client/Scripts/Packet

FOR /D /R "%flat_path%Cpp" %%A IN (*) DO rd /S /Q %%A
@rem for /R "%flat_path%Cpp" %%V IN (*) DO del %%V
for /R "%flat_path%Fbs" %%V IN (*.fbs) DO IF %%V GTR 0 (
    call "%flatc%" --cpp -o "%flat_path%/Cpp" %%V
)

FOR /D /R "%flat_path%Net" %%A IN (*) DO rd /S /Q %%A
@rem for /R "%flat_path%Net" %%V IN (*) DO del %%V
for /R "%flat_path%Fbs" %%V IN (*.fbs) DO IF %%V GTR 0 (
    call "%flatc%" --csharp -o "%flat_path%/Net" %%V
)

echo MProject Server Generate...
echo Cpp Copy Start.. to "%MProjectServerPath%"
FOR /D /R "%MProjectServerPath%/" %%A IN (*) DO rd /S /Q %%A
xcopy "%flat_path%Cpp" "%MProjectServerPath%" /m /y /d /e /s
echo Cpp Copy Complete..

echo.
echo. 

echo MProject TestClient Generate...
echo CSharp Copy Start.. to "%MProjectTestClientPath%"
FOR /D /R "%MProjectTestClientPath%/" %%A IN (*) DO rd /S /Q %%A
xcopy "%flat_path%Net/MProject" "%MProjectTestClientPath%" /m /y /d /e /s
echo CSharp Copy Complete..

echo.
echo. 

if exist %MProjectClientPath% (
    FOR /D /R "%MProjectClientPath%/" %%A IN (*) DO rd /S /Q %%A
    xcopy "%MProjectTestClientPath%" "%MProjectClientPath%" /m /y /d /e /s
) else (
    echo not exist MProject Client Generate...
    echo please Build.sh run.
)

echo.
echo.

echo Generate ALL Complete!

pause