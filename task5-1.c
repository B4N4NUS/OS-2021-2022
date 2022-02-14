#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char *buff = 0;
    size_t length;
    FILE *file = fopen("myfile", "rb");

    if (file) {
        // Перемещаем указатель позиции в потоке.
        fseek(file, 0, SEEK_END);
        // Вычисляем длину строки в файле.
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        // Получаем инфу о кол-ве байт на буфер.
        buff = malloc(length);
        if (buff) {
            fread(buff, 1, length, file);
            printf("Successfully opened:\n%s", buff);
        } else {
            printf("ERROR\nFile is empty!");
        }
        fclose(file);
    } else {
        printf("ERROR\nCan\'t open file!");
    }
    return 0;
}
