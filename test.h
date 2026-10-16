#include <stdio.h>
#include "bitwise.h"

void test_1()
{
    printf("TEST 1 - LOWER MASK\n");

    uint32_t mask;
    uint8_t width;

    int itr = 32;
    for (width=0; width<=itr; width++)
    {
        mask = lower_mask(width);
        printf("width: %d\tmask: %032b\n", width, mask);
    }

    printf("\n");
}

void test_2()
{
    printf("TEST 2 - VAILID FIELD\n");

    uint8_t start;
    uint8_t width;
    bool valid;

    start = 0;
    width = 0;
    valid = field_valid(start, width);
    printf("start: %d, width: %d\tvalid:%d\n", start, width, valid);

    start = 0;
    width = 1;
    valid = field_valid(start, width);
    printf("start: %d, width: %d\tvalid:%d\n", start, width, valid);

    start = 0;
    width = 32;
    valid = field_valid(start, width);
    printf("start: %d, width: %d\tvalid:%d\n", start, width, valid);

    start = 1;
    width = 32;
    valid = field_valid(start, width);
    printf("start: %d, width: %d\tvalid:%d\n", start, width, valid);

    start = 1;
    width = 50;
    valid = field_valid(start, width);
    printf("start: %d, width: %d\tvalid:%d\n", start, width, valid);

    start = 5;
    width = 10;
    valid = field_valid(start, width);
    printf("start: %d, width: %d\tvalid:%d\n", start, width, valid);

    printf("\n");
}

void test_3()
{
    printf("TEST 3 - INSERT FIELD\n");

    uint32_t reg;
    uint8_t pos;
    uint8_t width;
    uint32_t value;
    uint32_t updated_reg;

    reg = 0x00000000;
    pos = 4;
    width = 8;
    value = 0xFF;
    updated_reg = insert_bits(reg, pos, width, value);
    printf("reg: %032b pos: %d width: %d value: %d result: %032b\n", reg, pos, width, value, updated_reg);

    printf("\n");
}
