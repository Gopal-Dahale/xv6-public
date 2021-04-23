/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "uspinlock.h"

// define an array of NLOCK uspinlocks
uspinlock_t uspinlocks[NLOCK];

int uspinlock_init(void)
{
  // Initialize all locks to unlocked state
  int i;
  for (i = 0; i < NLOCK; i++)
    uspinlocks[i].locked = 0;
  return 0;
}

int uspinlock_acquire(int index)
{
  // The xchg is atomic.
  while (xchg(&uspinlocks[index].locked, 1) != 0)
    ;
  return 0;
}

int uspinlock_release(int index)
{
  uspinlocks[index].locked = 0;
  return 0;
}

int uspinlock_holding(int index)
{
  // Return 0 if lock is free, 1 if lock is held
  int r;
  r = uspinlocks[index].locked;
  return r;
}
/*----------xv6 sync lock end----------*/
