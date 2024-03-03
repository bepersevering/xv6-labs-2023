#include "kernel/types.h"
#include "user/user.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

// xv6 lab1 pingpong function
// Write a user-level program that users xv6 system calls to "ping-pong"
// over a pair of pipes, one of each direction. The parent should send a byte to
// the child; the child should print "<pid>: receive ping", where <pid> is its
// process ID, write the byte on the pipe to the parent, and exit; the parent
// should read the byte from the child, print "<pid>:received pong", and exit.
// Your solution should be ine the file user/pingpong.c

int main(int argc, char *argv[]) {

  // use pipe to create a pipe.
  // use fork to create a child.
  // use read to read from a pipe, and write to a pipe.
  // use getpid to find the process ID of the calling process
  // use programs on xv6 have a limited of library functions avaliable
  // to them. You can see the list in user/user;
  // the source(other than for system calls) is in user/ulib.c
  // user/printf.c and user/umalloc.c
  char buf = 'X';
  int fd_c2p[2];
  int fd_p2c[2];
  int exit_status = 0;
  pipe(fd_p2c);
  pipe(fd_c2p);

  int pid = fork();
  if (0 > pid) {
    fprintf(2, "fork error.\n");
    close(fd_p2c[PIPE_READ]);
    close(fd_p2c[PIPE_WRITE]);
    close(fd_c2p[PIPE_READ]);
    close(fd_c2p[PIPE_WRITE]);
    exit(1);
  } else if (0 == pid) {
    // child process
    close(fd_p2c[PIPE_WRITE]);
    close(fd_c2p[PIPE_READ]);
    if (read(fd_p2c[PIPE_READ], &buf, sizeof(char)) != sizeof(char)) {
      fprintf(2, "child read from pipe error.\n");
      exit_status = 1;
    } else {
      fprintf(1, "%d: received ping\n", getpid());
    }

    if (write(fd_c2p[PIPE_WRITE], &buf, sizeof(char)) != sizeof(char)) {
      fprintf(2, "child write to pipe error.\n");
      exit_status = 1;
    }

    close(fd_p2c[PIPE_READ]);
    close(fd_c2p[PIPE_WRITE]);
    exit(exit_status);
  } else {
    // parent process
    close(fd_p2c[PIPE_READ]);
    close(fd_c2p[PIPE_WRITE]);
    if (write(fd_p2c[PIPE_WRITE], &buf, sizeof(char)) != sizeof(char)) {
      fprintf(2, "parent write to pipe error.\n");
      exit_status = 1;
    }

    if (read(fd_c2p[PIPE_READ], &buf, sizeof(char)) != sizeof(char)) {
      fprintf(2, "parent read from pipe error.\n");
      exit_status = 1;
    } else {
      fprintf(1, "%d: received pong\n", getpid());
    }

    close(fd_p2c[PIPE_WRITE]);
    close(fd_c2p[PIPE_READ]);
    exit(exit_status);
  }
}
