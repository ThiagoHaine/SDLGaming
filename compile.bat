@ECHO OFF
cls;
SET /P user_input=Qual o nome do arquivo a compilar?(ex:file.c) 
gcc -o game %user_input% -mwindows -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
