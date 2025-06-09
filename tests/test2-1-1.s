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
	mov	w8, #5
	str	w8, [sp, #8]
	adrp	x8, :got:b
	ldr	x8, [x8, :got_lo12:b]
	ldr	w8, [x8]
	subs	w8, w8, #3
	b.lt	.LBB0_2
	b	.LBB0_1
.LBB0_1:                                // %.L5
	mov	w8, #1
	str	w8, [sp, #8]
	b	.LBB0_2
.LBB0_2:                                // %.L7
	ldr	w8, [sp, #8]
	adrp	x9, :got:b
	ldr	x9, [x9, :got_lo12:b]
	ldr	w9, [x9]
	add	w8, w8, w9
	str	w8, [sp, #12]
	b	.LBB0_3
.LBB0_3:                                // %.L12
	ldr	w0, [sp, #12]
	add	sp, sp, #16
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        // -- End function
	.type	a,@object                       // @a
	.data
	.globl	a
	.p2align	2
a:
	.word	3                               // 0x3
	.size	a, 4

	.type	b,@object                       // @b
	.globl	b
	.p2align	2
b:
	.word	5                               // 0x5
	.size	b, 4

	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym b
