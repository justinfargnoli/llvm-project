// RUN: %clangxx_asan -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s

#include "defines.h"
#include <stdio.h>

struct IntHolder {
  explicit IntHolder(int *val = 0) : val_(val) { }
  ATTRIBUTE_NOINLINE ~IntHolder() {
    printf("Value: %d\n", *val_);  // BOOM
    // CHECK: ERROR: AddressSanitizer: stack-use-after-scope
    // CHECK:  #0 0x{{.*}} in IntHolder::~IntHolder{{.*}}.cpp:[[@LINE-2]]
  }
  void set(int *val) { val_ = val; }
  int *get() { return val_; }

  int *val_;
};

int main(int argc, char *argv[]) {
  // It is incorrect to use "x" int IntHolder destructor, because "x" is
  // "destroyed" earlier as it's declared later.
  IntHolder holder;
  int x = argc;
  holder.set(&x);
  return 0;
}
