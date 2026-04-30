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


void
superpg_test()
{
  printf("superpg_test: start\n");
  char *p = sbrk(0x200000); // Yêu cầu cấp 2MB bộ nhớ
  if(p == (char*)-1){
    printf("superpg_test: sbrk failed\n");
    exit(1);
  }
  p[0] = 'a';
  p[0x200000 - 1] = 'b';
  printf("superpg_test: OK\n");
}

// Trong hàm main(), hãy gọi nó:
int main(int argc, char *argv[]) {
  ugetpid_test();
  superpg_test(); // <-- Thêm dòng này vào
  printf("pgtbltest: all tests passed\n");
  exit(0);
}