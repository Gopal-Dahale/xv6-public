#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "uspinlock.h"
#include "barrier.h"
#include "semaphore.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return the birth year of Gopal Ramesh Dahale
int sys_myyear(void)
{
  return 2000;
}

/*----------xv6 sync lab----------*/
#define NCOUNTER 10
int counters[NCOUNTER];

int sys_ucounter_init(void)
{
  int i;
  for (i = 0; i < NCOUNTER; i++)
    counters[i] = 0;
  return 1;
}

int sys_ucounter_get(void)
{
  int index;
  if (argint(0, &index) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  if (index >= NCOUNTER)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  return counters[index];
}

int sys_ucounter_set(void)
{
  int index, value;
  if (argint(0, &index) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  if (argint(1, &value) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  if (index >= NCOUNTER)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  counters[index] = value;
  return 1;
}

int sys_uspinlock_init(void)
{
  return uspinlock_init();
}

int sys_uspinlock_acquire(void)
{
  int index;
  if (argint(0, &index) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  if (index >= NLOCK)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  return uspinlock_acquire(index);
}

int sys_uspinlock_release(void)
{
  int index;
  if (argint(0, &index) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  if (index >= NLOCK)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  return uspinlock_release(index);
}

int sys_ucv_sleep(void)
{
  int variable, index;
  if (argint(0, &variable) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  if (argint(1, &index) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  if (index >= NLOCK)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  ucv_sleep((void *)&variable, index);
  return 1;
}

int sys_ucv_wakeup(void)
{
  int variable;
  if (argint(0, &variable) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  wakeup((void *)variable);
  return 1;
}

int sys_barrier_init(void)
{
  int variable;
  if (argint(0, &variable) < 0)
  {
    cprintf("Kernel: System call returning -1\n");
    return -1;
  }
  return barrier_init(variable);
}

int sys_barrier_check(void)
{
  return barrier_check();
}

int sys_waitpid(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return waitpid(pid);
}

int sys_sem_init(void)
{
  int index, val;
  if (argint(0, &index) < 0)
    return -1;

  if (argint(1, &val) < 0)
    return -1;

  return sem_init(index, val);
}

int sys_sem_up(void)
{
  int index;
  if (argint(0, &index) < 0)
    return -1;

  return sem_up(index);
}

int sys_sem_down(void)
{
  int index;
  if (argint(0, &index) < 0)
    return -1;
  return sem_down(index);
}

/*----------xv6 sync lab end----------*/
