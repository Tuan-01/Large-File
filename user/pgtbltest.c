#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"
#include "kernel/memlayout.h"
#include "user/user.h"

void
ugetpid_test()
{
  int pid;
  printf("ugetpid_test starting\n");
  pid = getpid();

  struct usyscall *u = (struct usyscall *)USYSCALL;
  if (u->pid != pid) {
    printf("ugetpid: failed! expected %d, got %d\n", pid, u->pid);
    exit(1);
  }
  printf("ugetpid_test: OK\n");
}

int
main(int argc, char *argv[])
{
  ugetpid_test();
  printf("pgtbltest: all tests passed\n");
  exit(0);
}