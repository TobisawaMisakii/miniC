	.arch armv8-a
.text
.text

.align 1
.global main
.type main, %function
main:
	@ %l0:[sp,#0]
	@ %t1:[sp,#8]
	@ %t3:[sp,#16]
	str x29,[sp, #-8]!
	sub sp,sp,40
	mov x29,sp
	mov x0,#3
	str x0,[sp]
	b .L0
.L0:
	ldr x0,[sp]
	str x0,[sp,#16]
	ldr x0,[sp,#16]
	mov sp,x29
	add sp,sp,40
	ldr x29,[sp], #8
	ret
