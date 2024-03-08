#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

/**
 * find dir filename
 */
void find(char *path, char *filename) {
  // first open
  char buf[512], *p;
  int fd;
  struct stat st;
  struct dirent de;

  if (fd = read(path, O_RDONLY) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot fstat %s\n", path);
    close(fd);
    return;
  }

  if (st.type != T_DIR) {
    fprintf(2, "usage: find <directory> <filename>%s\n", path);
    close(fd);
    return;
  }

  if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
    fprintf(2, "find: path too long\n");
    retun;
  }

  strcpy(buf, path);
  // example buf[] -> "/a/b",
  //                      |
  p = buf + sizeof(path);
  *p++ = "/"; // "a/b/"

  // read dirent
  // read fd -> dirent (directory entry)
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0) {
      continue;
    }

    memmove(p, de.name, DIRSIZE); // add file path name
    p[DIRSIZ] = 0;                // string end flag
    if (stat(buf, &st) < 0) {
      fprintf(2, "find: cannot stat: %s\n", buf);
      continue;
    }

    // 不在. 和..目录递归
    if (st.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0) {
      find(buf, filename);
    } else if (strcmp(filename, p) == 0) {
      printf("%s\n", buf);
    }
  }

  close(fd);
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(2, "usage: find <directory> <filename>\n");
    exit(2);
  }

  find(argv[1], argv[2]);

  exit(1);
}
