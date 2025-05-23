; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --check-globals all --version 5
; RUN: opt %s -passes=bdce -S | FileCheck %s

define i32 @foo(i32 %a) #0 {
; CHECK-LABEL: define i32 @foo(
; CHECK-SAME: i32 [[A:%.*]]) #[[ATTR0:[0-9]+]] {
; CHECK-NEXT:  [[ENTRY:.*:]]
; CHECK-NEXT:    ret i32 [[A]]
;
entry:
  %tk0 = call token @llvm.experimental.convergence.entry()
  ret i32 %a
}

define void @bar() #0 {
; CHECK-LABEL: define void @bar(
; CHECK-SAME: ) #[[ATTR0]] {
; CHECK-NEXT:  [[ENTRY:.*:]]
; CHECK-NEXT:    ret void
;
entry:
  %tk0 = call token @llvm.experimental.convergence.anchor()
  ret void
}

define void @baz() #0 {
; CHECK-LABEL: define void @baz(
; CHECK-SAME: ) #[[ATTR0]] {
; CHECK-NEXT:  [[ENTRY:.*:]]
; CHECK-NEXT:    br label %[[HEADER:.*]]
; CHECK:       [[HEADER]]:
; CHECK-NEXT:    br i1 true, label %[[BODY:.*]], label %[[EXIT:.*]]
; CHECK:       [[BODY]]:
; CHECK-NEXT:    br label %[[HEADER]]
; CHECK:       [[EXIT]]:
; CHECK-NEXT:    ret void
;
entry:
  %tk0 = call token @llvm.experimental.convergence.entry()
  br label %header

header:
  %tk1 = call token @llvm.experimental.convergence.loop() [ "convergencectrl"(token %tk0) ]
  br i1 true, label %body, label %exit

body:
  br label %header

exit:
  ret void
}

declare token @llvm.experimental.convergence.entry() #1
declare token @llvm.experimental.convergence.anchor() #1
declare token @llvm.experimental.convergence.loop() #1

attributes #0 = { convergent }
attributes #1 = { convergent nocallback nofree nosync nounwind willreturn memory(none) }
;.
; CHECK: attributes #[[ATTR0]] = { convergent }
; CHECK: attributes #[[ATTR1:[0-9]+]] = { convergent nocallback nofree nosync nounwind willreturn memory(none) }
;.
