declare i32 @getint(...);
declare float @getfloat(...);
declare i32 @getch(...);
declare i32 @getarray(i32*);
declare i32 @getfarray(float*);
declare void @putint(i32);
declare void @putfloat(float);
declare void @putch(i32);
declare void @putarray(i32, i32*);
declare void @putfarray(i32, float*);
declare void @putf(i32*);
declare void @starttime(...);
declare void @stoptime(...);
define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:a
	%l2 = alloca float, align 4 ; 1:b
	store i32 1, i32* %l1, align 4
	store float 1.000000, float* %l2, align 4
	%t5 = load i32, i32* %l1, align 4
	%t6 = load float, float* %l2, align 4
	%t7 = sitofp i32 %t5 to float
	%t8 = fcmp oeq float %t7, %t6
	br i1 %t8, label %.L9, label %.L11
.L9:
	store i32 66, i32* %l0, align 4
	br label %.L13
.L11:
	store i32 77, i32* %l0, align 4
	br label %.L13
.L13:
	%t14 = load i32, i32* %l0, align 4
	ret i32 %t14
}
