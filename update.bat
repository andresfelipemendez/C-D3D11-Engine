REM @echo off
cd Engine
set sourceFiles= ..\Engine\Engine.c ..\Engine\EntityManager.c ..\Engine\SystemsManager.c ..\Engine\Systems\InputSystem.c ..\Engine\Systems\RenderingSystem.c
cl /w /nologo %sourceFiles% /LD 
cd ..
