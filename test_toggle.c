#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
	int ret;
	int i;

	ret = fork();
	if(ret == 0)
	{
	  for(i=0; i < 10; i++) {
	    printf(1, "I am child\n");
	  }
          exit();
	}
	else
	{
	  for(i=0; i < 10; i++) {
	    printf(1, "I am parent\n");
	  }
	  wait();
          exit();
	}
}

