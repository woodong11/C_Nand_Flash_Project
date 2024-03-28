#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include "ssd.h"

int main() {

    int add = 0;
    ssdRead(1);

    while (1) {

        printf("SSD_shell >> ");
        char cmd[15];
        scanf("%s", cmd);

        if (strcmp(cmd, "write") == 0) {
            uint32_t num = 0;
            scanf("%d", &add);
            scanf("%X", &num);
            ssdWrite(add, num);
        }

        else if (strcmp(cmd, "read") == 0) {
            scanf("%d", &add);
            uint32_t result = ssdRead(add);
            printf("0x%08X\n", result);
        }

        else if (strcmp(cmd, "exit") == 0) {
            printf("SSD test shell terminated");
            break;
        }

        else if (strcmp(cmd, "help") == 0) {
            printf("write 명령어 : 원하는 주소에 저장할 값 저장\n사용법 : write, 저장하고 싶은 주소, 저장하고자 하는 값\n");
            printf("read 명령어 : 원하는 주소의 저장값 읽음\n사용법 : read, 보고싶은 주소\n");
            printf("exit 명령어 : 종료\n사용법 : exit\n");
            printf("fullwrite 명령어 : 전체에 원하는 값 저장\n사용법 : fullwrite, 저장하고자 하는 값\n");
            printf("fullread 명령어 : 전체 주소의 저장값 읽음\n사용법 : fullread\n");
        }

        else if (strcmp(cmd, "fullwrite") == 0) {
            uint32_t num = 0;
            scanf("%X", &num);
            for (int i = 1; i <= 100; i++){
                ssdWrite(i, num);
            }
        }

        else if (strcmp(cmd, "fullread") == 0) {

            for (int i = 1; i <= 100; i++) {
                uint32_t result = ssdRead(i);
                printf("LBA %d data: 0x%08X\n", i, result);
            }
        }

        else {
            printf("INVALID COMMAND\n");
        }
    }


    return 0;
}