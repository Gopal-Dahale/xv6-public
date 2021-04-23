#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
SYSCALL(myyear)
SYSCALL(ucounter_init)
SYSCALL(ucounter_get)
SYSCALL(ucounter_set)
SYSCALL(uspinlock_init)
SYSCALL(uspinlock_acquire)
SYSCALL(uspinlock_release)
SYSCALL(ucv_sleep)
SYSCALL(ucv_wakeup)
SYSCALL(barrier_init)
SYSCALL(barrier_check)
SYSCALL(waitpid)
SYSCALL(sem_init)
SYSCALL(sem_up)
SYSCALL(sem_down)
