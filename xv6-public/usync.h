#ifndef USYNC_H
#define USYNC_H
#include "spinlock.h"

typedef struct {
  uint locked;
  struct spinlock lk;
  char *name;
  int pid; 
} mutex; 
#endif
