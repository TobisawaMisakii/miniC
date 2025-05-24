define i32 @add([5 x i32]* %t0, i32* %t1, i32 %t2) {
	%l3 = alloca [5 x i32]*, align 8 ; variable: a
	%l4 = alloca i32*, align 8 ; variable: b
	%l5 = alloca i32, align 4 ; variable: c
	%l6 = alloca i32, align 4
	store [5 x i32]* %t0, [5 x i32]** %l3, align 8
	store i32* %t1, i32** %l4, align 8
	store i32 %t2, i32* %l5, align 4
	%t7 = mul nsw i32 0, 5
	%t8 = add nsw i32 %t7, 0
	%t10 = mul nsw i32 %t8, 4
	%t19 = load [5 x i32]*, [5 x i32]** %l3, align 8
	%t20 = getelementptr inbounds [5 x i32], [5 x i32]* %t19, i64 0, i64 0
	%t21 = bitcast i32* %t20 to i8*
	%t23 = sext i32 %t10 to i64
	%t22 = getelementptr inbounds i8, i8* %t21, i64 %t23
	%t9 = bitcast i8* %t22 to i32*
	%t13 = mul nsw i32 0, 4
	%t24 = load i32*, i32** %l4, align 8
	%t25 = getelementptr inbounds i32, i32* %t24, i64 0
	%t26 = bitcast i32* %t25 to i8*
	%t28 = sext i32 %t13 to i64
	%t27 = getelementptr inbounds i8, i8* %t26, i64 %t28
	%t12 = bitcast i8* %t27 to i32*
	%t15 = load i32, i32* %t9, align 4
	%t16 = load i32, i32* %t12, align 4
	%t17 = add nsw i32 %t15, %t16
	%t29 = load i32, i32* %l5, align 4
	%t18 = add nsw i32 %t17, %t29
	store i32 %t18, i32* %l6, align 4
	%t30 = load i32, i32* %l6, align 4
	ret i32 %t30
}
define i32 @main() {
	%l0 = alloca i32, align 4
	%l1 = alloca [3 x [5 x i32]], align 16 ; variable: a
	%l2 = alloca [3 x i32], align 16 ; variable: b
	%l3 = alloca i32, align 4 ; variable: c
	store i32 1, i32* %l3, align 4
	%t4 = mul nsw i32 1, 5
	%t5 = add nsw i32 %t4, 1
	%t7 = mul nsw i32 %t5, 4
	%t23 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t24 = bitcast i32* %t23 to i8*
	%t26 = sext i32 %t7 to i64
	%t25 = getelementptr inbounds i8, i8* %t24, i64 %t26
	%t6 = bitcast i8* %t25 to i32*
	store i32 2, i32* %t6, align 4
	%t12 = mul nsw i32 1, 5
	%t13 = add nsw i32 %t12, 1
	%t15 = mul nsw i32 %t13, 4
	%t27 = getelementptr inbounds [3 x [5 x i32]], [3 x [5 x i32]]* %l1, i64 0, i64 0, i64 0
	%t28 = bitcast i32* %t27 to i8*
	%t30 = sext i32 %t15 to i64
	%t29 = getelementptr inbounds i8, i8* %t28, i64 %t30
	%t14 = bitcast i8* %t29 to i32*
	%t17 = load i32, i32* %t14, align 4
	%t31 = load i32, i32* %l3, align 4
	%t18 = sub nsw i32 %t17, %t31
	%t10 = mul nsw i32 0, 4
	%t32 = getelementptr inbounds [3 x i32], [3 x i32]* %l2, i64 0, i64 0
	%t33 = bitcast i32* %t32 to i8*
	%t35 = sext i32 %t10 to i64
	%t34 = getelementptr inbounds i8, i8* %t33, i64 %t35
	%t9 = bitcast i8* %t34 to i32*
	store i32 %t18, i32* %t9, align 4
	%t20 = mul nsw i32 0, 4
	%t36 = getelementptr inbounds [3 x i32], [3 x i32]* %l2, i64 0, i64 0
	%t37 = bitcast i32* %t36 to i8*
	%t39 = sext i32 %t20 to i64
	%t38 = getelementptr inbounds i8, i8* %t37, i64 %t39
	%t19 = bitcast i8* %t38 to i32*
	%t22 = load i32, i32* %t19, align 4
	store i32 %t22, i32* %l0, align 4
	%t40 = load i32, i32* %l0, align 4
	ret i32 %t40
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
