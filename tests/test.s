	.text
	.file	"test2-1.ll"
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	mov	w8, #893                        // =0x37d
	str	w8, [sp, #24]
	mov	w8, #716                        // =0x2cc
	str	w8, [sp, #20]
	mov	w8, #837                        // =0x345
	str	w8, [sp, #16]
	ldr	w8, [sp, #16]
	add	w8, w8, #128
	str	w8, [sp, #16]
	ldr	w8, [sp, #20]
	ldr	w9, [sp, #16]
	add	w8, w8, w9
	str	w8, [sp, #20]
	mov	w8, #241                        // =0xf1
	str	w8, [sp, #12]
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #12]
	add	w8, w8, w9
	subs	w8, w8, #412
	str	w8, [sp, #16]
	mov	w8, #771                        // =0x303
	str	w8, [sp, #8]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #8]
	add	w8, w8, w9
	subs	w8, w8, #18
	str	w8, [sp, #12]
	ldr	w8, [sp, #12]
	add	w8, w8, #66
	str	w8, [sp, #8]
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #16]
	add	w8, w8, w9
	subs	w8, w8, #33
	str	w8, [sp, #12]
	ldr	w8, [sp, #12]
	subs	w8, w8, #55
	str	w8, [sp, #16]
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #12]
	add	w8, w8, w9
	mov	w10, #21                        // =0x15
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	str	w8, [sp, #28]
	b	.LBB0_1
.LBB0_1:                                // %.L79
	ldr	w0, [sp, #28]
	add	sp, sp, #32
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        // -- End function
	.section	".note.GNU-stack","",@progbits
	.addrsig
