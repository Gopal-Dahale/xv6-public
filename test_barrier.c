#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
  int ret1, ret2;

  barrier_init(3);
  
  ret1 = fork();
  if(ret1 == 0)
    {
       
      sleep(10);

      printf(1, "Child 1 at barrier\n");
      barrier_check();
      printf(1, "Child 1 cleared barrier\n");

      exit();
    }
  else
    {
      ret2 = fork();

      if(ret2 == 0)
	{
	  sleep(20);
	  printf(1, "Child 2 at barrier\n");
	  barrier_check();
	  printf(1, "Child 2 cleared barrier\n");

	  exit();
	}
      else
	{
	  printf(1, "Parent at barrier\n");
	  barrier_check();
	  printf(1, "Parent cleared barrier\n");

	  wait();
	  wait();
	  exit();
	  
	}
      
    }
}

