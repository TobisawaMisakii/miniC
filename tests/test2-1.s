	.arch armv8-a
.text
.text

.align 1
.global main
.type main, %function
main:
	@ %l0:[sp,#0]
	@ a:%l1:[sp,#8]
	@ b:%l2:[sp,#16]
	@ %t3:[sp,#24]
	@ %t4:[sp,#32]
	@ %t5:[sp,#40]
	@ %t6:[sp,#48]
	@ %t7:[sp,#56]
	@ %t8:[sp,#64]
	@ %t9:[sp,#72]
	@ %t11:[sp,#80]
	str x29,[sp, #-8]!
	sub sp,sp,104
	mov x29,sp
	mov x0,#10
	str x0,[sp,#8]
	mov x0,#1
	mov x1,#0
	sub x0,x1,x0
	str x0,[sp,#32]
	ldr x0,[sp,#32]
	str x0,[sp,#16]
	ldr x0,[sp,#8]
	str x0,[sp,#48]
	ldr x0,[sp,#16]
	str x0,[sp,#56]
	ldr x0,[sp,#48]
	ldr x1,[sp,#56]
	add x2,x0,x1
	str x2,[sp,#64]
	ldr x0,[sp,#64]
	str x0,[sp]
	b .L0
.L0:
	ldr x0,[sp]
	str x0,[sp,#80]
	ldr x0,[sp,#80]
	mov sp,x29
	add sp,sp,104
	ldr x29,[sp], #8
	ret
