#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void ssdWrite(int lbaNum, uint32_t data){
    FILE *file;
    file = fopen("nand.txt", "r+t"); // 파일 열기
    if (file == NULL) {
        perror("we don't have file: nand.txt\n");
        return;
    } 

    // ssdWrite 실행
    char line[15]; // 한 줄을 쓰기 위함
    int targetLine = lbaNum;
    long offset = (lbaNum) * (13+1) + 3;      // 원하는 줄 번호 x 각 줄의 길이 + 16진수부분만 바꾸기 위해 3추가
    // long offset = (lbaNum-1)) * (11+2);      // 윈도우에선 \r\n이 붙어서 추가 고려해야한다.
    fseek(file, offset, SEEK_SET);              // 파일의 특정 위치로 이동


    // 바꾸기
    fprintf(file, "0x%08X\n", data);

    fclose(file); // 파일 닫기
    return;
}

uint32_t ssdRead(int lbaNum){
    
    // nand에서 읽고 result에 쓰기기
    FILE *nandFile;
    nandFile = fopen("nand.txt", "r"); // 파일 열기

    if (nandFile == NULL) {
        perror("we don't have file: nand.txt\n");
        return EXIT_FAILURE;
    }

    FILE *resultFile;
    resultFile = fopen("result.txt", "w"); // 파일 열기

    if (resultFile == NULL) {
        perror("we don't have file: result.txt\n");
        return EXIT_FAILURE;
    }

 
    char line[15]; // 한 줄을 쓰기 위함
    int targetLine = lbaNum;
    long offset = (lbaNum) * (13+1);              // 각 줄의 길이 x 원하는 줄 번호
    // long offset = (lbaNum-1)) * (11+2);          // 윈도우에선 \r\n이 붙어서 13으로 해줘야 한다.
    fseek(nandFile, offset, SEEK_SET);              // 파일의 특정 위치로 이동

    char* token;
    uint32_t output;
    
    if (fgets(line, sizeof(line), nandFile) != NULL) {
        //printf("%s\n", line);
        token = strtok(line, "|");
        token = strtok(NULL, "|");
        output = strtol(token, NULL, 16);
        fprintf(resultFile, "0x%08X", output);
        
    }

    fclose(nandFile); // 파일 닫기
    fclose(resultFile); // 파일 닫기

    return output;
}


int init() {
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

