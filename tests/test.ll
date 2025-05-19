define i32 @get_one(i32 %t0) {
	%l1 = alloca i32, align 4 ; 1:a
	%l2 = alloca i32, align 4
	%l1 = %t0
	store i32 1, i32* %l2, align 4
	br label %.L4
.L4:
	%t5 = load i32, i32* %l2, align 4
	ret i32 %t5
}
define i32 @deepWhileBr(i32 %t0, i32 %t1) {
	%l2 = alloca i32, align 4 ; 1:a
	%l3 = alloca i32, align 4 ; 1:b
	%l4 = alloca i32, align 4
	%l5 = alloca i32, align 4 ; 1:c
	%l6 = alloca i32, align 4 ; 2:d
	%l7 = alloca i32, align 4 ; 4:e
	%l2 = %t0
	%l3 = %t1
	%t8 = load i32, i32* %l2, align 4
	%t9 = load i32, i32* %l3, align 4
	%t10 = add i32 %t8, %t9
	store i32 %t10, i32* %l5, align 4
	br label %.L12
.L12:
	%t13 = load i32, i32* %l5, align 4
	%t14 = icmp slt i32 %t13, 75
	br i1 %t14, label %.L15, label %.L39
.L15:
	store i32 42, i32* %l6, align 4
	%t17 = load i32, i32* %l5, align 4
	%t18 = icmp slt i32 %t17, 100
	br i1 %t18, label %.L19, label %.L38
.L19:
	%t20 = load i32, i32* %l5, align 4
	%t21 = load i32, i32* %l6, align 4
	%t22 = add i32 %t20, %t21
	store i32 %t22, i32* %l5, align 4
	%t24 = load i32, i32* %l5, align 4
	%t25 = icmp sgt i32 %t24, 99
	br i1 %t25, label %.L26, label %.L37
.L26:
	%t27 = load i32, i32* %l6, align 4
	%t28 = mul i32 %t27, 2
	store i32 %t28, i32* %l7, align 4
	%t30 = call i32 @get_one(i32 0)
	%t31 = icmp eq i32 %t30, 1
	br i1 %t31, label %.L32, label %.L36
.L32:
	%t33 = load i32, i32* %l7, align 4
	%t34 = mul i32 %t33, 2
	store i32 %t34, i32* %l5, align 4
	br label %.L36
	br label %.L36
.L36:
	br label %.L37
	br label %.L37
.L37:
	br label %.L38
	br label %.L38
.L38:
	br label %.L12
.L39:
	%t40 = load i32, i32* %l5, align 4
	store i32 %t40, i32* %l4, align 4
	br label %.L42
.L42:
	%t43 = load i32, i32* %l4, align 4
	ret i32 %t43
}
define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:p
	store i32 2, i32* %l1, align 4
	%t3 = load i32, i32* %l1, align 4
	%t4 = load i32, i32* %l1, align 4
	%t5 = call i32 @deepWhileBr(i32 %t3, i32 %t4)
	store i32 %t5, i32* %l1, align 4
	%t7 = load i32, i32* %l1, align 4
	call void @putint(i32 %t7)
	store i32 0, i32* %l0, align 4
	br label %.L9
.L9:
	%t10 = load i32, i32* %l0, align 4
	ret i32 %t10
}
