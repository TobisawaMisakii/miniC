declare i32 @getint(...);
declare float @getfloat(...);
declare i32 @getch(...);
declare i32 @getarray(i32);
declare i32 @getfarray(float);
declare void @putint(i32);
declare void @putfloat(float);
declare void @putch(i32);
declare void @putarray(i32, i32);
declare void @putfarray(i32, float);
declare void @putf(i32);
declare void @starttime(...);
declare void @stoptime(...);
define i32 @main()
{
	%l0 = alloca i32, align 4
	%l1 = alloca i32, align 4 ; 1:a
	%l2 = alloca i32, align 4 ; 1:b
	store i32 10, i32* %l1, align 4
	%t4 = sub i32 0, 1
	store i32 %t4, i32* %l2, align 4
	%t6 = load i32, i32* %l1, align 4
	%t7 = load i32, i32* %l2, align 4
	%t8 = add i32 %t6, %t7
	store i32 %t8, i32* %l0, align 4
	br label %.L10
.L10:
	%t11 = load i32, i32* %l0, align 4
	ret i32 %t11
}
