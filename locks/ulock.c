#include "ulock.h"
#include "x86.h"
#include "defs.h"

void init_lock(struct lock_t *s) {
    s->locked = 0;
}

void 
acquire_lock(struct lock_t *s) 
{
    /* Your Code */
    // pushcli(); // disable interrupts to avoid deadlock.
    // if(holding(lk))
    //     panic("acquire");

  // The xchg is atomic.
    while(xchg(&s->locked, 1) != 0)
    {
        ;
    }

  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that the critical section's memory
  // references happen after the lock is acquired.
    __sync_synchronize();

//   // Record info about lock acquisition for debugging.
//     lk->cpu = mycpu();
//     getcallerpcs(&lk, lk->pcs);
}

void 
release_lock(struct lock_t *s) 
{
    /* Your Code */
    // if(!holding(lk))
    // panic("release");

  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that all the stores in the critical
  // section are visible to other cores before the lock is released.
  // Both the C compiler and the hardware may re-order loads and
  // stores; __sync_synchronize() tells them both not to.
  __sync_synchronize();

  // Release the lock, equivalent to lk->locked = 0.
  // This code can't use a C assignment, since it might
  // not be atomic. A real OS would use C atomics here.
  asm volatile("movl $0, %0" : "+m" (s->locked) : );

//   popcli();
}


void 
init_sem(struct sem_t *s, int initval)
{
    /* Your Code */
    init_lock(&s->lk);  // initialising the lock
    s->val = initval;   // iniitalising the value to be stored in the semaphore
}

void
up_sem(struct sem_t *s) 
{
    /* Your Code */
    acquire_lock(&s->lk);   // acquiring the lock
    s->val += 1;            // incrementing the value by 1
    signal_sem((void*)s);   // signalling all the threads to wakeup
    release_lock(&s->lk);   // releasing the lock
}

void 
down_sem(struct sem_t *s) 
{
    /* Your Code */
    acquire_lock(&s->lk);   // acquiring the lock
    while(s->val <= 0)
    {
        block_sem((void*)s);    // making this thread go to sleep until the value becomes > 0
    }
    s->val -= 1;    // decrementing the value by 1
    release_lock(&s->lk);    // releasing the lock
}
