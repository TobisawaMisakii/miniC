	.arch armv8-a
.text
.section .data
.global c
.align 4
.type c, %object
c:
.quad 3
.align 1
.global main
.type main, %function
main:
	push {xr,fp}
	mov xr,#32
	sub sp,sp,xr
	add fp,sp,#0
	b .L0
.L0:
	ldr x0,[fp,#28]
	add fp,fp,#32
	mov sp,fp
	pop {xr,fp}
	ret lr
