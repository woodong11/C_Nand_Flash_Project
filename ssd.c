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
    long offset = (lbaNum-1) * (11+3) + 3;      // 원하는 줄 번호 x 각 줄의 길이 + 16진수부분만 바꾸기 위해 3추가
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
    long offset = (lbaNum-1) * (11+3);              // 각 줄의 길이 x 원하는 줄 번호
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


// //test용 main
// int main(int argc, int* argv[]) {

//     ssdWrite(1, 0x11111111);
//     // uint32_t output1 = ssdRead(4);
//     // printf("0x%08x\n", output1 );
//     // ssdWrite(55, 0x11111111);
//     // uint32_t output2 = ssdRead(66);
//     // printf("0x%08x\n", output2 );

//     return 0;
// }
