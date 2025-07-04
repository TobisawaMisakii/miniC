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
	%l2 = alloca [5 x i32], align 16 ;  1:a
	%l3 = alloca [2 x [3 x i32]], align 16 ;  1:b
	%l4 = alloca [2 x [3 x [4 x i32]]], align 16 ;  1:c
	%t5 = sext i32 4 to i64
	%t6 = getelementptr inbounds [5 x i32], [5 x i32]* %l2, i64 0, i64 %t5
	store i32 33333, [5 x i32] %l2, align 4
	%t8 = sext i32 1 to i64
	%t9 = sext i32 2 to i64
	%t10 = getelementptr inbounds [2 x [3 x i32]], [2 x [3 x i32]]* %l3, i64 0, i64 %t8
	%t11 = getelementptr inbounds [3 x i32], [3 x i32]* %t10, i64 0, i64 %t9
	store i32 22222, [2 x [3 x i32]] %l3, align 4
	%t13 = sext i32 1 to i64
	%t14 = sext i32 2 to i64
	%t15 = sext i32 3 to i64
	%t16 = getelementptr inbounds [2 x [3 x [4 x i32]]], [2 x [3 x [4 x i32]]]* %l4, i64 0, i64 %t13
	%t17 = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* %t16, i64 0, i64 %t14
	%t18 = getelementptr inbounds [3 x [4 x i32]], [3 x [4 x i32]]* %t17, i64 0, i64 %t15
	store [2 x [3 x [4 x i32]]] %l4, i32* %l0, align 4
	br label %.L20
.L20:
	%t21 = load i32, i32* %l0, align 4
	ret i32 %t21
}
