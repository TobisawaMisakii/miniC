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
	%l1 = alloca i32, align 4 ; 1:i
	store i32 1, i32* %l1, align 4
	%t3 = load i32, i32* %l1, align 4
	%t4 = icmp ne i32 %t3, 1
	br i1 %t4, label %.L5, label %.L7
.L5:
	store i32 0, i32* %l0, align 4
	br label %.L9
.L7:
	store i32 1, i32* %l0, align 4
	br label %.L9
.L9:
	%t10 = load i32, i32* %l0, align 4
	ret i32 %t10
}
