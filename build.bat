@echo off
REM Compila todos los .cpp de src/ (usando los headers de include/) en un
REM solo ejecutable bin/programa.exe
if not exist bin mkdir bin
g++ -std=c++14 -Wall -Wextra -Iinclude -o bin\programa.exe src\*.cpp
if %errorlevel% neq 0 (
    echo.
    echo La compilacion fallo.
    exit /b 1
)

REM Copiamos los datos junto al ejecutable para que funcione tanto si lo
REM corres desde la raiz del proyecto (bin\programa.exe) como si haces
REM doble clic directamente sobre el .exe dentro de bin\.
xcopy /y /i /q data bin\data >nul

echo.
echo Compilacion exitosa: bin\programa.exe
echo Puedes ejecutarlo desde la raiz del proyecto o con doble clic dentro de bin\.
