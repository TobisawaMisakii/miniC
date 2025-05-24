define i32 @main()
{
	%l0 = alloca i32, align 4
	%l1 = alloca [3 x [5 x i32]], align 16 ;  1:a
	%l2 = alloca [3 x i32], align 16 ;  1:b
	%l3 = alloca i32, align 4 ; 1:c
	store i32 1, i32* %l3, align 4
	%t5 = mul i32 1, 5
	%t6 = add i32 %t5, 1
	%t7 = mul i32 %t6, 4
	%t8 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t9 = bitcast i32* %t8 to i8*
	%t10 = sext i32 %t7 to i64
	%t11 = getelementptr inbounds i8, i8* %t9, i64 %t10
	%t12 = bitcast i8* %t11 to i32*
	store i32 2, i32* %t12, align 4
	%t14 = mul i32 1, 5
	%t15 = add i32 %t14, 1
	%t16 = mul i32 %t15, 4
	%t17 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t18 = bitcast i32* %t17 to i8*
	%t19 = sext i32 %t16 to i64
	%t20 = getelementptr inbounds i8, i8* %t18, i64 %t19
	%t21 = bitcast i8* %t20 to i32*
	%t22 = load i32, i32* %t21, align 4
	%t23 = load i32, i32* %l3, align 4
	%t24 = add i32 %t22, %t23
	%t25 = mul i32 0, 4
	%t26 = getelementptr inbounds [3 x i32], [3 x i32]* %l2, i64 0, i64 0
	%t27 = bitcast i32* %t26 to i8*
	%t28 = sext i32 %t25 to i64
	%t29 = getelementptr inbounds i8, i8* %t27, i64 %t28
	%t30 = bitcast i8* %t29 to i32*
	store i32 %t24, i32* %t30, align 4
	%t32 = mul i32 0, 4
	%t33 = getelementptr inbounds [3 x i32], [3 x i32]* %l2, i64 0, i64 0
	%t34 = bitcast i32* %t33 to i8*
	%t35 = sext i32 %t32 to i64
	%t36 = getelementptr inbounds i8, i8* %t34, i64 %t35
	%t37 = bitcast i8* %t36 to i32*
	%t38 = load i32, i32* %t37, align 4
	store i32 %t38, i32* %l0, align 4
	br label %.L40
.L40:
	%t41 = load i32, i32* %l0, align 4
	ret i32 %t41
}
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
