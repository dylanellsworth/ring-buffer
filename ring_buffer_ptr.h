#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 10

typedef struct
{
    uint8_t* rd_ptr;
    uint8_t* wr_ptr;
    uint8_t arr[BUFFER_SIZE];
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

void ringBufferWrite(RingBuffer* rb, uint8_t elem)
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

uint8_t ringBufferRead(RingBuffer* rb)
{
    uint8_t data = 0;
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