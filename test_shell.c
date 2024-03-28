#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "ssd.h"

// 터미널의 너비에 맞게 라인 출력
void print_line(char symbol) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // 터미널 크기 확인
    for (int i = 0; i < w.ws_col; i++) {
        putchar(symbol);
    }
    putchar('\n');
}

// 터미널의 가로 폭을 얻는 함수
int get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // 터미널 크기 확인
    return w.ws_col;
}

// 문자열을 가운데 정렬하여 출력하는 함수
void print_centered(char *text) {
    int terminal_width = get_terminal_width();
    int text_length = strlen(text);
    int padding = (terminal_width - text_length) / 2;

    for (int i = 0; i < padding; i++) {
        putchar(' ');
    }

    printf("%s\n", text);
}

int main() {

    int add = 0;
    ssdRead(1);

    while (1) {

        printf("SSD_Shell >> ");
        char cmd[15];
        scanf("%s", cmd);

        if (strcmp(cmd, "init") == 0) {
            printf("inited whole SSD\n");
            init(); 
        }

        else if (strcmp(cmd, "write") == 0) {
            uint32_t num = 0;
            scanf("%d", &add);
            scanf("%X", &num);
            ssdWrite(add, num);
            printf("writed 0x%08X to LBA %d\n", num, add);
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
            FILE *file;
            char line[200]; // 줄을 저장할 버퍼

            // "##############" 출력
            print_line('#');
            printf("\n");
            print_centered("help\n");
            print_line('#');
            printf("\n");
        
            file = fopen("help.txt", "r");
            if (file == NULL) {
                printf("Cannot open help file.\n");
                return -1;
            }

            // 파일에서 한 줄씩 읽어와서 출력
            int line_number = 0;
            while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        if (line_number % 4 == 0) {
            printf("\033[1m"); 
            printf("%s", line);
            printf("\033[0m"); 
        } else {
            printf("%s", line);
        }
    }
            fclose(file);

            printf("\n\n");
            print_line('#');
            printf("\n");


        }

        else if (strcmp(cmd, "fullwrite") == 0) {
            uint32_t num = 0;
            scanf("%X", &num);
            for (int i = 0; i < 100; i++){
                ssdWrite(i, num);
            }
            printf("whole SSD writed with 0x%08X", num);
        }

        else if (strcmp(cmd, "fullread") == 0) {

            for (int i = 0; i < 100; i++) {
                uint32_t result = ssdRead(i);
                printf("LBA %d data: 0x%08X\n", i, result);
            }
        }




        // test api 작성 부분
        else if (strcmp(cmd, "testapp1") == 0) {
            printf("%s\n", "########## test1 start ##########");
            uint32_t num = 0xBBBBAAAA;

            for (int i = 0; i < 100; i++) {
                ssdWrite(i, num);
            }
            for (int i = 0; i < 100; i++) {
                uint32_t result = ssdRead(i);
                if (num == result)
                    printf("LBA %d correctly checked\n", i);
                else
                    printf("we got problem in LBA %d\n", i);
            }
            printf("%s\n", "########## test1 complete ##########");
        }

        else if (strcmp(cmd, "testapp2") == 0) {
            printf("%s\n", "########## test2 start ##########");
            
            uint32_t temp = 0xAAAABBBB;
            for(int i=0; i<30; i++){
                for (int j = 0; j <= 5; j++) {
                    ssdWrite(j, temp);
                    printf("writed 0x%08X to LBA %d\n", temp, j);
                }   
            }
            
            for (int i = 0; i <= 5; i++) {
                temp = 0x12345678;
                ssdWrite(i, temp);
                printf("writed 0x%08X to LBA %d\n", temp, i);
            }
            for (int i = 0; i <= 5; i++) {
                uint32_t result = ssdRead(i);
                if (temp == result)
                    printf("LBA %d correctly checked\n", i);
                else
                    printf("we got problem in LBA %d\n", i);
            }

            printf("%s\n", "########## test2 complete ##########");
        }

        else {
            printf("INVALID COMMAND\n");
        }
    }


    return 0;
}