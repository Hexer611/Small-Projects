set sdlincpath="C:\Users\Administrator\Downloads\SDL3-devel-3.2.0-VC\SDL3-3.2.0\include\SDL3"
set sdllibpath="C:\Users\Administrator\Downloads\SDL3-devel-3.2.0-VC\SDL3-3.2.0\lib\x64"

gcc My_Physic_Engine.cpp -I %sdlincpath% -I %sdlincpath%\.. -L %sdllibpath% -l sdl3

xcopy /S /Q /Y /F %sdllibpath%\sdl3.dll sdl3.dll

.\a.exe