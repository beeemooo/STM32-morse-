#include "ring_buffer.h"


static uint16_t inc(uint16_t idx) {
    return (idx + 1) % RB_SIZE;
}


void rb_init(RingBuffer *rb)
{
    rb->head = rb->tail = 0;
}


bool rb_is_empty(const RingBuffer *rb)
{
    return rb->head == rb->tail;
}


bool rb_is_full(const RingBuffer *rb)
{
    return inc(rb->head) == rb->tail;
}


uint16_t rb_size(const RingBuffer *rb)
{
    if (rb->head >= rb->tail)
        return rb->head - rb->tail;
    else
        return RB_SIZE - (rb->tail - rb->head);
}


bool rb_push(RingBuffer *rb, uint8_t byte)
{
    uint16_t next = inc(rb->head);
    if (next == rb->tail)       // full
        return false;

    rb->buf[rb->head] = byte;
    rb->head = next;
    return true;
}


bool rb_pop(RingBuffer *rb, uint8_t *byte)
{
    if (rb_is_empty(rb))
        return false;

    *byte   = rb->buf[rb->tail];
    rb->tail = inc(rb->tail);
    return true;
}


bool rb_peek(RingBuffer *rb, uint8_t *byte)
{
    if (rb_is_empty(rb))
        return false;

    *byte = rb->buf[rb->tail];
    return true;
}


void rb_flush(RingBuffer *rb)
{
    rb->head = rb->tail = 0;
}
