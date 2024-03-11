#include "kernel/types.h"

#include "kernel/fcntl.h"

#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

void fmtname(char *path);

void find(char *path, char *filename) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, O_RDONLY)) < 0) {
    fprintf(2, "find: cannot read %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if (st.type != T_DIR) {
    fprintf(2, "usage: find <directory> <filename> %s\n", path);
    return;
  }

  // path is too long
  if ((strlen(path) + 1 + DIRSIZ + 1) > sizeof(buf)) {
    fprintf(2, "find: path is too long %s\n", path);
    return;
  }

  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/';

  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0) {
      continue;
    }
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;

    if (stat(buf, &st) < 0) {
      fprintf(2, "find: cannot stat %s\n", buf);
      close(fd);
    }

    if (st.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0) {
      find(buf, filename);
    } else if (strcmp(p, filename) == 0) {
      printf("%s\n", buf);
    }
  }

  close(fd);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(2, "usage: find <directory> <filename>\n");
    exit(1);
  }

  find(argv[1], argv[2]);
  exit(0);
}
