#include "kernel/types.h"
#include "user/user.h"

#define P_RD 0
#define P_WR 1

const int INT_LEN = sizeof(int);

int lpipe_first_data(int p[2], int *first_data) {
  if (read(p[P_RD], first_data, INT_LEN) == INT_LEN) {
    printf("prime %d\n", *first_data);
    return 0;
  }
  return -1;
}

void transmit_data(int lpipe[2], int rpipe[2], int first_data) {
  int data;
  while (read(lpipe[P_RD], &data, INT_LEN) == INT_LEN) {
    if (data % first_data) {
      write(rpipe[P_WR], &data, INT_LEN);
    }
  }
  close(lpipe[P_RD]);
  close(rpipe[P_WR]);
}

void primes(int p[2]) {
  close(p[P_WR]);
  int first_data;
  if (lpipe_first_data(p, &first_data) == 0) {
    int rpipe[2];
    pipe(rpipe);
    transmit_data(p, rpipe, first_data);

    if (0 == fork()) {
      primes(rpipe);
    } else {
      close(rpipe[P_RD]);
      wait(0);
    }
  }
  exit(0);
}

int main(int argc, char **argv) {
  int p[2];
  pipe(p);
  for (int i = 2; i <= 35; i++) {
    write(p[P_WR], &i, INT_LEN);
  }

  if (0 == fork()) {
    primes(p);
  } else {
    close(p[P_WR]);
    close(p[P_RD]);
    wait(0);
  }

  exit(0);
}
