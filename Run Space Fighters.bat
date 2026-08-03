@echo off
setlocal

set "GAME_DIR=%~dp0Space_Fighters_(SFML)"
set "GAME_EXE=%GAME_DIR%\build\bin\SpaceFighters.exe"

if not exist "%GAME_EXE%" (
    echo Space Fighters has not been built yet.
    echo Run: cmake -S "Space_Fighters_(SFML)" -B "Space_Fighters_(SFML)\build"
    echo Then: cmake --build "Space_Fighters_(SFML)\build" --config Debug
    exit /b 1
)

cd /d "%GAME_DIR%"
"%GAME_EXE%"
