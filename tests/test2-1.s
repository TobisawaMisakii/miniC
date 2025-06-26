	.arch armv8-a
.text
.text

.align 1
.global main
.type main, %function
main:
	@ %l0:[sp,#0]
	@ i:%l1:[sp,#8]
	@ %t2:[sp,#16]
	@ %t3:[sp,#24]
	@ %t4:[sp,#32]
	@ %t6:[sp,#40]
	@ %t8:[sp,#48]
	@ %t10:[sp,#56]
	str x29,[sp, #-8]!
	sub sp,sp,72
	mov x29,sp
	mov x0,#1
	str x0,[sp,#8]
	ldr x0,[sp,#8]
	str x0,[sp,#24]
	ldr x0,[sp,#24]
	mov x1,#1
	cmp x0,x1
	cset x2,ne
	str x2,[sp,#32]
	ldr x0,[sp,#32]
	mov x1,#1
	cmp x0,x1
	beq .L0
	b .L1
.L0:
	mov x1,#0
	str x1,[sp]
	b .L3
	b .L2
.L1:
	mov x1,#1
	str x1,[sp]
	b .L3
	b .L2
.L2:
.L3:
	ldr x1,[sp]
	str x1,[sp,#56]
	ldr x0,[sp,#56]
	mov sp,x29
	add sp,sp,72
	ldr x29,[sp], #8
	ret
