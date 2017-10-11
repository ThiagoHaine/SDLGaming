clear;
echo "Qual o nome do arquivo a compilar?(ex:file.c)"
read user_input;
gcc -o ${user_input%??} ${user_input} -lSDL -lSDL_image
#./game
