#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 10

typedef struct
{
    u_int8_t* rd_ptr;
    u_int8_t* wr_ptr;
    u_int8_t arr[BUFFER_SIZE];
    bool full;
}RingBuffer;

RingBuffer* ringBufferInit()
{
    RingBuffer* rb = malloc(sizeof(RingBuffer));
    rb->rd_ptr  = &(rb->arr[0]);
    rb->wr_ptr = &(rb->arr[0]);
    rb->full = false;
    memset(rb->arr, 0, BUFFER_SIZE);
    return rb;
}

void ringBufferDestroy(RingBuffer* rb)
{
    free(rb);
}

void ringBufferWrite(RingBuffer* rb, u_int8_t elem)
{
    // Check if already full
    if (rb->full)
    {
        // Increment read ptr and check bounds
        rb->rd_ptr++;
        if (rb->rd_ptr > &(rb->arr[BUFFER_SIZE - 1]))
        {
            rb->rd_ptr = &(rb->arr[0]);
        }
    }

    // Write to the buffer
    *(rb->wr_ptr) = elem;

    // Increment write ptr and check bounds
    rb->wr_ptr++;
    if (rb->wr_ptr > &(rb->arr[BUFFER_SIZE - 1]))
    {
        rb->wr_ptr = &(rb->arr[0]);
    }

    // Check if we are now full
    rb->full = (rb->wr_ptr == rb->rd_ptr);
}

u_int8_t ringBufferRead(RingBuffer* rb)
{
    u_int8_t data = 0;
    if (rb->rd_ptr != rb->wr_ptr || rb->full)
    {
        data = *(rb->rd_ptr);
        rb->rd_ptr++;
        if (rb->rd_ptr > &(rb->arr[BUFFER_SIZE - 1]))
        {
            rb->rd_ptr = &(rb->arr[0]);
        }
    }
    rb->full = false;
    return data;
}

void test1()
{
    printf("\nTEST 1 - Single element write/read\n");
    RingBuffer* rb = ringBufferInit();
    ringBufferWrite(rb, 9);
    printf("First element: %d\n", ringBufferRead(rb));
    ringBufferDestroy(rb);
}

void test2()
{
    printf("\nTEST 2 - Write/read full buffer\n");
    RingBuffer* rb = ringBufferInit();

    printf("Before writing buffer full: %d\n", rb->full);
    // fill full buffer
    uint8_t i;
    for (i=0; i<BUFFER_SIZE; i++)
    {
        ringBufferWrite(rb, i);
    }

    printf("After writing buffer full: %d\n", rb->full);

    for (i=0; i<BUFFER_SIZE; i++)
    {
        printf("Read count %d value: %d\n", i, ringBufferRead(rb));
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