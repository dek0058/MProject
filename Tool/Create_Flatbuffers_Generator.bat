setlocal
@echo off

rem ReadMe:https://google.github.io/flatbuffers/flatbuffers_guide_using_schema_compiler.html

set flatc=flatbuffers/flatc.exe
set flat_path=../PacketStructure/

for /R "%flat_path%/Cpp" %%V IN (*) DO del %%V
for /R "%flat_path%/Fbs" %%V IN (*.fbs) DO IF %%V GTR 0 (
    call "%flatc%" --cpp -o "%flat_path%/Cpp" %%V
)

for /R "%flat_path%/Net" %%V IN (*) DO del %%V
for /R "%flat_path%/Fbs" %%V IN (*.fbs) DO IF %%V GTR 0 (
    call "%flatc%" --csharp -o "%flat_path%/Net" %%V
)

