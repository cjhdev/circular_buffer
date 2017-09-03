#include "circular_buffer.h"
#include <string.h>

void InitCircularBuffer(struct circular_buffer *self)
{
    (void)memset(self, 0, sizeof(*self));
}

bool Push(struct circular_buffer *self, uint32_t value)
{
    bool retval = false;
    
    if(!Full(self)){
    
        self->buffer[self->count % MaximumSize(self)] = value;
        self->size++;
        self->count++;
        retval = true;
    }
    
    return retval;
}

bool Pop(struct circular_buffer *self, uint32_t *value)
{
    bool retval = false;
    
    if(!Empty(self)){
        
        *value = self->buffer[(self->count - self->size) % MaximumSize(self)];
        self->size--;
        retval = true;
    }
    
    return retval;
}

bool Peek(const struct circular_buffer *self, uint32_t *value)
{
    bool retval = false;
    
    if(!Empty(self)){
        
        *value = self->buffer[(self->count - self->size) % MaximumSize(self)];
        retval = true;
    }
    
    return retval;    
}

size_t CurrentSize(const struct circular_buffer *self)
{
    return self->size;
}

size_t MaximumSize(const struct circular_buffer *self)
{
    return sizeof(self->buffer)/sizeof(*self->buffer);
}

bool Empty(const struct circular_buffer *self)
{
    return (self->size == 0U);
}

bool Full(const struct circular_buffer *self)
{
    return (self->size == MaximumSize(self));
}


