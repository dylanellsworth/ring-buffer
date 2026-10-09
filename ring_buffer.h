#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 10

typedef struct
{
    size_t head;
    size_t tail;
    uint8_t arr[BUFFER_SIZE];
    bool full;
}RingBuffer;

RingBuffer* ringBufferInit()
{
    RingBuffer* rb = malloc(sizeof(RingBuffer));
    rb->head  = 0;
    rb->tail = 0;
    rb->full = false;
    memset(rb->arr, 0, BUFFER_SIZE);
    return rb;
}

RingBuffer* ringBufferReset(RingBuffer* rb)
{
    rb->head  = 0;
    rb->tail = 0;
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
        rb->head++;
        if (rb->head > (BUFFER_SIZE - 1))
        {
            rb->head = 0;
        }
    }

    // Write to the buffer
    rb->arr[rb->tail] = elem;

    // Increment write ptr and check bounds
    rb->tail++;
    if (rb->tail >(BUFFER_SIZE - 1))
    {
        rb->tail = 0;
    }

    // Check if we are now full
    rb->full = (rb->tail == rb->head);
}

uint8_t ringBufferRead(RingBuffer* rb)
{
    uint8_t data = 0;
    if (rb->head != rb->tail || rb->full)
    {
        data = rb->arr[rb->head];
        rb->head++;
        if (rb->head > (BUFFER_SIZE - 1))
        {
            rb->head = 0;
        }
    }
    rb->full = false;
    return data;
}

bool ringBufferFull(RingBuffer* rb)
{
    return rb->full;
}

bool ringBufferEmpty(RingBuffer* rb)
{
    return (!rb->full && (rb->tail == rb->head));
}

uint8_t ringBufferCount(RingBuffer* rb)
{
    uint8_t count = 0;
    if (rb->full)
    {
        count = BUFFER_SIZE;
    }
    else if(rb->tail == rb->head)
    {
        count = 0;
    }
    else if (rb->tail > rb->head)
    {
        count = rb->tail - rb->head;
    }
    else
    {
        count = BUFFER_SIZE - (rb->head - rb->tail);
    }
    return count;
}
