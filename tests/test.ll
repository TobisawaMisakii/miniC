define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:a
	store i32 5, i32* %l1, align 4
	%t3 = load i32, i32* %l1, align 4
	store i32 %t3, i32* %l0, align 4
	%t5 = load i32, i32* %l0, align 4
	br label %.L6
.L6:
	ret i32 %t5
}
