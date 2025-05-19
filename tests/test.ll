define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:a
	store i32 1, i32* %l1, align 4
	%t3 = load i32, i32* %l1, align 4
	store i32 %t3, i32* %l0, align 4
	br label %.L5
.L5:
	%t6 = load i32, i32* %l0, align 4
	ret i32 %t6
}
