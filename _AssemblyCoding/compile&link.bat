set nasmpath="C:/Users/erdem/Downloads/nasm-2.16.03-win64/nasm-2.16.03/nasm.exe"
set gccpath="C:/Users/erdem/Downloads/gcc-14.2.0-no-debug/bin/gcc.exe"

%nasmpath% -fwin64 erdem.s
%gccpath% main.c erdem.obj

::nasm -felf64 erdem.s
::gcc main.c erdem.o
