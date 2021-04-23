#include "types.h"
#include "stat.h"
#include "user.h"
#include "uspinlock.h"

int main()
{
  int ret;
  int i;

  // Initialize locks and counters
  ucounter_init();
  uspinlock_init();
  ret = fork();

  //both parent and child increment the same counter 10000 times each
  for (i = 0; i < 10000; i++)
  {
    uspinlock_acquire(0);
    ucounter_set(0, ucounter_get(0) + 1);
    uspinlock_release(0);
  }

  if (ret == 0)
  {
    exit();
  }
  else
  {
    wait();
    printf(1, "%d\n", ucounter_get(0));
    //ideally this value should be 20000
    exit();
  }
}
