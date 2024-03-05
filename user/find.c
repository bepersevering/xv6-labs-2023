#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

void find(char *filepath, char *filename) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
}

int main(int argc, char *argv[]) {

  // 判断参数个数
  if (argc != 2) {
    fprintf(2, "usage: find <directory> <filename>\n");
    exit(1);
  }

  find(argv[1], arv[2]);
  exit(0);
}
