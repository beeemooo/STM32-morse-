#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

//Ring buffer size
#define RB_SIZE 128          

/* Ring buffer struct */
typedef struct {
    uint8_t buf[RB_SIZE];
    volatile uint16_t head;  
    volatile uint16_t tail;  
} RingBuffer;

/* API */
void     rb_init   (RingBuffer *rb);
bool     rb_is_empty(const RingBuffer *rb);
bool     rb_is_full (const RingBuffer *rb);
uint16_t rb_size    (const RingBuffer *rb);

bool     rb_push    (RingBuffer *rb, uint8_t byte);    
bool     rb_pop     (RingBuffer *rb, uint8_t *byte);  
bool     rb_peek    (RingBuffer *rb, uint8_t *byte);  
void     rb_flush   (RingBuffer *rb);                 

#endif /* RING_BUFFER_H */
