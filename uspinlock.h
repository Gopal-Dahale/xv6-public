/*----------xv6 sync lab----------*/
#define NLOCK 10

// Structure
typedef struct __uspinlock_t
{
  uint locked; // Is the lock held?
} uspinlock_t;

extern uspinlock_t uspinlocks[NLOCK]; // Declaration

int uspinlock_init(void);
int uspinlock_acquire(int);
int uspinlock_release(int);
int uspinlock_holding(int);
/*----------xv6 sync lab end----------*/
