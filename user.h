struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int *);
int write(int, const void *, int);
int read(int, void *, int);
int close(int);
int kill(int);
int exec(char *, char **);
int open(const char *, int);
int mknod(const char *, short, short);
int unlink(const char *);
int fstat(int fd, struct stat *);
int link(const char *, const char *);
int mkdir(const char *);
int chdir(const char *);
int dup(int);
int getpid(void);
char *sbrk(int);
int sleep(int);
int uptime(void);
int myyear(void);
/*----------xv6 sync lab----------*/
int ucounter_init(void);
int ucounter_get(int);
int ucounter_set(int, int);
int uspinlock_init(void);
int uspinlock_acquire(int);
int uspinlock_release(int);
int ucv_sleep(int, int);
int ucv_wakeup(int);
int barrier_init(int);
int barrier_check(void);
int waitpid(int);
int sem_init(int, int);
int sem_up(int);
int sem_down(int);

/*----------xv6 sync lab end----------*/

// ulib.c
int stat(const char *, struct stat *);
char *strcpy(char *, const char *);
void *memmove(void *, const void *, int);
char *strchr(const char *, char c);
int strcmp(const char *, const char *);
void printf(int, const char *, ...);
char *gets(char *, int max);
uint strlen(const char *);
void *memset(void *, int, uint);
void *malloc(uint);
void free(void *);
int atoi(const char *);
