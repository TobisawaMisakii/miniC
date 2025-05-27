.arch armv7ve
.arm
.fpu vfpv4
.text
.align 1
.global main
.type main, %function
main:
	push {xr,fp}
	sub sp,sp,#40
	add fp,sp,#0
	ldr,[fp,#20]
	ldr,[fp,#24]
	add
	str,[fp,#28]
	b .L0
.L0:
	ldr x0,[fp,#36]
	add fp,fp,#40
	mov sp,fp
	pop {xr,fp}
	bx lr
