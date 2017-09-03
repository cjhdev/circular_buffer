#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#ifndef CIRCULAR_BUFFER_SIZE

    /** default FIFO maximum size */
    #define CIRCULAR_BUFFER_SIZE 42U    

#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** circular buffer state */
struct circular_buffer {
    
    uint32_t buffer[CIRCULAR_BUFFER_SIZE];  /**< FIFO buffer */
    size_t size;                            /**< number of values in FIFO */
    size_t count;                           /**< increments by number of values pushed; never decrements */
};

/** Initialise a buffer
 * 
 * @note not required if instance is stored in .bss
 * 
 * @param[in] self
 * */
void InitCircularBuffer(struct circular_buffer *self);

/** Push value to FIFO
 * 
 * @param[in] self
 * @param[in] value
 * 
 * @return true if successful
 * */
bool Push(struct circular_buffer *self, uint32_t value);

/** Pop value from FIFO
 * 
 * @param[in] self
 * @param[out] value
 * 
 * @return true if successful
 * */
bool Pop(struct circular_buffer *self, uint32_t *value);

/** Peek at the next to be popped value on the FIFO
 * 
 * @note similar to Pop but will not remove value from FIFO
 * 
 * @param[in] self
 * @param[in] value
 * 
 * @return true if successful
 * */
bool Peek(const struct circular_buffer *self, uint32_t *value);

/** Return number of values currently in FIFO
 * 
 * @param[in] self
 * 
 * @return current size
 * */
size_t CurrentSize(const struct circular_buffer *self);

/** Return maximum number of values that can be held by FIFO
 * 
 * @param[in] self
 * 
 * @return maximum size
 * */
size_t MaximumSize(const struct circular_buffer *self);

/** Return true if FIFO empty
 * 
 * @param[in] self
 * 
 * @return true if FIFO empty
 * 
 * */
bool Empty(const struct circular_buffer *self);

/** Return true if FIFO full
 * 
 * @param[in] self
 * 
 * @return true if FIFO is full
 * 
 * */
bool Full(const struct circular_buffer *self);

#endif
