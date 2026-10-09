#include <stdlib.h>
#include "ring_buffer.h"

void test1()
{
    printf("\nTEST 1 - Single element write/read\n");
    RingBuffer* rb = ringBufferInit();
    ringBufferWrite(rb, 9);
    printf("Count: %d\n", ringBufferCount(rb));
    printf("Read first element: %d\n", ringBufferRead(rb));
    printf("Count: %d\n", ringBufferCount(rb));
    ringBufferDestroy(rb);
}

void test2()
{
    printf("\nTEST 2 - Write/read full buffer\n");
    RingBuffer* rb = ringBufferInit();

    printf("Before writing buffer empty status: %d\n", ringBufferEmpty(rb));
    // fill full buffer
    uint8_t i;
    for (i=0; i<BUFFER_SIZE; i++)
    {
        ringBufferWrite(rb, i);
        printf("Writing element %d - count status: %d\n", i, ringBufferCount(rb));
    }

    printf("After writing buffer full: %d\n", ringBufferFull(rb));

    for (i=0; i<BUFFER_SIZE; i++)
    {
        printf("Read element %d value: %d buffer count:%d\n", i, ringBufferRead(rb), ringBufferCount(rb));
    }

    printf("After reading buffer full: %d\n", rb->full);

    ringBufferDestroy(rb);
}

int main(){
    // Test 1: Write single element 
    test1();

    // Test 2: Write full buffer
    test2();

    return 0;
}