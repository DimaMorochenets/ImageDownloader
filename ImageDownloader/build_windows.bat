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

cmake --build %build_path%

echo "Run application: (y/n)?"
set /p answer=""
if "%answer%" == "y" ("%build_path%\Debug\ImageDownloader.exe")