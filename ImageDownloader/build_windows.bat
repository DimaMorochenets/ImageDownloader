@echo off

set script_path=%~dp0
set build_path=%script_path%..\build

cmake -DCMAKE_BUILD_TYPE=Release %script_path%

if exist %build_path% (
    cmake -B %build_path%
    cmake --build %build_path% --target clean
) else (
    mkdir %build_path%
    cmake -B %build_path%
)

cmake --build %build_path% --parallel %NUMBER_OF_PROCESSORS%

::echo Run application: (y/n)?
::set /p answer=""
::if "%answer%" == "y" ("%build_path%\Debug\ImageDownloader.exe")

C:\Qt\6.3.1\msvc2019_64\bin\windeployqt.exe --qmldir . --release "%build_path%\Debug\ImageDownloader.exe"

"%build_path%\Debug\ImageDownloader.exe"