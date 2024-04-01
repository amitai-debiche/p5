#include "types.h"
#include "user.h"

int shared_variable = 0;
mutex m;
void fn1(void* arg) {
  //printf(1, "fn1 start\n");
  macquire(&m);
  //printf(1, "fn1 acquired\n");
  for (int i = 0; i < 10000000; i++) {
    ++shared_variable;
  }
    mrelease(&m);
    //printf(1, "released\n");
  exit();
}

void fn2(void* arg) {
  //printf(1, "fn2 start\n");
    macquire(&m);
    //printf(1, "fn2 acquired\n");
  for (int i = 0; i < 10000000; i++) {
    ++shared_variable;
  }
    mrelease(&m);
    //printf(1, "acquired\n");
  exit();
}

int main() {
  //printf(1, "before minit\n");
  minit(&m);
  //printf(1, "after minit\n");
  char* stack1 = (char*)malloc(4096);
  char* stack2 = (char*)malloc(4096);

  clone(fn1, stack1 + 4096, 0);
  clone(fn2, stack2 + 4096, 0);

  //printf(1, "after clones\n");
  wait();
  //printf(1, "after wait1\n");
  wait();
  //printf(1, "after wait2\n");
  printf(1,"%d",shared_variable);
  exit();
}
