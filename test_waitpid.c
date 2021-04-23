#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
  int ret;
  
  ret = fork();
  if(ret == 0)
  {
    sleep(10);
    exit();
  }
  else
  {
    int retwait = waitpid(ret+1);
    printf(1, "return value of wrong waitpid %d\n", retwait);

    retwait = waitpid(ret);
    printf(1, "return value of correct waitpid %d\n", retwait);
    
    retwait = wait();
    printf(1, "return value of wait %d\n", retwait);
    
    printf(1, "child reaped\n");
    exit();
  }
}
  
