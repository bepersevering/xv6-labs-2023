#include "kernel/types.h"
#include "user/user.h"

#define P_READ 0
#define P_WRITE 1

int lpipe_first_read(int pipe, int *first) {
  if (read(pipe, first, sizeof(int)) == sizeof(int)) {
    printf("prime %d\n", *first);
    return 0;
  }
  return -1;
}

void prime(int p[2]) {
  close(p[P_WRITE]);
  int rp[2];
  // 读第一个
  int first;
  int t;

  if (lpipe_first_read(p[P_READ], &first) == 0) {
    pipe(rp);
    while (read(p[P_READ], &t, sizeof(int)) == sizeof(int)) {
      if (t % first) {
        write(rp[P_WRITE], &t, sizeof(int));
      }
    }
    if (fork() == 0) {
      // chile process
      prime(rp);
      close(rp[P_WRITE]);
    } else {
      // parent process
      close(rp[P_READ]);
      close(rp[P_WRITE]);
      wait(0);
    }

    close(p[P_READ]);
  }
  exit(0);
}

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);

  for (int i = 2; i <= 35; i++) {
    write(p[P_WRITE], &i, sizeof(int));
  }

  if (fork() == 0) {
    // child process
    prime(p);
  } else {
    // parent process
    close(p[P_READ]);
    close(p[P_WRITE]);
    wait(0);
  }

  exit(0);
}
