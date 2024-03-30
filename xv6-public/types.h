typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
typedef struct {
  uint locked;
  struct spinlock lk;

  char *name;
  int pid; 
} mutex;
