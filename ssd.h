#include <stdint.h>

void ssdWrite(int lbaNum, uint32_t data);
uint32_t ssdRead(int lbaNum);
int init();