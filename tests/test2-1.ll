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
define i32 @f(i32 %t0)
{
	%l1 = alloca i32, align 4 ; 1:f
	%l2 = alloca i32, align 4
	store i32 %t0, i32* %l1, align 4
	%t4 = load i32, i32* %l1, align 4
	%t5 = mul i32 %t4, 2
	store i32 %t5, i32* %l2, align 4
	br label %.L7
.L7:
	%t8 = load i32, i32* %l2, align 4
	ret i32 %t8
}
define i32 @main()
{
	%l0 = alloca i32, align 4
	%t1 = call i32 @f()
	store i32 %t1, i32* %l0, align 4
	br label %.L3
.L3:
	%t4 = load i32, i32* %l0, align 4
	ret i32 %t4
}
