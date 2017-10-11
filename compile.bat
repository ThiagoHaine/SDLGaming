@ECHO OFF
cls;
SET /P user_input=Qual o nome do arquivo a compilar?(ex:file.c) 
gcc -o game %user_input% -lSDL -lSDL_image
