	.arch armv8-a
.text
.section .data
.global a
.align 4
.type a, %object
a:
.word 3
.section .data
.global b
.align 4
.type b, %object
b:
.word 5
.align 1
.global main
.type main, %function
main:
	@ %l0:[x29,#0]
	@ a:%l1:[x29,#4]
	@ %t2:[x29,#8]
	@ %t3:[x29,#12]
	@ %t4:[x29,#16]
	@ %t6:[x29,#20]
	@ %t8:[x29,#24]
	@ %t9:[x29,#28]
	@ %t10:[x29,#32]
	@ %t11:[x29,#36]
	@ %t13:[x29,#40]
	str x29,[sp, #-8]!
	sub sp,sp,56
	mov x29,sp
	mov x0,#5
	str x0,[x29,#4]
	adrp x0,b
	add x0,x0,:lo12:b
	ldr x0,[x0]
	str x0,[x29,#12]
	ldr x0,[x29,#12]
	mov x1,#3
	cmp x0,x1
	cset x2,ge
	str x2,[x29,#16]

	mov x0,#1
	str x0,[x29,#4]
	b .L1
	b .L1
.L1:
	ldr x0,[x29,#4]
	str x0,[x29,#24]
	adrp x0,b
	add x0,x0,:lo12:b
	ldr x0,[x0]
	str x0,[x29,#28]
	ldr x0,[x29,#24]
	ldr x1,[x29,#28]
	add x2,x0,x1
	str x2,[x29,#32]
	ldr x0,[x29,#32]
	str x0,[x29]
	b .L2
.L2:
	ldr x0,[x29]
	str x0,[x29,#40]
	ldr x0,[x29,#40]
	mov sp,x29
	add sp,sp,56
	ldr x29,[sp], #8
	ret
