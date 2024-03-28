#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("nand.txt", "w"); // 파일을 쓰기 모드로 열기

    if (file == NULL) {
        perror("we don't have file: nand.txt\n");
        return -1;
    }

    for (int i = 0; i < 100; i++) {
        fprintf(file, "%02d|0x00000000\n", i); // 파일에 내용 쓰기
    }

    fclose(file); // 파일 닫기
    return 0;
}