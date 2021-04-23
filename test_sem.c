#include "types.h"
#include "stat.h"
#include "user.h"



int main()
{
  int ret1, ret2;
  int CHILDSEM=0;
  int PARENTSEM=1;
  
  sem_init(CHILDSEM, 0);
  sem_init(PARENTSEM, 0); 
  
  ret1 = fork();
  if(ret1 == 0)
    {
      sem_down(CHILDSEM);
      printf(1, "I am child 1\n");
      sem_up(PARENTSEM);
      exit();
    }
  else
    {
      ret2 = fork();
      if(ret2 == 0)
	{
	  sem_down(CHILDSEM);
	  printf(1, "I am child 2\n");
	  sem_up(PARENTSEM);
	  exit();
	}
      else {

	sleep(2);

	//inspite of the sleep, parent should print first
	printf(1, "I am parent and I should print first\n");

	sem_up(CHILDSEM);
	sem_down(PARENTSEM);
	
	printf(1, "Only one child has printed by now\n");

	sem_up(CHILDSEM);
	sem_down(PARENTSEM);
	printf(1, "Both children have printed by now\n");
	
	wait();
	wait();
	
	exit();
      }
    }
}

