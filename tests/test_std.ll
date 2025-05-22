define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca [3 x [5 x i32]], align 16 ; variable: a
	%l2 = alloca [3 x i32], align 16 ; variable: b
	%t3 = mul nsw i32 0, 5
	%t4 = add nsw i32 %t3, 0
	%t6 = mul nsw i32 %t4, 4
	%t15 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t16 = bitcast i32* %t15 to i8*
	%t18 = sext i32 %t6 to i64
	%t17 = getelementptr inbounds i8, i8* %t16, i64 %t18
	%t5 = bitcast i8* %t17 to i32*
	store i32 2, i32* %t5, align 4
	%t9 = mul nsw i32 0, 4
	%t19 = getelementptr inbounds [3 x i32], [3 x i32]* %l2, i64 0, i64 0
	%t20 = bitcast i32* %t19 to i8*
	%t22 = sext i32 %t9 to i64
	%t21 = getelementptr inbounds i8, i8* %t20, i64 %t22
	%t8 = bitcast i8* %t21 to i32*
	store i32 1, i32* %t8, align 4
	%t12 = mul nsw i32 0, 4
	%t23 = getelementptr inbounds [3 x i32], [3 x i32]* %l2, i64 0, i64 0
	%t24 = bitcast i32* %t23 to i8*
	%t26 = sext i32 %t12 to i64
	%t25 = getelementptr inbounds i8, i8* %t24, i64 %t26
	%t11 = bitcast i8* %t25 to i32*
	%t14 = load i32, i32* %t11, align 4
	store i32 %t14, i32* %l0, align 4
	%t27 = load i32, i32* %l0, align 4
	ret i32 %t27
}
declare i32 @getint(...);
declare i32 @getch(...);
declare void @putint(i32);
declare void @putch(i32);
declare void @putstr(i8*);
declare i32 @getarray(i32*);
declare void @putarray(i32, i32*);
declare float @getfloat(...);
declare void @putfloat(float);
declare i32 @getfarray(float*);
declare void @putfarray(i32, float*);
