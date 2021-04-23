
#include "types.h"
#include "stat.h"
#include "user.h"
#include "uspinlock.h"

int main()
{
  int ret;
  int i;
  int n = 10;
  uspinlock_init();
  ucounter_init();
  ucounter_set(0, 1);
  ret = fork();
  if (ret == 0)
  {
    // Child
    for (i = 0; i < n; i++)
    {
      uspinlock_acquire(0);
      printf(1, "I am child\n");
      ucounter_set(0, 0);
      ucv_wakeup(1);   // Wakes up the parent
      ucv_sleep(2, 0); // Child goes to sleep
      uspinlock_release(0);
    }
    exit();
  }
  else
  {
    // Parent
    for (i = 0; i < n; i++)
    {
      uspinlock_acquire(0);
      while (ucounter_get(0))
        ucv_sleep(1, 0);
      printf(1, "I am parent\n");
      ucv_wakeup(2); // Wakes up the child
      if (i != n - 1)
        ucv_sleep(1, 0); // Parent goes to sleep
      uspinlock_release(0);
    }
    wait();
    exit();
  }
}
