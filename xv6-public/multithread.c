#include "types.h"
#include "user.h"

#define N_THREAD 4

int global_counter = 0;
mutex m;

void fn(void* arg) {
  for (int i = 0; i < 100; i++) {
    // race condition
    macquire(&m);
    int local_copy = global_counter;
    if(i % 10 == 0) sleep(0);
    global_counter = local_copy + 1;
    mrelease(&m);
  }

  exit();
}

int main() {
  char* stacks[N_THREAD];
  minit(&m);
  for (int i = 0; i < N_THREAD; i++) {
    stacks[i] = (char*)malloc(4096);
  }

  for (int i = 0; i < N_THREAD; i++) {
    int tid = clone(fn, stacks[i] + 4096, 0);
    if (tid < 0) {
      printf(2, "clone error");
    }
  }

  for (int i = 0; i < N_THREAD; i++)
  {
    wait();
  }

  printf(1, "Final counter value: %d\n", global_counter);

  exit();
}
