@echo off
REM Compila o Mini Compilador direto com g++ (sem precisar do CMake)
if not exist build mkdir build
g++ -std=c++17 -Wall -Wextra -Iinclude src\*.cpp -o build\aula6.exe
if %errorlevel% neq 0 (
    echo Falha na compilacao.
    exit /b 1
)
echo Compilado: build\aula6.exe
