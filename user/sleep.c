#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int sleep_seconds;
  if (argc < 1) {
    fprintf(2, "Usage: sleep [x] seconds ...");
    exit(1);
  }

  sleep_seconds = atoi(argv[1]);
  sleep(sleep_seconds);
  exit(1);
  return 0;
}
