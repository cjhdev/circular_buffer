#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include "cmocka.h"

#include "circular_buffer.h"

#include <string.h>

static int setup(void **user)
{
    static struct circular_buffer state;
    InitCircularBuffer(&state);
    *user = (void *)&state;
    
    return 0;
}

/* All in one test that provides 100% code coverage
 * 
 * - Verify that buffer can take the maximum number of entries and no more
 * - Verify that entire contents is returned in FIFO order
 * - Verify that buffer will not pop when empty
 * - Verify CurrentSize()
 * - Verify MaximumSize()
 * - Verify that Peek() works like Pop() but without affecting state of the buffer
 * - Verify that the buffer can wrap
 * 
 * */
static void test_Push_then_Pop_max(void **user)
{
    struct circular_buffer *self = (struct circular_buffer *)(*user);
    size_t i;
    uint32_t value;
    size_t maxSize = MaximumSize(self);         /* get the maximum size of the FIFO */
    
    assert_true(Empty(self));                   /* FIFO will start empty */
    
    /* fill the buffer to its maximum size */
    for(i=0U; i < maxSize; i++){
    
        assert_int_equal(i, CurrentSize(self)); /* current size will match i */
        assert_true(Push(self, i));             /* we should be able to push until maximum size has been reached */
        
        assert_true(Peek(self, &value));        /* we should be able to Peek */
        assert_int_equal(0, value);             /* the peeked value will be the first value pushed (0) */ 
    }
    
    assert_int_equal(maxSize, CurrentSize(self));   /* at this point current size will be the maximum size */
    assert_true(Full(self));                        /* in other words, the fifo is full */
    
    assert_false(Push(self, i));                    /* should not be able to push a full fifo */       
    
    /* pop the FIFO until empty */
    for(i=0U; i < maxSize; i++){
        
        assert_true(Peek(self, &value));            /* we should be able to Peek */
        assert_int_equal(i, value);                 /* the peeked values will be i..maxSize (since that is the the order they were pushed) */
        
        assert_int_equal(maxSize - i, CurrentSize(self));   /* current size will decrease from maxSize for each iteration */   
        assert_true(Pop(self, &value));                     /* we should be able to Pop */
        assert_int_equal(i, value);                         /* Popped value will be the same as the Peeked value */
    }
    
    assert_int_equal(0, CurrentSize(self));         /* FIFO should now be empty */
    assert_true(Empty(self));                       /* as above */
    
    assert_false(Pop(self, &value));                /* should not be able to pop an empty FIFO */ 
    
    /* repeat to check wrapping works */
    for(i=0U; i < maxSize; i++){
    
        assert_true(Push(self, i));
    }
    for(i=0U; i < maxSize; i++){
    
        assert_true(Pop(self, &value));
        assert_int_equal(i, value);
    }
}

int main(int argc, const char **argv)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(test_Push_then_Pop_max, setup),
    };

    return cmocka_run_group_tests(tests, setup, NULL);
}
