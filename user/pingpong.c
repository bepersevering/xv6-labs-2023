#include "kernel/types.h"
#include "user/user.h"

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

  return 0;
}
