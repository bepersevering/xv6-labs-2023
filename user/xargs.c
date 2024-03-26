
#include "kernel/param.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

#define MAXN 1024
// xargs, MAXARG
int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(2, "Usage: xargs <command> \n");
    exit(1);
  }

  char *xargv[MAXARG];
  char buf[MAXN];
  char temp[MAXN];
  int index;
  int xi;

  // copy command的参数
  for (int = 1; i < argc; i++) {
    xargv[xi++] = argv[i];
  }

  // 从标准输入获取
  while (read(1, buf, MAXN) > 0) {
    buf[MAXN] = '\0';
    index = 0;

    for (int i = 0; i < strlen(buf); i++) {
      if (buf[i] == '\n') {
        // 如果遇到换行符，则直接执行
        temp[index] = '\0';
        xargv[xi] = temp;
        index = 0;
        if (fork() == 0) {
          // child process
          exec(argv[1], xargv);
        }
        wait(0);
      } else {
        temp[index++] = buf[i];
      }
    }
  }
  exit(0);
}
