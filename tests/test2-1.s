	.arch armv8-a
.text
.text

.align 1
.global ififElse
.type ififElse, %function
ififElse:
	str x29,[sp, #-8]!
	sub sp,sp,136
	mov x29,sp
	mov x0,#5
	str x0,[sp,#8]
	mov x0,#10
	str x0,[sp,#16]
	ldr x0,[sp,#8]
	str x0,[sp,#40]
	ldr x0,[sp,#40]
	mov x1,#5
	cmp x0,x1
	cset x2,eq
	str x2,[sp,#48]
	ldr x0,[sp,#48]
	mov x1,#1
	cmp x0,x1
	beq .L0
	b .L4
.L0:
	ldr x1,[sp,#16]
	str x1,[sp,#56]
	ldr x1,[sp,#56]
	mov x2,#10
	cmp x1,x2
	cset x3,eq
	str x3,[sp,#64]
	ldr x1,[sp,#64]
	mov x2,#1
	cmp x1,x2
	beq .L1
	b .L2
.L1:
	mov x2,#25
	str x2,[sp,#8]
	b .L3
.L2:
	ldr x2,[sp,#8]
	str x2,[sp,#80]
	ldr x2,[sp,#80]
	mov x3,#15
	add x4,x2,x3
	str x4,[sp,#88]
	ldr x2,[sp,#88]
	str x2,[sp,#8]
	b .L3
.L3:
	b .L4
	b .L4
.L4:
	ldr x2,[sp,#8]
	str x2,[sp,#104]
	ldr x2,[sp,#104]
	str x2,[sp]
	b .L5
.L5:
	ldr x2,[sp]
	str x2,[sp,#120]
	ldr x0,[sp,#120]
	mov sp,x29
	add sp,sp,136
	ldr x29,[sp], #8
	ret

.align 1
.global main
.type main, %function
main:
	stp x29,lr,[sp, #-16]!
	sub sp,sp,32
	mov x29,sp
	bl ififElse
	str x0,[sp,#8]
	str x0,[sp,#8]
	ldr x2,[sp,#8]
	str x2,[sp]
	b .L6
.L6:
	ldr x2,[sp]
	str x2,[sp,#24]
	ldr x0,[sp,#24]
	mov sp,x29
	add sp,sp,32
	ldp x29,lr,[sp], #16
	ret
