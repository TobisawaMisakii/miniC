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
	%l1 = alloca [3 x [5 x i32]], align 16 ;  1:a
	%l2 = alloca i32, align 4 ; 1:b
	%t3 = mul i32 1, 5
	%t4 = add i32 %t3, 1
	%t5 = mul i32 %t4, 4
	%t6 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t7 = bitcast i32* %t6 to i8*
	%t8 = sext i32 %t5 to i64
	%t9 = getelementptr inbounds i8, i8* %t7, i64 %t8
	%t10 = bitcast i8* %t9 to i32*
	store i32 2, i32* %t10, align 4
	%t12 = mul i32 1, 5
	%t13 = add i32 %t12, 1
	%t14 = mul i32 %t13, 4
	%t15 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t16 = bitcast i32* %t15 to i8*
	%t17 = sext i32 %t14 to i64
	%t18 = getelementptr inbounds i8, i8* %t16, i64 %t17
	%t19 = bitcast i8* %t18 to i32*
	%t20 = load i32, i32* %t19, align 4
	store i32 %t20, i32* %l2, align 4
	%t22 = load i32, i32* %l2, align 4
	%t23 = mul i32 1, 5
	%t24 = add i32 %t23, 1
	%t25 = mul i32 %t24, 4
	%t26 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t27 = bitcast i32* %t26 to i8*
	%t28 = sext i32 %t25 to i64
	%t29 = getelementptr inbounds i8, i8* %t27, i64 %t28
	%t30 = bitcast i8* %t29 to i32*
	%t31 = load i32, i32* %t30, align 4
	%t32 = add i32 %t22, %t31
	store i32 %t32, i32* %l0, align 4
	br label %.L34
.L34:
	%t35 = load i32, i32* %l0, align 4
	ret i32 %t35
}
