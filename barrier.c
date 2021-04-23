/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "spinlock.h"
#include "defs.h"
#include "barrier.h"

//define any variables needed here
typedef struct __barrier_t
{
  int n;              // Number of processes
  int c;              // Number of invokes
  int chan;           // Channel on which processes sleep
  struct spinlock lk; // SpinLock
} barrier_t;

barrier_t barrier;

int barrier_init(int n)
{
  barrier.n = n;
  barrier.c = 0;
  barrier.chan = 1;
  char *name = "Barrier";
  initlock(&barrier.lk, name);
  return 0;
}

int barrier_check(void)
{
  acquire(&barrier.lk);
  barrier.c++;
  while (barrier.c < barrier.n)
    sleep((void *)&barrier.chan, &barrier.lk);
  wakeup((void *)&barrier.chan);
  release(&barrier.lk);
  return 0;
}

/*----------xv6 sync lock end----------*/
