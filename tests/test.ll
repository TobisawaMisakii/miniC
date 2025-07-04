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
	%l2 = alloca [2 x [3 x [4 x i32]]], align 16 ;  1:c
	%t3 = sext i32 1 to i64
	%t4 = sext i32 2 to i64
	%t5 = sext i32 3 to i64
	%t6 = getelementptr inbounds [2 x [3 x [4 x i32]]], [2 x [3 x [4 x i32]]]* %l2, i64 0, i64 %t3
	%t7 = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* %t6, i64 0, i64 %t4
	%t8 = getelementptr inbounds [4 x i32], [4 x i32]* %t7, i64 0, i64 %t5
	%t9 = load i32, i32* %t8, align 4
	store i32 %t9, i32* %l0, align 4
	br label %.L11
.L11:
	%t12 = load i32, i32* %l0, align 4
	ret i32 %t12
}
