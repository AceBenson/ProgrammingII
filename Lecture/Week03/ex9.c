#include <stdio.h>

int main(){
    int *pa;
    int a;
    pa = &a;
    *pa = 3;
}

/*
  compile with
     gcc -S -masm=intel ex8.c
  the output is
  ----------------------------------
	.file	"ex8.c"
	.intel_syntax noprefix
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB0:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	and	esp, -16
	sub	esp, 16
	call	___main
	lea	eax, [esp+8]
	mov	DWORD PTR [esp+12], eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (GNU) 4.8.1"


  */
