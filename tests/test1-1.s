.arch armv7ve
.arm
.fpu vfpv4
.text
.align 1
.global main
.type main, %function
main:
	push {r10,fp}
	sub sp,sp,#28
	add fp,sp,#0
	movw r0,#:lower16:2
	str r0,[fp,#4]
	movw r0,#:lower16:3
	str r0,[fp,#8]
	ldr r0,[fp,#4]
	ldr r1,[fp,#8]
	add r2,r0,r1
	str r2,[fp,#20]
	ldr r0,[fp,#20]
	movw r1,#:lower16:2
	add r2,r0,r1
	str r2,[fp,#24]
	ldr r0,[fp,#24]
	str r0,[fp]
	b .L0
.L0:
	ldr r0,[fp]
	add fp,fp,#28
	mov sp,fp
	pop {r10,fp}
	bx lr
