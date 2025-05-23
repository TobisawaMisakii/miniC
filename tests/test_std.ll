define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca [3 x [5 x i32]], align 16 ; variable: a
	%l2 = alloca i32, align 4 ; variable: b
	%t3 = mul nsw i32 1, 5
	%t4 = add nsw i32 %t3, 1
	%t6 = mul nsw i32 %t4, 4
	%t21 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t22 = bitcast i32* %t21 to i8*
	%t24 = sext i32 %t6 to i64
	%t23 = getelementptr inbounds i8, i8* %t22, i64 %t24
	%t5 = bitcast i8* %t23 to i32*
	store i32 2, i32* %t5, align 4
	%t8 = mul nsw i32 1, 5
	%t9 = add nsw i32 %t8, 1
	%t11 = mul nsw i32 %t9, 4
	%t25 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t26 = bitcast i32* %t25 to i8*
	%t28 = sext i32 %t11 to i64
	%t27 = getelementptr inbounds i8, i8* %t26, i64 %t28
	%t10 = bitcast i8* %t27 to i32*
	%t13 = load i32, i32* %t10, align 4
	store i32 %t13, i32* %l2, align 4
	%t14 = mul nsw i32 1, 5
	%t15 = add nsw i32 %t14, 1
	%t17 = mul nsw i32 %t15, 4
	%t29 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t30 = bitcast i32* %t29 to i8*
	%t32 = sext i32 %t17 to i64
	%t31 = getelementptr inbounds i8, i8* %t30, i64 %t32
	%t16 = bitcast i8* %t31 to i32*
	%t19 = load i32, i32* %t16, align 4
	%t33 = load i32, i32* %l2, align 4
	%t20 = add nsw i32 %t33, %t19
	store i32 %t20, i32* %l0, align 4
	%t34 = load i32, i32* %l0, align 4
	ret i32 %t34
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
