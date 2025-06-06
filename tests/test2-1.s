	.text
	.file	"test2-1.ll"
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	mov	w8, #3                          // =0x3
	str	w8, [sp, #12]
	b	.LBB0_1
.LBB0_1:                                // %.L2
	ldr	w0, [sp, #12]
	add	sp, sp, #16
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        // -- End function
	.section	".note.GNU-stack","",@progbits
	.addrsig
